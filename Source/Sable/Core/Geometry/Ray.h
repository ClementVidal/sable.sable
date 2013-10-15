#ifndef _CORE_GEOMETRY_RAY_
#define _CORE_GEOMETRY_RAY_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\Math\Vector3f.h>

namespace Sable
{

class CSphere;

/** 
\ingroup CoreGeometry
Geometric Ray
*/
class CRay 
{

public:

	/** @name Constructor/Destructor*/
	//@{
	CRay();
	CRay(const CVector3f& origin, const CVector3f& direction);
	virtual ~CRay();
	//@}

	/** @name Operator*/
	//@{
	//@}

	/** @name Accessors*/
	//@{
	//@}

	/** @name Manipulator*/
	//@{
	Void		Transform( const CMatrix4x4f& m ); 
    CVector3f    GetPointAt( Float32 dist ) const;
	Void        SetFromPoints( const CVector3f& pointA, const CVector3f& pointB );
    Void        Normalize();
    //@}

	/** @name Attributes*/
	//@{
	CVector3f	Direction;
	CVector3f	Origin;
	//@}

private:

	// Attributes

};



}

#endif


