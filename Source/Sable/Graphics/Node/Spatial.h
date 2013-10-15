#ifndef _SABLE_GRAPHICS_NODE_SPATIAL_
#define _SABLE_GRAPHICS_NODE_SPATIAL_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\ManagedObject\ManagedObject.h>
#include <Sable\Core\ManagedObject\Macro.h>
#include <Sable\Core\Geometry\AABox.h>
#include <Sable\Core\Geometry\Sphere.h>
#include <Sable\Core\Math\Matrix4x4f.h>
#include <Sable\Core\Collection\BitArray.h>
#include <Sable\Graphics\Node\Node.h>

namespace Sable
{

class CCamera;

/** 
\ingroup GraphicsSceneGraph
Base class for the representation of a spatial node.
\nA spatial node can be located into the world space of the system
using a set of two orientation, a global one, which represent the orientation of the node
in world space and a local orientation which represent the orientation of the node relatively to 
it's parent orientation.
*/
class CNodeSpatial : public CNode
{

	DEFINE_MANAGED_CLASS( CNodeSpatial );

public:

	/** @name Constructor/Destructor*/
	//@{
	CNodeSpatial();
	CNodeSpatial( CNode&  parent );
	virtual ~CNodeSpatial();
	//@}

	/** @name Operator*/
	//@{
	//@}

	/** @name Accessors*/
	//@{
	virtual Void						GetLocalBoundingBox( CAABox& box ) const;
	Void								GetWorldBoundingBox( CAABox& box ) const;
	Void								GetLocalBoundingSphere( CSphere& sphere ) const;
	Void								GetWorldBoundingSphere( CSphere& sphere ) const;

	Bool								GetIsWorldMatrixNew() const ;
	const CMatrix4x4f&					GetInverseWorldMatrix() const ;	
	CMatrix4x4f&						GetLocalMatrix() ;
	virtual const CVector3f&			GetLocalTranslation( ) const;
	virtual Void						SetLocalMatrix(const CMatrix4x4f& matrix) ;
	virtual Void						SetLocalTranslation(const CVector3f& t) ;

	virtual const CVector3f&			GetWorldTranslation( ) const;
	const CMatrix4x4f&					GetLocalMatrix() const ;
	const CMatrix4x4f&					GetWorldMatrix() const ;
	virtual Bool						IsVisible( const CCamera& camera ) const;
	const CVector3f&					GetWorldPosition() const;
	virtual Void						SetParent( CNode* pParent);
	//@}

	/** @name Manipulator*/
	//@{
	Bool				Serialize( CPersistentArchive& ar );
	virtual Bool		Update( );
	virtual Void		PrepareForNextUpdate();
	//@}

protected:

	//Methods
	Void					EvaluateWorldMatrix( );

private:    

	//Types

	//Attributes
	CMatrix4x4f				m_LocalMatrix;
	CMatrix4x4f				m_WorldMatrix;
	CMatrix4x4f				m_InverseWorldMatrix;

};

/** Return the inverse of the world matrix of that node
*/
Inline
const CMatrix4x4f& CNodeSpatial::GetInverseWorldMatrix() const
{
	return m_InverseWorldMatrix;
}

Inline
CMatrix4x4f&	CNodeSpatial::GetLocalMatrix()
{
	SetState( nState_NewLocalMatrix, TRUE );
	return m_LocalMatrix;
}

Inline
const CVector3f& CNodeSpatial::GetLocalTranslation( ) const
{
	return m_LocalMatrix.GetTranslationComponent();
}

Inline
const CVector3f& CNodeSpatial::GetWorldTranslation( ) const
{
	return m_WorldMatrix.GetTranslationComponent();
}

Inline
const CMatrix4x4f& CNodeSpatial::GetLocalMatrix() const
{
	return m_LocalMatrix;
}

Inline
const CMatrix4x4f& CNodeSpatial::GetWorldMatrix() const
{
	return m_WorldMatrix;
}

Inline
Bool CNodeSpatial::GetIsWorldMatrixNew() const
{
	return GetState( nState_NewWorldMatrix );
}

Inline
const CVector3f&	CNodeSpatial::GetWorldPosition() const
{
	return m_WorldMatrix.GetTranslationComponent();
}

Inline
Void CNodeSpatial::GetLocalBoundingBox( CAABox& box ) const
{
	DebugError("Must be implmented in child class" );
}

Inline
Void CNodeSpatial::GetWorldBoundingBox( CAABox& box ) const
{
	GetLocalBoundingBox( box );
	box.Transform( GetWorldMatrix() );
}

Inline
Void CNodeSpatial::GetLocalBoundingSphere( CSphere& sphere ) const
{
	CAABox bbox;
	GetLocalBoundingBox( bbox );
	sphere.SetFromBox( bbox );
}

Inline
Void CNodeSpatial::GetWorldBoundingSphere( CSphere& sphere ) const
{
	CAABox bbox;
	GetWorldBoundingBox( bbox );
	sphere.SetFromBox( bbox );
}


}

#endif
