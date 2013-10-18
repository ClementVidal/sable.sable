#ifndef _CORE_GEOMETRY_SPHERE_
#define _CORE_GEOMETRY_SPHERE_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/Math/Vector3f.h>

namespace Sable
{

class CPersistentArchive;
class CRay;
class CAABox;

/** 
\ingroup CoreGeometry
Geometric Sphere
*/
class CSphere 
{

public:

	/** @name Constructor/Destructor*/
	//@{
	CSphere();
	CSphere( const CVector3f& center, Float32 radius );
	~CSphere();
	//@}

	/** @name Operator*/
	//@{
	CSphere& operator = ( const CSphere& other );
	//@}

	/** @name Accessors*/
	//@{
	Void				SetEmpty( );
	Void				SetCenter( const CVector3f& pos );
	Void				SetRadius( Float32 radius );
	Float32				GetRadius() const;
	const CVector3f&	GetCenter() const;
	CVector3f&			GetCenter();
	//@}

	/** @name Manipulator*/
	//@{
	Void	AddPoint( const CVector3f& point );
	Void	SetFromBox( const CAABox& box );
	Bool	IsInside( const CVector3f& point ) const;
	Bool	Intersect( const CRay& ray ) const;
	Bool	Intersect( const CRay& ray, Float32& intersection1, Float32& intersection2 ) const;

	Bool	Serialize( CPersistentArchive& ar );
	//@}

	/** @name Attributes*/
	//@{
	CVector3f	Center;
	Float32		Radius;
	//@}

private:

	// Attributes


};

}

#endif


