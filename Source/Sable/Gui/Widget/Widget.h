#ifndef _SABLE_GUI_WIDGET_WIDGET_
#define _SABLE_GUI_WIDGET_WIDGET_

#include <Sable/Core/Common/Header.h>
#include <Sable/Core/Collection/Header.h>
#include <Sable/Core/Geometry/Header.h>
#include <Sable/Graphics/Node/Node.h>
#include <Sable/Input/Mouse/Event.h>
#include <Sable/Core/Math/Header.h>
#include <Sable/Core/Event/Header.h>
#include <Sable/Gui/Common/DataTypes.h>
#include <Sable/Gui/Widget/Event.h>

namespace Sable
{

class CRenderer;
class CWidget;
class CShader;
class CGeometryVertexBuffer;
class CLayout;

/**  
\ingroup UserInterface
Window class.
*/
class CWidget : public CNode
{

	DEFINE_MANAGED_CLASS( CWidget );

public:

	/** @name Constructor/destructor */
	//@{
	CWidget();
	~CWidget();
	//@}

	/** @name Operator*/
	//@{
	//@}

	/** @name Accessors*/
	//@{
    virtual Void			Show( Bool b );
	virtual Bool			IsInside(const CVector2i& pos);
	Bool					IsVisible() const;
	Bool					HasFocus()const;

	virtual CWidget&	    SetPosition( const CVector2i& pos );
	virtual CWidget&	    SetSize( const CVector2i& size );
	virtual CWidget&	    SetStretchFactor( const CVector2i& size );
	virtual CWidget&		SetColor( const CColor& col );
    Void                    SetLayout( CLayout* layout );
    CWidget&                SetDepth( UInt32 d, Bool recursive );
	CWidget&				SetCustomShader( const CShader* shader );
	CWidget&				SetCustomVB( const CGeometryVertexBuffer* vb );
	Void					SetVSizePolicy( ESizePolicy p );
	Void					SetHSizePolicy( ESizePolicy p );

    CLayout*                GetLayout() const;
    const CVector2i&		GetPosition() const ;
    const CVector2i&		GetSize() const;
    UInt32					GetDepth() const;
    const CVector2i&		GetStretchFactor() const;
	ESizePolicy				GetVSizePolicy() const;
	ESizePolicy				GetHSizePolicy() const;

	CShader*				GetCustomShader( ) const;
	CGeometryVertexBuffer*	GetCustomVB( ) const;
	CRect2Di				GetRect( ) const;
	//@}

	/** @name Manipulator*/
    //@{
	virtual Void	    OnMove( const CVector2i& pos );
	virtual Void	    OnResize( const CVector2i& pos );
	virtual Void	    OnCursorEnter( CWidgetEvent& event );
	virtual Void	    OnCursorLeave( CWidgetEvent& event );
	virtual Void	    OnCursorMove( CWidgetEvent& event );
	virtual Void	    OnCursorBtnUp( CWidgetEvent& event );
	virtual Void	    OnCursorBtnDown( CWidgetEvent& event );

	virtual Void	    Render( CRenderer& renderer, CShader& shader );

    Bool                Serialize( CPersistentArchive& ar );

	Void				SendEvent( CWidgetEvent& event );
	//@}

	/** @name Signals*/
	//@{
	CEventSignal<CWidgetEvent&> SignalMouseEnter;
	CEventSignal<CWidgetEvent&> SignalMouseLeave;
	CEventSignal<CWidgetEvent&> SignalMouseBtnUp;
	CEventSignal<CWidgetEvent&> SignalMouseBtnDown;
	//@}

protected:

	// Types

	// Methods
	Void					OnEvent( CWidgetEvent& event );
	Bool					Update( );

	CVector2i				GetPositionRecursive() const ;

    virtual Void            OnAddChild( CWidget& child );

	Void                    SetFocus(const Bool focus);

    // Attributes
	CVector2i					m_Size;
    CVector2i					m_Position;
	CVector2i					m_StretchFactor;
	ESizePolicy					m_VSizePolicy;
	ESizePolicy					m_HSizePolicy;

private:

    // Friendship
    friend class CGuiRenderPass;

    // Methods

    // Attributes
	Bool							m_HasFocus;
	Bool							m_Show;
    Int32							m_ChildCount;
    UInt32							m_Depth;
    CRef<CLayout>                   m_Layout;
	CRef<CShader>					m_CustomShader;
	CRef<CGeometryVertexBuffer>		m_CustomVB;

};

}

#endif
