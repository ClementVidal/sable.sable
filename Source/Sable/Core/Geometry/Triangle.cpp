#include <Sable\Core\Geometry\Triangle.h>

#include <Sable\Core\Persistent\Archive.h>
#include <Sable\Core\Geometry\Ray.h>

using namespace Sable;

CTriangle::CTriangle()
{
}

CTriangle::CTriangle( const CVector3f& a, const CVector3f& b, const CVector3f& c )
{
    Vertices[0] = a;
    Vertices[1] = b;
    Vertices[2] = c;
}

CTriangle::CTriangle( const CVector3f* vertices )
{
    Vertices[0] = vertices[0];
    Vertices[1] = vertices[1];
    Vertices[2] = vertices[2];
}

CTriangle::~CTriangle()
{
}

/**
Test for intersection between a ray and a triangle.

Thomas Moller, Ben trumbore, Fast minimum storage ray/triangle intersection.
http://www.graphics.cornell.edu/pubs/1997/MT97.pdf

\return -1.0f if no intersection found otherwise return the distance from the ray origin to the intersection point
*/
Float32 CTriangle::IntersectWithCulling( const CRay& r )
{
    CVector3f edge1, edge2, tVec, pVec, qVec;
    Float32 det, invDet, t, u, v;

    edge1 = Vertices[1] - Vertices[0];
    edge2 = Vertices[2] - Vertices[0];

    pVec = r.Direction.CrossProduct( edge2 );

    det = edge1.DotProduct( pVec );

    if( det < FLOAT32_ERROR_THRESHOLD )
        return -1.0;

    tVec = r.Origin - Vertices[0];

    u = tVec.DotProduct( pVec );
    if(  u < 0.0f || u > det )
    {
        return -1.0f;
    }

    qVec = tVec.CrossProduct( edge1 );

    v = r.Direction.DotProduct( qVec );
    if(  v < 0.0f || ( u + v ) > det )
    {
        return -1.0f;
    }

    t = edge2.DotProduct( qVec );
    invDet = 1.0f / det;
    t *= invDet;
    u *= invDet;
    v *= invDet;

    return t;
}

Float32 CTriangle::IntersectWithoutCulling( const CRay& r )
{
	CVector3f edge1, edge2, tVec, pVec, qVec;
	Float32 det, invDet, t, u, v;

	edge1 = Vertices[1] - Vertices[0];
	edge2 = Vertices[2] - Vertices[0];

	pVec = r.Direction.CrossProduct( edge2 );

	det = edge1.DotProduct( pVec );

	if( det > -FLOAT32_ERROR_THRESHOLD && det < FLOAT32_ERROR_THRESHOLD )
		return -1.0f;

	invDet = 1.0f / det;

	tVec = r.Origin - Vertices[0];

	u = tVec.DotProduct( pVec ) * invDet;
	if( u < 0.0f || u > 1.0f )
		return -1.0f;

	qVec = tVec.CrossProduct( edge1 );

	v = r.Direction.DotProduct( qVec ) * invDet;
	if( v < 0.0f || u+v > 1.0f )
		return -1.0f;

	t = edge2.DotProduct( qVec ) * invDet;

	return t;
}

const CVector3f& CTriangle::operator[]( const UInt32 i ) const
{
    DebugAssert( i < 3 );
    return Vertices[i];
}

CVector3f& CTriangle::operator[]( const UInt32 i )  
{
    DebugAssert( i < 3 );
    return Vertices[i];
}

CVector3f CTriangle::GetCenter() const
{
    return ( Vertices[0] + Vertices[1] + Vertices[2] ) / 3.0f;
}

