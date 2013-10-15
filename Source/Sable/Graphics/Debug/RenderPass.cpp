#include <Sable\Graphics\Debug\RenderPass.h>

#include <Sable\Core\Geometry\AABoxTree.h>
#include <Sable\Graphics\Common\Manager.h>
#include <Sable\Graphics\Debug\GraphicCommandGroup.h>
#include <Sable\Graphics\Renderer\Header.h>
#include <Sable\Core\ManagedObject\Ref.h>


using namespace Sable;

#define DebugRenderer_LineStripVBSize 2 * 1024 * 10
#define DebugRenderer_TriangleListVBSize 3 * 1024 * 30
#define DebugRenderer_LineListVBSize 2 * 1024 * 30
#define DebugRenderer_PointListVBSize 1 * 1024 * 10
#define DebugRenderer_CommandStackSize 2048

IMPLEMENT_MANAGED_CLASS1( Sable, CDebugRenderPass, CRenderPass );

CDebugRenderPass::CDebugRenderPass( CRenderer& renderer ):
    CRenderPass(renderer)
{
    m_WorldMatrixStack.SetCapacity( 8 );
    m_ViewMatrixStack.SetCapacity( 8 );
    m_ProjectionMatrixStack.SetCapacity( 8 );
    m_ColorStack.SetCapacity( 8 );
	m_DepthTestStack.SetCapacity( 8 );
	m_FillModeStack.SetCapacity( 8 );
	m_CommandTable.SetCapacity( DebugRenderer_CommandStackSize );
}

CDebugRenderPass::~CDebugRenderPass()
{
}

CDebugRenderPass::SVertexBuffer::SVertexBuffer()
{
    Reset();
}

Void CDebugRenderPass::SVertexBuffer::Reset()
{
    RawBuff = NULL;
    VtxBuff = NULL;
    CurrentVtxCount = NULL;
    TotalVtxCount = NULL;
}

UInt32  CDebugRenderPass::SVertexBuffer::GetVertexCapacity() const
{
    if( VtxBuff )
        return VtxBuff->GetVertexCount();

    return 0;
}

Void CDebugRenderPass::SVertexBuffer::ResizeBuffer( UInt32 count )
{
    Byte* src;

    if( count <= GetVertexCapacity() )
        return;

	CRef<CGeometryVertexBuffer> tmpBuffer = NEWOBJ( CGeometryVertexBuffer,  );

	tmpBuffer->SetAttribute( CGeometryVertexBuffer::nFlag_Dynamic  );
	tmpBuffer->SetAttribute( CGeometryVertexBuffer::nFlag_DoNotDiscard );

    // Initialize vertex buffer
    if( VtxBuff == NULL )
    {
		tmpBuffer->SetRawData( count, sizeof( CDebugRenderPass::SVertex ) );
    }
    else
    {
        Bool wasLocked = VtxBuff->IsLocked();

        if( wasLocked )
            VtxBuff->UnLock();

        src = VtxBuff->Lock( 0, 0 ); // Lock the entire buffer 

		tmpBuffer->SetRawData( count, sizeof( CDebugRenderPass::SVertex ) );
        VtxBuff->UnLock();

        if( wasLocked )
            VtxBuff->Lock( 0, 0 );

        VtxBuff = NULL; // Delete previous buffer;

    }

    VtxBuff = tmpBuffer;
    VtxBuff->Load();
}

/**
Initialize the debug renderer and bind it to a specific renderer
*/
Void CDebugRenderPass::Initialize( CRenderer& renderer, CRenderTarget* outputRenderTarget )
{
    CRenderPass::Initialize( renderer, outputRenderTarget );
    m_LineStripVB.Reset();
    m_LineListVB.Reset();
    m_PointListVB.Reset();
    m_TriangleListVB.Reset();
	
    ResetStacks();

    LoadShader();
    BuildMeshes();

	CStatesDepthStencil::SDesc dsDesc;
	dsDesc.DepthTestEnable = TRUE;
	dsDesc.DepthWriteEnable = FALSE;
	m_StatesDepthStencil[TRUE].Acquire( dsDesc );

	dsDesc.DepthTestEnable = FALSE;
	dsDesc.DepthWriteEnable = FALSE;
	m_StatesDepthStencil[FALSE].Acquire( dsDesc );

	CStatesRasterizer::SDesc srDesc;
	srDesc.FillMode = nStateFillMode_WireFrame;
	srDesc.CullMode = nStateCullMode_Disabled;
    m_StatesRasterizer[nStateFillMode_WireFrame].Acquire( srDesc );

	srDesc.FillMode = nStateFillMode_Solid;
	srDesc.CullMode = nStateCullMode_Disabled;
	m_StatesRasterizer[nStateFillMode_Solid].Acquire( srDesc );

	srDesc.FillMode = nStateFillMode_WireFrame;
	srDesc.CullMode = nStateCullMode_Disabled;
	m_StatesRasterizer[nStateFillMode_Point].Acquire( srDesc );

	CStatesBlend::SDesc blendDesc;
	blendDesc.BlendEnable[0] = FALSE;
    m_StatesBlend.Acquire( blendDesc );
}

