#include <Sable/Core/Geometry/Sphere.h>

#include <Sable/Core/Persistent/Archive.h>
#include <Sable/Core/Geometry/AABox.h>
#include <Sable/Core/Geometry/Ray.h>

using namespace Sable;

CSphere::CSphere()
{
    Radius = 1.0f;
}

CSphere::CSphere( const CVector3f& center, Float32 radius )
{
	Center = center;
	Radius = radius;
}

CSphere::~CSphere()
{
}

CSphere& CSphere::operator = ( const CSphere& other )
{
    Center = other.Center;
	Radius = other.Radius;

	return *this;
}

Void CSphere::SetEmpty( )
{
	Center = CVector3f::Zero;
	Radius = 0.0f;
}

Float32 CSphere::GetRadius() const
{
	return Radius;
}

const CVector3f& CSphere::GetCenter() const
{
	return Center;
}

CVector3f& CSphere::GetCenter() 
{
	return Center;
}

Bool CSphere::IsInside( const CVector3f& point ) const
{
	CVector3f vect;

	vect = point - Center;
	
	if( MathAbs( vect.GetLength() ) <= Radius )
		return TRUE;

	return FALSE;
}

Bool CSphere::Intersect( const CRay& ray ) const
{
	Float32 a,b;

	return Intersect(ray, a,b);
}

Bool CSphere::Intersect( const CRay& ray, Float32& intersection1, Float32& intersection2 ) const
{
	Float32 det, b;
	CVector3f p;

	p = ray.Origin - Center;

	b = -p.DotProduct( ray.Direction );

	det = b * b - p.DotProduct(p) + Radius*Radius;
	if (det<0)
	{
		return FALSE;
	}
	det = MathSqrt(det);
	intersection1 = b - det;
	intersection2 = b + det;

	// intersecting with ray?
	if(intersection2<0) 
		return FALSE;

	if(intersection1<0)
		intersection1=0;

	return TRUE;
}

Void CSphere::SetFromBox( const CAABox& box )
{
	Center = box.GetCenter();
	Radius = box.GetSize().GetLength() / 2.0f;
}

Bool CSphere::Serialize( CPersistentArchive& ar )
{
	if( ar.Serialize( Center, WT("Center") ) )
		if( ar.Serialize( Radius, WT("Radius") ) )
			return TRUE;

	return FALSE;
}

/**
Add a virtual point to the sphere, after that, the sphere will contain this point.
After a call to that method, the radius can't be smaller than before
*/
Void CSphere::AddPoint( const CVector3f& point )
{
	if( IsInside( point ) )
		return;

	Float32 oldRadius = Radius;

	CVector3f d = point - Center;
	CVector3f v = d;
	v.Normalize();

	Center = (point + Center) / 2.0f;
	// Offset the center by radius/2 in order to encompass any possible point previously within the sphere
	Center = Center - v * Radius / 2.0f;
	Radius = ( d.GetLength() + Radius )/ 2.0f;

	DebugAssert( Radius >= oldRadius );
}