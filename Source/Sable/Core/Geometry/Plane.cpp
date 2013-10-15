#include <Sable\Core\Geometry\Plane.h>

#include <Sable\Core\Persistent\Archive.h>
#include <Sable\Core\Math\Primitives.h>
#include <Sable\Core\Math\Matrix4x4f.h>
#include <Sable\Core\Geometry\Ray.h>
#include <Sable\Core\Geometry\Sphere.h>
 
using namespace Sable;

CPlane::CPlane()
{

}

CPlane::CPlane( Float32 a, Float32 b, Float32 c, Float32 d )
{
    Set( a, b, c, d );
}

CPlane::CPlane( const CVector3f& pos, const CVector3f& norm )
{
    Set( pos, norm );
}

CPlane::CPlane( const CVector3f& a, const CVector3f& b, const CVector3f& c  )
{
    Set( a, b, c );
}

CPlane::~CPlane()
{
}

Bool CPlane::IsNormalized( ) const
{
	const Float32 delta = 0.001f;

	Float32 mag = MathSqrt(m_Coef.GetX() * m_Coef.GetX() + m_Coef.GetY() * m_Coef.GetY() + m_Coef.GetZ() * m_Coef.GetZ());

	if( ( mag < ( 1.0f + delta ) ) && ( mag > ( 1.0f - delta ) ) )
		return TRUE;

	return FALSE;
}

Int32 CPlane::Intersect( const CSphere& s ) const
{
	const CVector3f& c = s.Center;
	DebugAssert( IsNormalized() );

	Float32 r = m_Coef.GetX()*c.GetX() + m_Coef.GetY()*c.GetY() + m_Coef.GetZ()*c.GetZ() + m_Coef.GetW();

	if( r < s.Radius )
	{
		return -1;
	}
	else if( r > s.Radius )
	{
		return 1;
	}

	return 0;
}

/**
Return TRUE, if the ray intersect the plane.
\param ray The input ray
\param intersection the intersection distance from the origin of the ray
\return TRUE if any intersection.
*/
Float32 CPlane::Intersect( const CRay& ray ) const
{
	CVector3f
		origin = ray.Origin, 
		dir = ray.Direction;
	Float32 divider, intersection;

	dir.Normalize();

	// Take line equation as: P = origin + t * dir
	// Then plug line equation into plane equation:
	// a*(origin.x + t*dir.x) + a*(origin.y + t*dir.y) + a*(origin.z + t*dir.z) + d = 0
	// solve for t :
    divider = (m_Coef.GetX()*dir.GetX() + m_Coef.GetY()*dir.GetY() + m_Coef.GetZ()*dir.GetZ());
    if( divider == 0.0f )
        return FALSE;

	intersection = -(m_Coef.GetX()*origin.GetX() + m_Coef.GetY()*origin.GetY() + m_Coef.GetZ()*origin.GetZ() + m_Coef.GetW()) / divider;

	if(intersection < 0.0f)
		return -1.0f;

	return intersection;
}


/**
Return TRUE, if the two plane intersect.
\param other The other plane
\return TRUE if the two plane intersect.
*/
Bool CPlane::Intersect( const CPlane& other ) const
{
	if( MathIsNearlyEqual( GetNormal().DotProduct( other.GetNormal() ),  1.0f ) )
	{
		return FALSE;
	}

	return TRUE;
}

Void CPlane::Transform(const CMatrix4x4f& matrix)
{
	CMatrix4x4f m = matrix;
	m.Invert();
	TransformProvidingInvert( m );
}

Void CPlane::TransformProvidingInvert(const CMatrix4x4f& matrix)
{
	CVector4f v = m_Coef;

	v.Transform( matrix );

	Set( v.GetX(), v.GetY(), v.GetZ(), v.GetW() );

	Normalize();
}

Void CPlane::Set( Float32 a, Float32 b, Float32 c, Float32 d )
{
	m_Coef.SetX(a);
	m_Coef.SetY(b);
	m_Coef.SetZ(c);
	m_Coef.SetW(d);
}

Void CPlane::Normalize( )
{
	Float32 mag = MathSqrt(m_Coef.GetX() * m_Coef.GetX() + m_Coef.GetY() * m_Coef.GetY() + m_Coef.GetZ() * m_Coef.GetZ());
	m_Coef.SetX( m_Coef.GetX() / mag );
	m_Coef.SetY( m_Coef.GetY() / mag );
	m_Coef.SetZ( m_Coef.GetZ() / mag );
	m_Coef.SetW( m_Coef.GetW() / mag );
}

/**
Initialize the plane from 3 points lying on it 
*/
Void CPlane::Set( const CVector3f& a, const CVector3f& b, const CVector3f& c )
{
    CVector3f d1 = a - b;
    CVector3f d2 = c - b;

    Set( a, d1.CrossProduct(d2) );
}

/**
Initialize the plane from a points and a normal vector
*/
Void CPlane::Set( const CVector3f& pos, const CVector3f& norm )
{
	CVector3f n = norm;
	n.Normalize();

	m_Coef.SetX( n.GetX() );
	m_Coef.SetY( n.GetY() );
	m_Coef.SetZ( n.GetZ() );
	m_Coef.SetW(  -(m_Coef.GetX()*pos.GetX() + m_Coef.GetY()*pos.GetY() + m_Coef.GetZ()*pos.GetZ() ) );
}

CVector3f CPlane::GetNormal() const
{
	return CVector3f( m_Coef.GetX(),m_Coef.GetY(),m_Coef.GetZ() );
}

/**
Compute the position of a point projected orthogonally on the plane. (according to the plane's normal)
*/
Bool CPlane::OrthogonalProjection( const CVector3f& point, CVector3f& projectedPoint )
{
	CVector3f planeNormal = GetNormal();

	Float32 nx, ny, nz, px, py, pz, d, distFromPlane, denum;
	nx = m_Coef.GetX();
	ny = m_Coef.GetY();
	nz = m_Coef.GetZ();
	d = m_Coef.GetW();

	px = point.GetX();
	py = point.GetY();
	pz = point.GetZ();
	denum = ( nx*nx + ny*ny + nz*nz );
	if( denum == 0.0f )
		return FALSE;

	distFromPlane = ( nx*px + ny*py + nz*pz + d ) / denum;

	projectedPoint = point - planeNormal * distFromPlane;

	return TRUE;
}