/**
Clear all stack and reset them to default values
*/
Void CDebugRenderPass::ResetStacks()
{
    CMatrix4x4f worldMatrix, viewMatrix, projectionMatrix;

    worldMatrix.SetFromIdentity();
    viewMatrix.SetFromIdentity();
    projectionMatrix.SetFromIdentity();

	m_FillModeStack.ClearAllItems();
    m_WorldMatrixStack.ClearAllItems();
    m_ViewMatrixStack.ClearAllItems();
    m_ProjectionMatrixStack.ClearAllItems();
    m_ColorStack.ClearAllItems();
	m_DepthTestStack.ClearAllItems();

    m_WorldMatrixStack.PushItem( worldMatrix );
    m_ViewMatrixStack.PushItem( viewMatrix );
    m_ProjectionMatrixStack.PushItem( projectionMatrix );
    m_ColorStack.PushItem( CColor( 0.2f, 1.0f, 0.0f, 0.0f ) );
	m_DepthTestStack.PushItem( TRUE );
	m_FillModeStack.PushItem( nStateFillMode_WireFrame );

    m_CommandTable.ClearAllItems();
}

/**
Push a NEW world matrix on the stack
*/
Void CDebugRenderPass::PushWorldMatrix( const CMatrix4x4f& matrix )
{
    m_WorldMatrixStack.PushItem( matrix );
}

/**
Push a NEW view matrix on the stack
*/
Void CDebugRenderPass::PushViewMatrix( const CMatrix4x4f& matrix )
{
    m_ViewMatrixStack.PushItem( matrix );
}

/**
Push a NEW projection matrix on the stack
*/
Void CDebugRenderPass::PushProjMatrix( const CMatrix4x4f& matrix )
{
    m_ProjectionMatrixStack.PushItem( matrix );
}

/**
Push both View and Projection matrix of the current camera
( i.e: The one provided by the binded renderer )
*/
Void CDebugRenderPass::PushViewProjMatrix()
{
    PushViewMatrix( );
    PushProjMatrix( );
}

/**
Pop both View and Projection matrix of the current camera
( i.e: The one provided by the binded renderer )
*/
Void CDebugRenderPass::PopViewProjMatrix()
{
    PopViewMatrix();
    PopProjMatrix();
}

CCamera* CDebugRenderPass::GetCamera() const
{
	if( GetRenderer().GetView() )
		return GetRenderer().GetView()->GetCamera();

	return NULL;
}

/**
Push View matrix of the current camera
( i.e: The one provided by the binded renderer )
*/
Void CDebugRenderPass::PushViewMatrix( )
{
	DebugAssert( GetCamera() );
    PushViewMatrix( GetCamera()->GetViewMatrix() );
}

/**
Push Projection matrix of the current camera
( i.e: The one provided by the binded renderer )
*/
Void CDebugRenderPass::PushProjMatrix( )
{
	DebugAssert( GetCamera() );
	PushProjMatrix( GetCamera()->GetProjectionMatrix() );
}

/**
Push a color on the stack.

This color will be used in all sub sequent draw call
*/
Void CDebugRenderPass::PushColor( const CColor& color )
{
    m_ColorStack.PushItem( color );
}

/**
Pop a world matrix of the stack
*/
Void CDebugRenderPass::PopWorldMatrix( )
{
    if( m_WorldMatrixStack.GetCapacity() > 1 )
        m_WorldMatrixStack.PopItem( );
}

/**
Pop a view matrix of the stack
*/
Void CDebugRenderPass::PopViewMatrix( )
{
    if( m_ViewMatrixStack.GetCapacity() > 1 )
        m_ViewMatrixStack.PopItem();
}

/**
Pop a projection matrix of the stack
*/
Void CDebugRenderPass::PopProjMatrix( )
{
    if( m_ProjectionMatrixStack.GetCapacity() > 1 )
        m_ProjectionMatrixStack.PopItem();
}

/**
Pop a color of the stack
*/
Void CDebugRenderPass::PopColor( )
{
    if( m_ColorStack.GetCapacity() > 1 )
        m_ColorStack.PopItem();
}

