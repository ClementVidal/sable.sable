#include <Sable/Core/Geometry/Cylinder.h>

#include <Sable/Core/Persistent/Archive.h>
#include <Sable/Core/Geometry/Ray.h>

using namespace Sable;

CCylinder::CCylinder()
{
}


CCylinder::~CCylinder()
{
}

Float32 CCylinder::GetLength() const
{
    return CVector3f( PointB - PointA ).GetLength();
}

CVector3f CCylinder::GetAxis() const
{
    CVector3f tmp = PointB - PointA;
    tmp.Normalize();
    return tmp;
}

Void CCylinder::Transform( const CMatrix4x4f& matrix )
{
    Float32 oldLength = GetLength();
    PointA.TransformPosition( matrix );
    PointB.TransformPosition( matrix );
    Float32 scaleRatio = GetLength()/oldLength;
    Radius = Radius * scaleRatio;
}

/**
"Intersecting a Ray with a Cylinder"
by Joseph M. Cychosz and Warren N. Waggenspack, Jr.,
(3ksnn64@ecn.purdue.edu, mewagg@mewnw.dnet.lsu.edu)
in "Graphics Gems IV", Academic Press, 1994
*/
Float32 CCylinder::Intersect( const CRay& r )
{
    Float32 in, out;
    Bool		hit;		// True if ray intersects cyl
    CVector3f	rc;		    // Ray base to cylinder base
    Float32		dist;		    // Shortest distance between

    Float32		t, s;		// Distances along the ray
    CVector3f	n, o;
    Float32		ln;

    CVector3f axis = GetAxis();
    rc = r.Origin - PointA;
    n.CrossProduct( r.Direction, axis );

    ln = n.GetLength();
    if ( ln == 0.0f ) 
    {	
        CVector3f tmp;
        // ray parallel to cyl
        dist = rc.DotProduct( axis );
        tmp = rc - axis * dist;

        dist = tmp.GetLength();
        in = -FLOAT32_MAX_VAL;
        out =  FLOAT32_MAX_VAL;
        if( dist <= Radius )		// true if ray is in cyl
        {
            return 1.0;
        }
    }

    n.Normalize();
    dist = MathAbs( rc.DotProduct( n ) );		// shortest distance
    hit = (dist <= Radius);

    if  (hit) 
    {	
        // if ray hits cylinder 
        o.CrossProduct( rc, axis );
        t = - o.DotProduct( n ) / ln;
        o.CrossProduct( n, axis );
        o.Normalize();
        s = MathAbs( MathSqrt( Radius*Radius - dist*dist) / r.Direction.DotProduct( o ) );
        in	 = t - s;			// entering distance
        out = t + s;			// exiting  distance

        // Test for capped cylinder
        CVector3f intersection = r.Origin + r.Direction * in;
        CVector3f cylBaseToInter = intersection - PointA;
        ln = cylBaseToInter.GetLength();
        cylBaseToInter.Normalize();

        if( axis.DotProduct( cylBaseToInter ) >= 0.0f )
        {
            Float32 cylLength = CVector3f( PointA-PointB ).GetLength();
            if( ln <= cylLength )
                return in;
        }
		
    }

    return -1.0f;
    
}
