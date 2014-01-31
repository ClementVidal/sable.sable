#include <Sable/Gui/Common/RenderPass.h>

#include <Sable/Input/Common/Manager.h>
#include <Sable/Input/Keyboard/Header.h>
#include <Sable/Gui/Layout/Item.h>
#include <Sable/Gui/Layout/Layout.h>
#include <Sable/Gui/Layout/WidgetItem.h>
#include <Sable/Graphics/Text/Text.h>
#include <Sable/Graphics/Common/Manager.h>
#include <Sable/Graphics/Debug/GraphicCommandGroup.h>

#define UIMANAGER_PRERENDER_TABLE_SIZE 128
//#define DEBUG_EVENTS

using namespace Sable;

IMPLEMENT_MANAGED_CLASS( Sable, CGuiRenderPass );

CGuiRenderPass::CGuiRenderPass(CRenderer& renderer ) :
    CRenderPass( renderer )
{
    m_ShowCursor = TRUE;
    m_ShowFps = TRUE;
    m_ShowProfView = FALSE;
    m_ShowMemView = FALSE;
    m_WidgetTableSize  =0;
    m_WidgetTable.SetItemCount( UIMANAGER_PRERENDER_TABLE_SIZE );
}

Void CGuiRenderPass::SortWidgetTable( Int32 l, Int32 r )
{
    Int32 m;
    Int32 i;
    
    if( l < r )
    {
        m_WidgetTable.SwapItems( l, (l+r)/2);
        CWidget* pivot = m_WidgetTable[l];
        
        m = l;
        for (i = l + 1; i <= r; i++)
        {
            if ( m_WidgetTable[i]->GetDepth()  <  pivot->GetDepth() ) 
            {
                m++;
                m_WidgetTable.SwapItems( m, i);
            }
        }
        m_WidgetTable.SwapItems( l , m);
        SortWidgetTable( l, m - 1);
        SortWidgetTable( m + 1, r);
    }
}

Void CGuiRenderPass::Initialize( CRenderer& renderer, CRenderTarget* outputRenderTarget )
{
    if( InputManager.GetMouse() )
    {
        EVENT_CONNECT_SLOT( InputManager.GetMouse()->SignalEvent, m_SlotMouseEvent, &CGuiRenderPass::OnMouseEvent );
    }

    if( InputManager.GetKeyboard() )
    {
        EVENT_CONNECT_SLOT( InputManager.GetKeyboard()->SignalEvent, m_SlotKeyboardEvent, &CGuiRenderPass::OnKeyboardEvent )
    }

    m_Shader.Load(  CoreManager.GetFileSystem().GetFilePath( "System/Shader", "RendererPass/UserInterface/DefaultWidget.vsh" ),
                    CoreManager.GetFileSystem().GetFilePath( "System/Shader", "RendererPass/UserInterface/DefaultWidget.psh" ),
                    CFilePath() );

    m_Cursor = NEWOBJ( CCursor, () );

	InitVertexBuffer();

	CStatesBlend::SDesc blendDesc;
	blendDesc.BlendEnable[0] = TRUE;
	blendDesc.SrcColorBlend = nStateBlend_SrcAlpha;
	blendDesc.DstColorBlend = nStateBlend_InvSrcAlpha;
	m_StatesBlend.Acquire( blendDesc );
	
	CStatesRasterizer::SDesc srDesc;
	srDesc.CullMode = nStateCullMode_Disabled;
	m_StatesRasterizer.Acquire( srDesc );

	CStatesDepthStencil::SDesc dsDesc;
	dsDesc.DepthTestEnable = FALSE;
	m_StatesDepthStencil.Acquire( dsDesc );

    m_Shader.SetBlendStates( &m_StatesBlend );
	m_Shader.SetDepthStencilStates( &m_StatesDepthStencil );
	m_Shader.SetRasterizerStates( &m_StatesRasterizer );

    m_FpsText.SetPosition( CVector2f( 0.8f, 0.0f ) );
	m_FpsText.SetCapacity( 128 );

	m_ProfViewText.SetPosition( CVector2f( 0.0f, 0.0f ) );
	m_ProfViewText.SetCapacity( 1024 );

	m_MemViewText.SetPosition( CVector2f( 0.0f, 0.4f ) );
	m_MemViewText.SetCapacity( 1024 * 4 );

	CStatesSampler::SDesc ssDesc;

	m_StateSampler.Acquire( ssDesc );
	
    CRenderPass::Initialize( renderer, outputRenderTarget );
}