Void CDebugRenderPass::PushDepthTestMode( Bool mode )
{
	m_DepthTestStack.PushItem( mode );
}

Void CDebugRenderPass::PushFillMode( EStateFillMode mode )
{
	m_FillModeStack.PushItem( mode );
}

Void CDebugRenderPass::PopDepthTestMode( )
{
	if( m_DepthTestStack.GetCapacity() > 1 )
		m_DepthTestStack.PopItem();
}

Void CDebugRenderPass::PopFillMode( )
{
	if( m_FillModeStack.GetCapacity() > 1 )
		m_FillModeStack.PopItem();
}


Void CDebugRenderPass::DrawAABoxTreeNode( const CAABoxTree::CNode& node )
{
    if( node.GetLeftNode() == NULL && node.GetRightNode() == NULL && !node.GetBox().IsEmpty() )
    {
        PushColor( CColor::Black );
        DrawAABox( node.GetBox() );
        PopColor();
/*
        PushColor( CColor::Red );
        DrawTriangleList( node.GetTriangleList() );
        PopColor();*/
    }
}

Void CDebugRenderPass::DrawAABoxTreeNode( const CAABoxTree& tree, const CAABoxTree::CNode& node, UInt32 depth )
{
    DrawAABoxTreeNode( node );

    if( node.GetLeftNode() )
    {
        DrawAABoxTreeNode( tree, *node.GetLeftNode(), depth + 1 );
    }
    if( node.GetRightNode() )
    {
        DrawAABoxTreeNode( tree, *node.GetRightNode(), depth + 1 );
    }
}

/**
Render a full AABoxTree
*/
Void CDebugRenderPass::DrawAABoxTree( const CAABoxTree& boxTree )
{
    if( boxTree.GetRootNode() )
        DrawAABoxTreeNode( boxTree, *boxTree.GetRootNode(), 0 );
}

/**
Render a simple box.
\param center The center of the bbox
\param size The length of each side of the box
*/
Void CDebugRenderPass::DrawAABox( const CVector3f& center, const CVector3f& size )
{
	CVector3f p;
	Float32 x = size.GetX() / 2.0f;
	Float32 y = size.GetY() / 2.0f;
	Float32 z = size.GetZ() / 2.0f;

	BeginLineList();
	
	// lines from -x to +x
	DrawLine( center + CVector3f( -x,  y,  z ), center + CVector3f( x,  y,  z ) );
	DrawLine( center + CVector3f( -x,  y, -z ), center + CVector3f( x,  y, -z ) );
	DrawLine( center + CVector3f( -x, -y,  z ), center + CVector3f( x, -y,  z ) );
	DrawLine( center + CVector3f( -x, -y, -z ), center + CVector3f( x, -y, -z ) );

	// lines from -y to +y
	DrawLine( center + CVector3f( -x, -y,  z ), center + CVector3f( -x,  y,  z ) );
	DrawLine( center + CVector3f( -x, -y, -z ), center + CVector3f( -x,  y, -z ) );
	DrawLine( center + CVector3f(  x, -y,  z ), center + CVector3f(  x,  y,  z ) );
	DrawLine( center + CVector3f(  x, -y, -z ), center + CVector3f(  x,  y, -z ) );

	// lines from -z to +z
	DrawLine( center + CVector3f( -x, -y, -z ), center + CVector3f( -x, -y, z ) );
	DrawLine( center + CVector3f( -x,  y, -z ), center + CVector3f( -x,  y, z ) );
	DrawLine( center + CVector3f(  x, -y, -z ), center + CVector3f(  x, -y, z ) );
	DrawLine( center + CVector3f(  x,  y, -z ), center + CVector3f(  x,  y, z ) );

	EndLineList();

}

/**
Render a simple cylinder
*/
Void CDebugRenderPass::DrawCylinder( const CVector3f& center, const Float32 radius, const Float32 height )
{
	DebugError("Must be re implemented");
}

/**
Render a 2D quad textured with a given texture.
The quad position and size are given in clip space
*/
Void CDebugRenderPass::DrawTexture( const CTexture2D& texture, const CVector2f& pos, const CVector2f& size  )
{
    DebugError("Not yet implemented");
}

/**
Render a triangle
*/
Void CDebugRenderPass::DrawTriangle( const CTriangle& t )
{
    DrawTriangle( t.Vertices[0], t.Vertices[1], t.Vertices[2] );
}

/**
Render a triangle list
*/
Void CDebugRenderPass::DrawTriangleList( const CArray<CTriangle>& triangles )
{
    BeginTriangleList();
    for(UInt32 i=0;i<triangles.GetItemCount();i++)
    {
        const CTriangle& t = triangles[i];
        DrawTriangle( t );
    }
    EndTriangleList();
}

