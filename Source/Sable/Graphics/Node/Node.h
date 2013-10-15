#ifndef _SABLE_GRAPHICS_NODE_NODE_
#define _SABLE_GRAPHICS_NODE_NODE_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\ManagedObject\Ref.h>
#include <Sable\Graphics\Common\DataTypes.h>

namespace Sable
{

class CNode;
class CPersistentArchive;
class CRenderer;

/** 
\ingroup GraphicsSceneGraph
Base class for the representation of a node in the Scene graph.
\nProvide methods for manipulate graph hierarchy
*/
class CNode : public CManagedObject
{

	DEFINE_MANAGED_CLASS( CNode );

public:

	/** @name DatTypes*/
	//@{
	enum EState
	{
		nState_NewLocalMatrix = 1,
		nState_NewWorldMatrix,
	};

	enum EAttribute
	{
		nAttribute_DoNotRenderToDepthBuffer = 1,
		nAttribute_DoNotRender,
        nAttribute_RenderFromFrontToBack,
        nAttribute_RenderFromBacktoFront,
		nAttribute_InheritPosition,
		nAttribute_InheritRotatationAndTranslation,
		nAttribute_InheritAll,	
		nAttribute_CameraAligned
	};
	//@}

    /** @name Constructor/Destructor*/
    //@{
	CNode();
	CNode( CNode& parent );
	~CNode();
    //@}

    /** @name Operator*/
    //@{
    //@}

    /** @name Accessors*/
    //@{
	virtual Void			SetAttribute( EAttribute attrib, Bool onOff );
	Bool					GetAttribute( EAttribute attrib ) const;

	virtual Void			SetParent( CNode* pParent);

	CNode*					GetParent() const;
    CNode*					GetChild() const;
    CNode*					GetSibling() const;

	UInt32					GetChildCount( ) const;
	//\}

    /** @name Manipulator*/
    //@{
    Void                    RemoveAllChilds();
    //@}

	/** @name System */
	//@{
	virtual Bool			RecursiveUpdate( );
	virtual Bool			RecursiveUnInit();
	virtual Void			PrepareForNextUpdate();
    Bool					Serialize( CPersistentArchive& ar );
	//@}

protected:

    //Methods
	virtual Void	AddChild( CNode& childToAdd );
	virtual Void	RemoveChild( CNode& childToRemove );
	virtual Bool	Update( );
    Void	        SetState( EState state, Bool onOff );
    Bool			GetState( EState state ) const;

private:    

    //Types

	//Methods

	//Attributes
	CNode*					m_Parent;
	CRef<CNode>			    m_Child;
    CRef<CNode>				m_Sibling;
	CBitArray32				m_Attributes;
	CBitArray32				m_States;

};

}

#endif
