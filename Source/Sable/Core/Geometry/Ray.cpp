#include <Sable/Core/Geometry/Ray.h>
#include <Sable/Core/Persistent/Archive.h>

using namespace Sable;

CRay::CRay()
{

}

/**
Construct a ray from an origin position and a direction vector
*/
CRay::CRay(const CVector3f& origin, const CVector3f& direction)
{
	Origin = origin;
	Direction = direction;
}

CRay::~CRay()
{
}

/**
Return the coordinate of a point located at a specified distance fromthe ray origin
*/
CVector3f CRay::GetPointAt( Float32 dist ) const
{
    DebugAssert( Direction.IsNormalized() );
    return Origin + Direction * dist;
}

Void CRay::SetFromPoints( const CVector3f& pointA, const CVector3f& pointB )
{
	Origin = pointA;
	Direction = pointB - pointA;
	Direction.Normalize();
}

Void CRay::Normalize()
{
    Direction.Normalize();
}

Void CRay::Transform( const CMatrix4x4f& m )
{
	Direction.Transform( m );
	Origin.TransformPosition( m );
}