/**
Render a simple sphere
*/
Void CDebugRenderPass::DrawSphere( const CSphere& sphere )
{
    DrawSphere(sphere.Center, sphere.Radius);
}

/**
Render a simple sphere
*/
Void CDebugRenderPass::DrawSphere( const CVector3f& center, Float32 radius )
{
	UInt32 i=0;
	UInt32 stepCount = 20;
	Float32 step = MathPi * 2.0f / (Float32)stepCount;
	CVector3f pos;
	CMatrix4x4f m =m_WorldMatrixStack.GetTopItem();
	m.SetTranslationComponent( CVector3f::Zero );

	BeginLineStrip();
	for( i=0;i<=stepCount;i++ )
	{
		pos = center + CVector3f( MathCos( step*i ) * radius, MathSin( step*i ) * radius, 0.0f );
		DrawLine( pos );
	}
	EndLineStrip();

	BeginLineStrip();
	for( i=0;i<=stepCount;i++ )
	{
		pos = center + CVector3f( 0.0f, MathCos( step*i ) * radius, MathSin( step*i ) * radius );
		DrawLine( pos );
	}
	EndLineStrip();

	BeginLineStrip();
	for( i=0;i<=stepCount;i++ )
	{
		pos = center + CVector3f( MathCos( step*i ) * radius, 0.0f, MathSin( step*i ) * radius );
		DrawLine( pos );
	}
	EndLineStrip();

}

Void CDebugRenderPass::DrawAABox( const CAABox& box )
{
	DrawAABox( box.GetCenter(), box.GetSize() );
}

Void CDebugRenderPass::DrawDisk( const CDisk& disk )
{
    DebugError( "Not Implemented" );
}

/**
Start the drawing of a line strip.
Every BeginLineStrip  must be paired with a EndLineStrip.

Exemple:
\code
debugRenderer.BeginLineStrip();
    BeginLineStrip.DrawLine( CVector3f( 0,0,0 ) );
    BeginLineStrip.DrawLine( CVector3f( 0,1,0 ) );
    BeginLineStrip.DrawLine( CVector3f( 0,1,1 ) );
debugRenderer.EndLineStrip();
*/
Void CDebugRenderPass::BeginLineStrip()
{
    DebugGraphicCommandGroup( "CDebugRenderPass::BeginLineStrip" );

    DebugAssert( m_LineStripVB.RawBuff == NULL );

    UInt32 bufferSize = m_LineStripVB.GetVertexCapacity();

    m_LineStripVB.CurrentVtxCount = 0;
    m_LineStripVB.RawBuff = (SVertex*)m_LineStripVB.VtxBuff->Lock(
        m_LineStripVB.TotalVtxCount, 
        bufferSize - m_LineStripVB.TotalVtxCount);

}

/**
Finish the drawing of a line strip and create a NEW render command
*/
Void CDebugRenderPass::EndLineStrip()
{
    CMatrix4x4f
        finalMatrix;
    CDebugRendererCommand
        command;
    CRef<CGeometryMesh>
        mesh;

    DebugGraphicCommandGroup( "CDebugRenderPass::EndLineStrip" );

    mesh = NEWOBJ( CGeometryMesh,  );	
    
    m_LineStripVB.VtxBuff->UnLock();

    mesh->SetVertexBuffer( m_LineStripVB.VtxBuff );
    mesh->SetPrimitiveType( nPrimitiveType_LineStrip );
    mesh->SetUsedVertexCount( m_LineStripVB.CurrentVtxCount );
    mesh->SetVertexOffset( m_LineStripVB.TotalVtxCount - m_LineStripVB.CurrentVtxCount );
	mesh->SetVertexLayout( &m_VertexLayout );

    finalMatrix =	m_WorldMatrixStack.GetTopItem() * 
                    m_ViewMatrixStack.GetTopItem() * 
                    m_ProjectionMatrixStack.GetTopItem();

    command.SetWorldViewProjectionMatrix( finalMatrix );
    command.SetColor( m_ColorStack.GetTopItem() );
    command.SetMesh( *mesh );
	command.SetDepthTestEnabled( m_DepthTestStack.GetTopItem() );


    m_CommandTable.PushItem( command );

    m_LineStripVB.RawBuff = NULL;
    m_LineStripVB.CurrentVtxCount = 0;

}

