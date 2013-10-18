#ifndef _SABLE_GUI_COMMON_RENDERPASS_
#define _SABLE_GUI_COMMON_RENDERPASS_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/ManagedObject/Ref.h>
#include <Sable/Core/Collection/Header.h>
#include <Sable/Core/String/StaticString.h>
#include <Sable/Gui/Widget/Header.h>
#include <Sable/Gui/Cursor/Header.h>
#include <Sable/Input/Mouse/Header.h>
#include <Sable/Graphics/Common/Manager.h>
#include <Sable/Graphics/Renderer/Header.h>
#include <Sable/Graphics/RenderPass/RenderPass.h>
#include <Sable/Graphics/Texture/Header.h>
#include <Sable/Graphics/Geometry/Header.h>
#include <Sable/Graphics/Text/Text.h>
#include <Sable/Graphics/States/Header.h>
#include <Sable/Core/Event/Header.h>
#include <Sable/Core/Debug/Header.h>
#include <Sable/Input/Keyboard/Event.h>

namespace Sable
{

class CRenderer;
class CWidget;
class CTextFont;
class CLayoutItem;

/**  
\ingroup UserInterface
UI Manager class.
*/
class CGuiRenderPass : public CRenderPass
{

    DEFINE_MANAGED_CLASS( CGuiRenderPass );

public:

	/** @name DataTypes*/
	//@{
    //@}

    /** @name Constructor/destructor */
    //@{
    CGuiRenderPass(CRenderer& renderer );
    virtual ~CGuiRenderPass();
    //@}

    /** @name Operator*/
    //@{
    //@}

    /** @name Accessors*/
    //@{
    Void                ShowCursor( Bool onOff );
    Void                ShowFps( Bool onOff );
	Void				ShowProfView( Bool onOff );
	Void				ShowMemView( Bool onOff );
	CShader&            GetShader() ;
    CCursor&            GetCursor() const;	
    //@}

    /** @name Manipulator*/
    //@{
    Void                DrawQuad( CShader& shader, const CRect2Di& rect, const CColor& color = CColor(1,1,1,1));
    Void                DrawBeveledQuad( CShader& shader, const CRect2Di& rect, const UInt8 bevelSize,const CColor& color,const CColor& bevelColor );
    Void                Update();
    Void                Initialize( CRenderer& renderer, CRenderTarget* outputRenderTarget = NULL );

    Bool                ProcessTraversedNode( CNode& node, CRenderer& renderer );
    Void                Render( CRenderer& renderer );
    //@}

    /** @name Signal*/
    //@{
    //@}

protected:

    // Protected methods

private:

    // Data types
    struct SVertex
    {
        CVector3f Position;
        CVector2f TexCoord0;
    };

    // Methods
	Void OnKeyboardEvent( EKeyboardEventType type, EKeyboardEventData data );
    Void OnMouseEvent( EMouseEventType type, EMouseEventData data, const CVector2f& pos );
    Void InitVertexBuffer();
    Void MouseDown(const CVector2i& pos, const EMouseEventData data );
    Void MouseUp(const CVector2i& pos, const EMouseEventData data );
    Void MouseMove(const CVector2i& pos, const EMouseEventData data );
    Void SortWidgetTable( Int32 l, Int32 r );
	Void AddToWidgetTable( CWidget& w );
	Bool ProcessTraversedLayout( CLayoutItem& node, CRenderer& renderer );

    // Attributes
	CStatesRasterizer				m_StatesRasterizer;
	CStatesDepthStencil				m_StatesDepthStencil;
	CStatesBlend					m_StatesBlend;
	CStatesSampler					m_StateSampler;
    CGeometryVertexBuffer			m_VertexBuffer;
	CGeometryVertexLayout			m_VertexLayout;
    CShader							m_Shader;

    CRef<CCursor>                   m_Cursor;
    Bool                            m_ShowCursor;

	CText							m_FpsText;
    Bool                            m_ShowFps;

	Bool							m_ShowProfView;
	CDebugProfView					m_ProfView;
	CText							m_ProfViewText;

	Bool							m_ShowMemView;
	CDebugMemoryView				m_MemView;
	CText							m_MemViewText;

	mutable CVector2f				m_Resolution;

	CArray< CWidget* >				m_WidgetTable;
	UInt32							m_WidgetTableSize;

    CEventSlot<CGuiRenderPass, EMouseEventType, EMouseEventData, const CVector2f& > m_SlotMouseEvent;
    CEventSlot<CGuiRenderPass, EKeyboardEventType, EKeyboardEventData> m_SlotKeyboardEvent;


};

/**
Get used cursor if any
*/
Inline
CCursor& CGuiRenderPass::GetCursor() const
{
    return *m_Cursor;
}

/**
Return a default shader used for UI display.
*/
Inline
CShader& CGuiRenderPass::GetShader()
{
    return m_Shader;
}

}

#endif
