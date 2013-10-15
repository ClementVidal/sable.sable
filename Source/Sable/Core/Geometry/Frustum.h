#ifndef _SABLE_CORE_GEOMETRY_FRUSTUM_
#define _SABLE_CORE_GEOMETRY_FRUSTUM_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\Geometry\Sphere.h>
#include <Sable\Core\Geometry\Plane.h>

namespace Sable
{

/** 
\ingroup CoreGeometry
Geometric frustum
*/
class CFrustum 
{

public:

	/** @name DataTypes*/
	//@{
	enum EPlane
	{
		nPlane_Near = 0,
		nPlane_Far,
		nPlane_Left,
		nPlane_Right,
		nPlane_Top,
		nPlane_Bottom,
		nPlane_Count
	};
	//@}

	/** @name Constructor/Destructor*/
	//@{
	CFrustum();
	virtual ~CFrustum();
	//@}

	/** @name Operator*/
	//@{
	//@}

	/** @name Manipulator*/
	//@{
	Void		ExtractFrom( const CMatrix4x4f& worldViewMtx );
	Int32	Intersect( const CSphere& s ) const;
	//@}

private:

	// Attributes
	CPlane	m_Planes[nPlane_Count];

};

}

#endif