Void CGuiRenderPass::ShowFps( Bool onOff )
{
    m_ShowFps = onOff;
}

Void CGuiRenderPass::ShowProfView( Bool onOff )
{
	m_ShowProfView = onOff;
}

Void CGuiRenderPass::ShowMemView( Bool onOff )
{
	m_ShowMemView = onOff;
}

Void CGuiRenderPass::ShowCursor( Bool onOff)
{
    m_ShowCursor = onOff;
}

CGuiRenderPass::~CGuiRenderPass()
{
}

Void CGuiRenderPass::AddToWidgetTable( CWidget& wdg )
{
	m_WidgetTable[m_WidgetTableSize] = &wdg;
	m_WidgetTableSize++;
}

Bool CGuiRenderPass::ProcessTraversedLayout( CLayoutItem& node, CRenderer& renderer )
{
	if( node.GetTypeInfo().IsKindOf( CLayoutWidgetItem::GetStaticTypeInfo() ) )
	{
		ProcessTraversedNode( ((CLayoutWidgetItem&)node).GetWidget(), renderer );
	}

	CLayoutItem* child = node.GetChild();
	while( child )
	{
		ProcessTraversedLayout( *child, renderer );
		child = child->GetSibling();
	}

	return TRUE;
}

Bool CGuiRenderPass::ProcessTraversedNode( CNode& node, CRenderer& renderer )
{
	CWidget* wdg = node.CastTo<CWidget>();
	if( wdg )
	{
		if( !wdg->IsVisible() )
			return FALSE;

		AddToWidgetTable( *wdg );

		CLayoutItem* l = wdg->GetLayout();
		if( l )
		{
			ProcessTraversedLayout( *l, renderer );
		}

	}

	return TRUE;
}

Void CGuiRenderPass::Render( CRenderer& renderer )
{
	DebugProfile( "CGuiRenderPass::Render" );

    DebugGraphicCommandGroup( "CGuiRenderPass::Render" );

	SortWidgetTable( 0, m_WidgetTableSize - 1 );

    UInt32 i;

	Bool isText = FALSE;
	
	CShader* shader;
	CGeometryVertexBuffer* vb;
    for( i=0;i<m_WidgetTableSize; i++ )
    {
		shader = &m_Shader;
		if( m_WidgetTable[i]->GetCustomShader() )
		{
			shader = m_WidgetTable[i]->GetCustomShader();
		}

		vb = &m_VertexBuffer;
		if( m_WidgetTable[i]->GetCustomVB() )
		{
			vb = m_WidgetTable[i]->GetCustomVB();
		}

		renderer.Activate( *shader );
		renderer.Activate( *vb, 0 );
		renderer.Activate( m_VertexLayout );

        m_WidgetTable[i]->Render( renderer, *shader );
    }


	renderer.Activate( m_VertexBuffer, 0 );
	renderer.Activate( m_Shader );
	renderer.Activate( m_VertexLayout );

    if( m_ShowCursor )
    {    
#ifdef SETUP_PACKAGE_SABLE_INPUT
        m_Cursor->SetPosition( InputManager.GetMouse()->GetPosition() );
#endif
        m_Cursor->Render(renderer);
    }

    if( m_ShowFps )
    {
        Char tmpBuffer[128];

        StringSetFormattedText( tmpBuffer, 128, "FPS: %.5f", GraphicsManager.GetAverageFPS() );
        m_FpsText.SetText( tmpBuffer );
        m_FpsText.Render( renderer );
    }

	if( m_ShowProfView )
	{
		m_ProfView.Update( );

		m_ProfViewText.SetText( m_ProfView.GetBuffer() );
		m_ProfViewText.Render( renderer );
	}
	if( m_ShowMemView )
	{
		m_MemView.Update( );

		m_MemViewText.SetText( m_MemView.GetBuffer() );
		m_MemViewText.Render( renderer );
	}
}

