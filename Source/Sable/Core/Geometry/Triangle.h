#ifndef _SABLE_CORE_GEOMETRY_TRIANGLE_
#define _SABLE_CORE_GEOMETRY_TRIANGLE_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\Math\Vector3f.h>

namespace Sable
{

class CPersistentArchive;
class CRay;

/** 
\ingroup CoreGeometry
Geometric triangle
*/
class CTriangle 
{

public:

	/** @name Constructor/Destructor*/
	//@{
	CTriangle();
	CTriangle( const CVector3f& a, const CVector3f& b, const CVector3f& c );
	CTriangle( const CVector3f* vertices );
	~CTriangle();
	//@}

	/** @name Operator*/
	//@{
    const CVector3f& operator[]( const UInt32 i ) const;
    CVector3f& operator[]( const UInt32 i );
	//@}

	/** @name Accessors*/
	//@{
    CVector3f    GetCenter() const;
	//@}

	/** @name Manipulator*/
	//@{
    Float32 IntersectWithCulling( const CRay& r );
    Float32 IntersectWithoutCulling( const CRay& r );
	Bool    Serialize( CPersistentArchive& ar );
	//@}

	/** @name Attributes*/
	//@{
	CVector3f	Vertices[3];
	//@}

private:

	// Attributes


};

}

#endif