/**
Add one point to a line strip.
Must be called between Begin/End LineStrip
*/
Void CDebugRenderPass::DrawLine( const CVector3f& point )
{
    if( m_LineStripVB.TotalVtxCount + 1 > m_LineStripVB.GetVertexCapacity() )
    {
        EndLineStrip();
        m_LineStripVB.ResizeBuffer( m_LineStripVB.GetVertexCapacity() + DebugRenderer_LineStripVBSize );
        BeginLineStrip();
    }

    m_LineStripVB.RawBuff[ m_LineStripVB.CurrentVtxCount ].Pos = point;
    m_LineStripVB.RawBuff[ m_LineStripVB.CurrentVtxCount ].Color = m_ColorStack.GetTopItem();
    m_LineStripVB.CurrentVtxCount ++;
    m_LineStripVB.TotalVtxCount++;
}

/**
Start the drawing of a line list.
Every BeginLineList  must be paired with a EndLineList.

Exemple:
\code
debugRenderer.BeginLineStrip();
    BeginLineStrip.DrawLine( CVector3f( 0,0,0 ) );
    BeginLineStrip.DrawLine( CVector3f( 0,1,0 ) );
    BeginLineStrip.DrawLine( CVector3f( 0,1,1 ) );
debugRenderer.EndLineStrip();
*/
Void CDebugRenderPass::BeginLineList()
{
    DebugAssert( m_LineListVB.RawBuff == NULL );

    UInt32 bufferSize = m_LineListVB.VtxBuff->GetVertexCount();

    m_LineListVB.CurrentVtxCount = 0;

    if( bufferSize - m_LineListVB.TotalVtxCount > 0 )
    {
        m_LineListVB.RawBuff = (SVertex*)m_LineListVB.VtxBuff->Lock(
            m_LineListVB.TotalVtxCount, bufferSize - m_LineListVB.TotalVtxCount );
    }
}

/**
Finish the drawing of line list and create a NEW render command
*/
Void CDebugRenderPass::EndLineList()
{
    if( !m_LineListVB.VtxBuff->IsLocked() )
        return ;

    CMatrix4x4f finalMatrix;
    CDebugRendererCommand command;

	CGeometryMesh tmp;

    CRef<CGeometryMesh> mesh;

    mesh = NEWOBJ( CGeometryMesh,  );	
    
    m_LineListVB.VtxBuff->UnLock();

    mesh->SetVertexBuffer( m_LineListVB.VtxBuff );
    mesh->SetPrimitiveType( nPrimitiveType_LineList );
    mesh->SetUsedVertexCount( m_LineListVB.CurrentVtxCount );
    mesh->SetVertexOffset( m_LineListVB.TotalVtxCount - m_LineListVB.CurrentVtxCount );
	mesh->SetVertexLayout( &m_VertexLayout );

    finalMatrix =	m_WorldMatrixStack.GetTopItem() * 
                    m_ViewMatrixStack.GetTopItem() * 
                    m_ProjectionMatrixStack.GetTopItem();

    command.SetWorldViewProjectionMatrix( finalMatrix );
    command.SetColor( m_ColorStack.GetTopItem() );
    command.SetMesh( *mesh );
	command.SetDepthTestEnabled( m_DepthTestStack.GetTopItem() );

    m_CommandTable.PushItem( command );

    m_LineListVB.RawBuff = NULL;
    m_LineListVB.CurrentVtxCount = 0;

}

/**
Add one line to a line list.
Must be called between Begin/End LineList
*/
Void CDebugRenderPass::DrawLine( const CVector3f& a, const CVector3f& b )
{
    if( m_LineListVB.TotalVtxCount + 2 > m_LineListVB.GetVertexCapacity() )
    {
        EndLineList();
        m_LineListVB.ResizeBuffer( m_LineListVB.GetVertexCapacity() + DebugRenderer_LineListVBSize );
        BeginLineList();
    }

    m_LineListVB.RawBuff[ m_LineListVB.CurrentVtxCount ].Pos = a;
    m_LineListVB.RawBuff[ m_LineListVB.CurrentVtxCount ].Color = m_ColorStack.GetTopItem();
    m_LineListVB.CurrentVtxCount ++;
    m_LineListVB.TotalVtxCount++;

    m_LineListVB.RawBuff[ m_LineListVB.CurrentVtxCount ].Pos = b;
    m_LineListVB.RawBuff[ m_LineListVB.CurrentVtxCount ].Color = m_ColorStack.GetTopItem();
    m_LineListVB.CurrentVtxCount ++;
    m_LineListVB.TotalVtxCount++;

}