Void CGuiRenderPass::OnKeyboardEvent( EKeyboardEventType type, EKeyboardEventData data )
{
	if( type == nKeyboardEventType_KeyDown )
	{
		if( data == nKeyboardEventData_LEFT )
		{
			m_ProfView.MoveBackward();			
		}
		else if( data == nKeyboardEventData_RIGHT )
		{
			m_ProfView.MoveForward();
		}
		else if( data == nKeyboardEventData_UP )
		{
			m_ProfView.MoveUp();
		}
		else if( data == nKeyboardEventData_DOWN )
		{
			m_ProfView.MoveDown();
		}
		else if( data == nKeyboardEventData_P )
		{
			if( InputManager.GetKeyboard()->GetIsKeyDown( nKeyboardEventData_LeftControl ) && 
				InputManager.GetKeyboard()->GetIsKeyDown( nKeyboardEventData_LeftShift ))
			{
				m_ShowProfView = !m_ShowProfView;
				if( m_ShowProfView )
					m_ProfView.Sample();
			}
		}
		else if( data == nKeyboardEventData_Space )
		{
			if( InputManager.GetKeyboard()->GetIsKeyDown( nKeyboardEventData_LeftControl ) && 
				InputManager.GetKeyboard()->GetIsKeyDown( nKeyboardEventData_LeftShift ))
			{
				if( m_ShowProfView )
					m_ProfView.Sample();
			}
		}
		else if( data == nKeyboardEventData_F )
		{
			if( InputManager.GetKeyboard()->GetIsKeyDown( nKeyboardEventData_LeftControl ) && 
				InputManager.GetKeyboard()->GetIsKeyDown( nKeyboardEventData_LeftShift ))
			{
				m_ShowFps = !m_ShowFps;
			}
		}
		else if( data == nKeyboardEventData_C )
		{
			if( InputManager.GetKeyboard()->GetIsKeyDown( nKeyboardEventData_LeftControl ) && 
				InputManager.GetKeyboard()->GetIsKeyDown( nKeyboardEventData_LeftShift ))
			{
				m_ShowCursor = !m_ShowCursor;
			}
		}
		else if( data == nKeyboardEventData_M )
		{
			if( InputManager.GetKeyboard()->GetIsKeyDown( nKeyboardEventData_LeftControl ) && 
				InputManager.GetKeyboard()->GetIsKeyDown( nKeyboardEventData_LeftShift ))
			{
				m_ShowMemView = !m_ShowMemView;
			}
		}
	}
}

Void CGuiRenderPass::OnMouseEvent( EMouseEventType type, EMouseEventData data, const CVector2f& pos )
{
	if( !GetRenderer().GetCurrentViewport() )
		return;

	CVector2i mousePosition = pos * GetRenderer().GetCurrentViewport()->GetSize();

	if (type == nMouseEventType_KeyDown)
	{
		MouseDown(mousePosition, data);
	}
	else if (type == nMouseEventType_KeyUp)
	{
		MouseUp(mousePosition, data);
	}
    else if (type == nMouseEventType_Move)
	{
		MouseMove(mousePosition, data);
	}
}

Void CGuiRenderPass::InitVertexBuffer()
{
	SVertex streamData[ 4 ];

	streamData[ 0 ].Position = CVector3f(  0.0f, 1.0f, 0.0f );
	streamData[ 1 ].Position = CVector3f( 0.0f, 0.0f, 0.0f );
	streamData[ 2 ].Position = CVector3f(  1.0f, 1.0f, 0.0f );
	streamData[ 3 ].Position = CVector3f( 1.0f, 0.0f, 0.0f );

	streamData[ 0 ].TexCoord0 = CVector2f( 0.0f, 1.0f );
	streamData[ 1 ].TexCoord0 = CVector2f( 0.0f, 0.0f );
	streamData[ 2 ].TexCoord0 = CVector2f( 1.0f, 1.0f );
	streamData[ 3 ].TexCoord0 = CVector2f( 1.0f, 0.0f );

	m_VertexLayout.AddElement( nVertexComponent_Position, nVertexComponentType_Float3 );
	m_VertexLayout.AddElement( nVertexComponent_TexCoord0, nVertexComponentType_Float2 );
	m_VertexLayout.Initialize();

	m_VertexBuffer.SetRawData( 4, sizeof( SVertex ), ( Byte* ) streamData  );

	m_VertexBuffer.Load( );
}

