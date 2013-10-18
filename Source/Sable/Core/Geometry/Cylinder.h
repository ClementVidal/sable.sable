#ifndef _SABLE_CORE_GEOMETRY_CYLINDER_
#define _SABLE_CORE_GEOMETRY_CYLINDER_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/Math/Vector3f.h>

namespace Sable
{

class CPersistentArchive;
class CRay;

/** 
\ingroup CoreGeometry
Geometric cylinder
*/
class CCylinder 
{

public:

	/** @name Constructor/Destructor*/
	//@{
	CCylinder();
	~CCylinder();
	//@}

	/** @name Operator*/
	//@{
	//@}

	/** @name Accessors*/
	//@{
    CVector3f GetAxis() const;
    Float32  GetLength() const;
	//@}

	/** @name Manipulator*/
	//@{
    Float32 Intersect( const CRay& r );
	Bool    Serialize( CPersistentArchive& ar );
    Void    Transform(const CMatrix4x4f& matrix);
	//@}

	/** @name Attributes*/
	//@{   
    CVector3f    PointA;
    CVector3f    PointB;
    Float32     Radius;
	//@}

private:

	// Attributes


};

}

#endif