/**
Start the drawing of a triangle list.
Every BeginTriangleList  must be paired with a EndTriangleList.

Exemple:
\code
debugRenderer.BeginTriangleList();
    BeginLineStrip.DrawTriangle( a, b, c );
debugRenderer.EndTriangleList();
*/
Void CDebugRenderPass::BeginTriangleList()
{
    DebugAssert( m_TriangleListVB.RawBuff == NULL );

    UInt32 bufferSize = m_TriangleListVB.VtxBuff->GetVertexCount();

    m_TriangleListVB.CurrentVtxCount = 0;
    m_TriangleListVB.RawBuff = (SVertex*)m_TriangleListVB.VtxBuff->Lock(
        m_TriangleListVB.TotalVtxCount, bufferSize - m_TriangleListVB.TotalVtxCount );
}

/**
Finish the drawing of triangle list and create a NEW render command
*/
Void CDebugRenderPass::EndTriangleList()
{
    CMatrix4x4f finalMatrix;
    CDebugRendererCommand command;
    CRef<CGeometryMesh> mesh;

    mesh = NEWOBJ( CGeometryMesh,  );	
    
    m_TriangleListVB.VtxBuff->UnLock();

    mesh->SetVertexBuffer( m_TriangleListVB.VtxBuff );
    mesh->SetPrimitiveType( nPrimitiveType_TriangleList );
    mesh->SetUsedVertexCount( m_TriangleListVB.CurrentVtxCount );
    mesh->SetVertexOffset( m_TriangleListVB.TotalVtxCount - m_TriangleListVB.CurrentVtxCount );
	mesh->SetVertexLayout( &m_VertexLayout );

    finalMatrix =	m_WorldMatrixStack.GetTopItem() * 
                    m_ViewMatrixStack.GetTopItem() * 
                    m_ProjectionMatrixStack.GetTopItem();

    command.SetWorldViewProjectionMatrix( finalMatrix );
    command.SetColor( m_ColorStack.GetTopItem() );
    command.SetMesh( *mesh );
	command.SetDepthTestEnabled( m_DepthTestStack.GetTopItem() );
	command.SetFillMode( m_FillModeStack.GetTopItem() );

    m_CommandTable.PushItem( command );

    m_TriangleListVB.RawBuff = NULL;
    m_TriangleListVB.CurrentVtxCount = 0;

}

/**
Add one triangle to a triangle list.
Must be called between Begin/End TriangleList
*/
Void CDebugRenderPass::DrawTriangle( const CVector3f& a, const CVector3f& b, const CVector3f& c )
{
    if( m_TriangleListVB.TotalVtxCount + 3 > m_TriangleListVB.GetVertexCapacity() )
    {
        EndTriangleList();
        m_TriangleListVB.ResizeBuffer( m_TriangleListVB.GetVertexCapacity() + DebugRenderer_TriangleListVBSize );
        BeginTriangleList();
    }

    m_TriangleListVB.RawBuff[ m_TriangleListVB.CurrentVtxCount ].Pos = a;
    m_TriangleListVB.RawBuff[ m_TriangleListVB.CurrentVtxCount ].Color = m_ColorStack.GetTopItem();
    m_TriangleListVB.CurrentVtxCount ++;
    m_TriangleListVB.TotalVtxCount++;
    
    m_TriangleListVB.RawBuff[ m_TriangleListVB.CurrentVtxCount ].Pos = b;
    m_TriangleListVB.RawBuff[ m_TriangleListVB.CurrentVtxCount ].Color = m_ColorStack.GetTopItem();
    m_TriangleListVB.CurrentVtxCount ++;
    m_TriangleListVB.TotalVtxCount++;
    
    m_TriangleListVB.RawBuff[ m_TriangleListVB.CurrentVtxCount ].Pos = c;
    m_TriangleListVB.RawBuff[ m_TriangleListVB.CurrentVtxCount ].Color = m_ColorStack.GetTopItem();
    m_TriangleListVB.CurrentVtxCount ++;
    m_TriangleListVB.TotalVtxCount++;
    
}


/**
Start the drawing of a pont list
*/
Void CDebugRenderPass::BeginPointList()
{
    DebugAssert( m_PointListVB.RawBuff == NULL );

    UInt32 bufferSize = m_PointListVB.VtxBuff->GetVertexCount();

    m_PointListVB.CurrentVtxCount = 0;
    m_PointListVB.RawBuff = (SVertex*)m_PointListVB.VtxBuff->Lock(
        m_PointListVB.TotalVtxCount, bufferSize - m_PointListVB.TotalVtxCount );
}