Void CGuiRenderPass::DrawQuad( CShader& shader, const CRect2Di& rect,const CColor& color)
{
    if( rect.IsEmpty() )
        return;

	shader.GetParameter("Position")->SetValue( CVector2f( rect.GetLowerLeftCorner() ) );
	shader.GetParameter("Size")->SetValue( CVector2f( rect.GetSize() ) );
	shader.GetParameter("Color")->SetValue(color );

	GetRenderer().GetCurrentViewport()->GetShaderConnector().FlushParametersValues( shader );

	CShaderParameter* sampler = shader.GetParameter( "Sampler");
	if( sampler )
		sampler->SetValue( m_StateSampler );

	GetRenderer().Activate( m_VertexBuffer, 0 );
	GetRenderer().Draw(nPrimitiveType_TriangleStrip, m_VertexBuffer.GetVertexCount(), 0 );

}

Void CGuiRenderPass::DrawBeveledQuad( CShader& shader, const CRect2Di& rect, const UInt8 bevelSize, const CColor& color, const CColor& bevelColor)
{
    if( rect.IsEmpty() )
        return;

	m_Shader.GetParameter("Position")->SetValue( CVector2f( rect.GetLowerLeftCorner() ) ) ;
	m_Shader.GetParameter("Size")->SetValue( CVector2f( rect.GetSize() ) );
	m_Shader.GetParameter("Color")->SetValue( bevelColor );
	GetRenderer().Activate( m_VertexBuffer, 0 );
	GetRenderer().Draw(nPrimitiveType_TriangleStrip, m_VertexBuffer.GetVertexCount(), 0 );

	m_Shader.GetParameter("Position")->SetValue( CVector2f( rect.GetLowerLeftCorner() ) + CVector2f( bevelSize, bevelSize ) );
	m_Shader.GetParameter("Size")->SetValue( CVector2f( rect.GetSize() ) - CVector2f( bevelSize, bevelSize ) * 2.0f );
	m_Shader.GetParameter("Color")->SetValue(color);
	GetRenderer().Draw(nPrimitiveType_TriangleStrip, m_VertexBuffer.GetVertexCount(), 0 );

}

Void CGuiRenderPass::MouseDown(const CVector2i& pos, const EMouseEventData data )
{
    if( !InputManager.GetMouse() || !GetRenderer().GetView() ) 
        return;

	CSceneWorld* world = GetRenderer().GetView()->GetWorld();
	if( !world )
		return;

	CWidgetEvent event( CWidgetEvent::nType_CursorDown, pos, (UInt32)data );
	world->GetGuiRootNode().SendEvent( event );
}

Void CGuiRenderPass::Update()
{
   if( !InputManager.GetMouse() ) 
        return;

   // Compile this only if input package is available
#ifdef SETUP_PACKAGE_SABLE_INPUT
	CVector2f mousePosition = CVector2f(InputManager.GetMouse()->GetXPosition(), InputManager.GetMouse()->GetYPosition());

	GetCursor().SetPosition(mousePosition);
#endif
	m_WidgetTableSize = 0;
}

Void CGuiRenderPass::MouseUp(const CVector2i& pos, const EMouseEventData data  )
{
	if( !InputManager.GetMouse() || !GetRenderer().GetView() ) 
		return;

	CSceneWorld* world = GetRenderer().GetView()->GetWorld();
	if( !world )
		return;

	CWidgetEvent event( CWidgetEvent::nType_CursorUp, pos, (UInt32)data );
	world->GetGuiRootNode().SendEvent( event );
}

Void CGuiRenderPass::MouseMove(const CVector2i& pos, const EMouseEventData data )
{
	if( !InputManager.GetMouse() || !GetRenderer().GetView() ) 
		return;

	CSceneWorld* world = GetRenderer().GetView()->GetWorld();
	if( !world )
		return;

	CWidgetEvent event( CWidgetEvent::nType_CursorMove, pos, (UInt32)data );
	world->GetGuiRootNode().SendEvent( event );
}
