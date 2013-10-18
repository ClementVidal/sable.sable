#ifndef _CORE_GEOMETRY_DISK_
#define _CORE_GEOMETRY_DISK_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/Geometry/Plane.h>

namespace Sable
{

class CRay;

/** 
\ingroup CoreGeometry
Represent a disk in 3D space.
The disk is represented by a normal, a radius and an origin.
*/
class CDisk 
{

public:

	/** @name Constructor/Destructor*/
	//@{
	CDisk();
	CDisk( const CVector3f& normal, const CVector3f& origin, const Float32 radius);
	virtual ~CDisk();
	//@}

	/** @name Operator*/
	//@{
	//@}

	/** @name Accessors*/
	//@{
	Void Set( const CVector3f& normal, const CVector3f& origin, const Float32 radius);
	Void SetNormal( const CVector3f& normal );
	Void SetOrigin( const CVector3f& origin );
	Void SetRadius( const Float32 radius);
	const CVector3f& GetNormal( ) const;
	const CVector3f& GetOrigin( ) const;
	const Float32 GetRadius( ) const;
	//@}

	/** @name Manipulator*/
	//@{
	Void		Transform(const CMatrix4x4f& matrix);
	Float32		Intersect( const CRay& ray ) const;
	//@}

private:

	// Attributes
	CVector3f m_Normal;
    CVector3f m_Origin;
	Float32 m_Radius;
};

Inline
Void CDisk::SetNormal( const CVector3f& normal )
{
	m_Normal = normal;
}

Inline
Void CDisk::SetOrigin( const CVector3f& origin )
{
    m_Origin = origin;
}

Inline
const CVector3f& CDisk::GetNormal( ) const
{
	return m_Normal;
}

Inline
const CVector3f& CDisk::GetOrigin( ) const
{
	return m_Origin;
}

Inline
const Float32 CDisk::GetRadius( ) const
{
	return m_Radius;
}

Inline
Void CDisk::SetRadius(const Float32 radius) 
{
	m_Radius = radius;
}

}

#endif