/**
Finish the drawing of point list and create a NEW render command
*/
Void CDebugRenderPass::EndPointList()
{
    CMatrix4x4f finalMatrix;
    CDebugRendererCommand command;
    CRef<CGeometryMesh> mesh;

    mesh = NEWOBJ( CGeometryMesh,  );	
    
    m_PointListVB.VtxBuff->UnLock();

    mesh->SetVertexBuffer( m_PointListVB.VtxBuff );
    mesh->SetPrimitiveType( nPrimitiveType_PointList );
    mesh->SetUsedVertexCount( m_PointListVB.CurrentVtxCount );
    mesh->SetVertexOffset( m_PointListVB.TotalVtxCount - m_PointListVB.CurrentVtxCount );
	mesh->SetVertexLayout( &m_VertexLayout );

    finalMatrix =	m_WorldMatrixStack.GetTopItem() * 
                    m_ViewMatrixStack.GetTopItem() * 
                    m_ProjectionMatrixStack.GetTopItem();

    command.SetWorldViewProjectionMatrix( finalMatrix );
    command.SetColor( m_ColorStack.GetTopItem() );
    command.SetMesh( *mesh );
	command.SetDepthTestEnabled( m_DepthTestStack.GetTopItem() );

    m_CommandTable.PushItem( command );

    m_PointListVB.RawBuff = NULL;
    m_PointListVB.CurrentVtxCount = 0;

}

/**
Add one point to a point list.
Must be called between Begin/End PointList
*/
Void CDebugRenderPass::DrawPoint( const CVector3f& a )
{
    if( m_PointListVB.TotalVtxCount + 1 > m_PointListVB.GetVertexCapacity() )
    {
        EndPointList();
        m_PointListVB.ResizeBuffer( m_PointListVB.GetVertexCapacity() + DebugRenderer_PointListVBSize );
        BeginPointList();
    }

    m_PointListVB.RawBuff[ m_PointListVB.CurrentVtxCount ].Pos = a;
    m_PointListVB.RawBuff[ m_PointListVB.CurrentVtxCount ].Color = m_ColorStack.GetTopItem();
    m_PointListVB.CurrentVtxCount ++;
    m_PointListVB.TotalVtxCount++;
}


/**
Render s CTCBCurve3f using a precision specified by step
*/
Void CDebugRenderPass::DrawSpline3D( const CTCBCurve3f& spline, const UInt32 step )
{
    Index
        index;

    BeginLineStrip();

    for( index = 0; index < step ; index++ )
    {
        DrawLine( spline.EvaluteAt( (Float32) index / ( step - 1 ) ) );
    }

    EndLineStrip();


    for( index = 0; index < spline.GetNodeCount() ; index++ )
    {
        DrawAABox( spline.GetNode( index ).Value, CVector3f(4.0f,4.0f,4.0f) );
    }
}


Void CDebugRenderPass::DrawPlane( const CPlane& plane, const Float32 scale )
{
	DebugError("Must be re implemented");
}

Void CDebugRenderPass::DrawAdaptativeGrid( const CVector3f& pos, const CVector2f& size, const CColor& col1, const CColor& col2 )
{
    DebugGraphicCommandGroup( "CDebugRenderPass::DrawAdaptativeGrid" );

    CVector2f halfSize = size / 2.0f;
    CVector3f posToCam = GetCamera()->GetWorldPosition() - pos;

    PushColor( col2 );

    Int32 i = 0;
    for( i=-(Int32)halfSize.GetX() ; i <= (Int32)halfSize.GetX() ; i++ )
    {
        BeginLineStrip();
        DrawLine( CVector3f( (Float32)-halfSize.GetX(), 0, (Float32)i ) );
        DrawLine( CVector3f( (Float32)halfSize.GetX(), 0, (Float32)i ) );
        EndLineStrip();
    }

    for( i=-(Int32)halfSize.GetY() ; i <= (Int32)halfSize.GetY() ; i++ )
    {
        BeginLineStrip();
        DrawLine( CVector3f( (Float32)i, 0, (Float32)-halfSize.GetY() ) );
        DrawLine( CVector3f( (Float32)i, 0, (Float32)halfSize.GetY() ) );
        EndLineStrip();
    }

    PopColor();


    PushColor( col1 );
    BeginLineList();

    DrawLine( CVector3f( -halfSize.GetX(), 0.0f, 0.0f ), CVector3f( halfSize.GetX(), 0.0f, 0.0f ) );
    DrawLine( CVector3f( 0.0f, 0.0f, -halfSize.GetY() ), CVector3f( 0.0f, 0.0f, halfSize.GetY()  ) );

    EndLineList();
    PopColor();
}

