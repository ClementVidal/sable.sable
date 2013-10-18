#include <Sable/Core/Geometry/Disk.h>

#include <Sable/Core/Math/Primitives.h>
#include <Sable/Core/Geometry/Ray.h>

using namespace Sable;

CDisk::CDisk()
{
}

CDisk::CDisk( const CVector3f& normal, const CVector3f& origin, const Float32 radius)
{
    Set( normal, origin, radius );
}

CDisk::~CDisk()
{
}

Void CDisk::Set( const CVector3f& normal, const CVector3f& origin, const Float32 radius)
{
	SetNormal( normal );
	SetOrigin( origin );
	SetRadius( radius );
}

/**
Return TRUE, if the ray intersect the Disk.
\param ray The input ray
\param intersection the intersection distance from the origin of the ray
\return TRUE if any intersection.
*/
Float32 CDisk::Intersect( const CRay& ray ) const
{
    CPlane plane;
    plane.Set( m_Origin, m_Normal );

	Float32 d = plane.Intersect( ray );

    if( d > -1.0f )
    {
        CVector3f intersectionPos = ray.GetPointAt( d );
        CVector3f delta = intersectionPos - m_Origin;
        if( delta.GetLength() <= m_Radius )
            return d;
    }

	return -1.0f;
}

Void CDisk::Transform(const CMatrix4x4f& matrix)
{
	m_Origin.TransformPosition(matrix);
    m_Normal.Transform( matrix );
}

