#ifndef _SABLE_CORE_GEOMETRY_PLANE_
#define _SABLE_CORE_GEOMETRY_PLANE_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\Math\Vector4f.h>

namespace Sable
{

class CSphere;
class CRay;

/** 
\ingroup CoreGeometry
Geometric Plane
*/
class CPlane 
{

public:

	/** @name Constructor/Destructor*/
	//@{
	CPlane();
    CPlane( Float32 a, Float32 b, Float32 c, Float32 d );
    CPlane( const CVector3f& pos, const CVector3f& norm );
    CPlane( const CVector3f& a, const CVector3f& b, const CVector3f& c  );
	~CPlane();
	//@}

	/** @name Operator*/
	//@{
	//@}

	/** @name Accessors*/
	//@{
	CVector3f GetNormal() const;
	Void	Set( Float32 a, Float32 b, Float32 c, Float32 d );
	Void	Set( const CVector3f& pos, const CVector3f& norm );
	Void	Set( const CVector3f& a, const CVector3f& b, const CVector3f& c  );
	//@}

	/** @name Manipulator*/
	//@{
	Bool		OrthogonalProjection( const CVector3f& point, CVector3f& projectedPoint );
	Bool		IsNormalized( ) const;
	Void		Transform(const CMatrix4x4f& matrix);
	Void		TransformProvidingInvert(const CMatrix4x4f& matrix);
	Float32		Intersect( const CRay& ray ) const;
	Bool		Intersect( const CPlane& other ) const;
	Int32		Intersect( const CSphere& other ) const;
	Void		Normalize( );
	//@}

private:

	// Attributes
	CVector4f	m_Coef;
};

}

#endif