Void CDebugRenderPass::DrawUnitGrid( const CVector3f& pos, Int32 width )
{
    Int32 halfWidth = width / 2;
    Int32 i;

    for( i=-halfWidth ; i <= halfWidth ; i++ )
    {
        BeginLineStrip();
        DrawLine( CVector3f( (Float32)-halfWidth, 0, (Float32)i ) );
        DrawLine( CVector3f( (Float32)halfWidth, 0, (Float32)i ) );
        EndLineStrip();
    }

    for( i=-halfWidth ; i <= halfWidth ; i++ )
    {
        BeginLineStrip();
        DrawLine( CVector3f( (Float32)i, 0, (Float32)-halfWidth ) );
        DrawLine( CVector3f( (Float32)i, 0, (Float32)halfWidth ) );
        EndLineStrip();
    }

}

Void CDebugRenderPass::DrawSpatialFrame( Float32 size )
{
    DebugGraphicCommandGroup("CDebugRenderPass::DrawSpatialFrame");

    PushColor( CColor::Red );
    DrawRay( CRay( CVector3f::Zero, CVector3f::XAxis ), size );
    PopColor();

    PushColor( CColor::Green );
    DrawRay( CRay( CVector3f::Zero, CVector3f::YAxis ), size );
    PopColor();

    PushColor( CColor::Blue );
    DrawRay( CRay( CVector3f::Zero, CVector3f::ZAxis ), size );
    PopColor();
}

Void CDebugRenderPass::LoadShader()
{
    m_MainShader = NEWOBJ( CShader, ( ) );
    m_MainShader->Load( CoreManager.GetFileSystem().GetFilePath( "System/Shader", "System/DebugRenderer.vsh" ),
                        CoreManager.GetFileSystem().GetFilePath( "System/Shader", "System/DebugRenderer.psh" ),
                        CFilePath() );
 }

Void CDebugRenderPass::BuildMeshes()
{
    // Initialize vertex buffer
    m_LineStripVB.ResizeBuffer( DebugRenderer_LineStripVBSize );
    m_LineListVB.ResizeBuffer( DebugRenderer_LineListVBSize );
    m_PointListVB.ResizeBuffer( DebugRenderer_PointListVBSize );
    m_TriangleListVB.ResizeBuffer( DebugRenderer_TriangleListVBSize );

	m_VertexLayout.AddElement( nVertexComponent_Position, nVertexComponentType_Float3 );
	m_VertexLayout.AddElement( nVertexComponent_Color0, nVertexComponentType_Float4 );
	m_VertexLayout.Initialize();

}

Void CDebugRenderPass::DrawRay( const CRay& ray, const Float32 lenght  )
{
    DebugGraphicCommandGroup("CDebugRenderPass::DrawRay");

    CVector3f a, b, up, right;

    up = CVector3f( 0.0f, 1.0f, 0.0f );

    a = ray.Origin ;
    b = ray.Origin + ray.Direction*lenght;

    BeginLineList();
        DrawLine( a, b );
    EndLineList();
}

Void CDebugRenderPass::DrawVector( const CVector3f& v, const CVector3f& o )
{
    CRay r;

    r.Direction = v;
    r.Direction.Normalize();

    r.Origin = o;
 
    DrawRay( r, v.GetLength() );
}

Bool CDebugRenderPass::ProcessTraversedNode( CNode& node, CRenderer& renderer )
{
	return TRUE;
}

Void CDebugRenderPass::Render( CRenderer& renderer )
{   
	DebugGraphicCommandGroup( "CDebugRenderPass::Render" );

    renderer.Activate( m_StatesBlend );

    CStack<CDebugRendererCommand>::Iterator
        iterator;


    ForEachItem( iterator, m_CommandTable )
    {
		CDebugRendererCommand& rc = iterator.GetData();
        m_MainShader->GetParameter( "WorldViewProjectionMatrix" )->SetValue( rc.GetWorldViewProjectionMatrix() );
        renderer.Activate( *m_MainShader );

        CStatesDepthStencil& ds = m_StatesDepthStencil[ rc.GetDepthTestEnabled() ];
		renderer.Activate( ds );

		CStatesRasterizer& sr = m_StatesRasterizer[ rc.GetFillMode() ];
		renderer.Activate( sr );

        iterator.GetData().GetMesh().Activate(renderer);
        iterator.GetData().GetMesh().Render();

    }

    ResetStacks();

    m_LineStripVB.TotalVtxCount = 0;
    m_LineListVB.TotalVtxCount = 0;
    m_PointListVB.TotalVtxCount = 0;
    m_TriangleListVB.TotalVtxCount = 0;

	renderer.Activate( renderer.GetDefaultRasterizerStates() );
	renderer.Activate( renderer.GetDefaultBlendStates() );
	renderer.Activate( renderer.GetDefaultDepthStencilStates() );
}
