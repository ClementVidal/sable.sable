#include <Sable/Core/Geometry/AABox.h>

#include <Sable/Core/Persistent/Archive.h>
#include <Sable/Core/Common/BufferVisitor.h>
#include <Sable/Core/Geometry/Plane.h>
#include <Sable/Core/Geometry/Ray.h>

using namespace Sable;

CAABox::CAABox()
{

}

CAABox::CAABox( const CBufferVisitor& bufferVisitor )
{
	UInt32 i=0;
	for(i=0;i<bufferVisitor.GetChunckCount();i++)
	{
		AddPoint( bufferVisitor.GetChunckElement<CVector3f>( i ) );
	}
}

CAABox::~CAABox()
{
}

/**
Compute the intersection between a ray and a aabox.

Amy Williams, Steve Barrus, R. Keith Morley, and Peter Shirley: "An
Efficient and Robust Ray-Box Intersection Algorithm" Journal of graphics
tools, 10(1):49-54, 2005
http://www.cs.utah.edu/~awilliam/box/box.pdf

\return -1.0f if no intersection found otherwise return the distance from the ray origin to the intersection point
*/
Float32 CAABox::Intersect( const CRay& ray ) const
{   
    Float32 tmin, tmax, tymin, tymax, tzmin, tzmax, divX, divY, divZ;

    divX = 1.0f / ray.Direction.GetX();
    if( divX >= 0) 
    {
        tmin = (m_Minimum.GetX() - ray.Origin.GetX()) * divX;
        tmax = (m_Maximum.GetX() - ray.Origin.GetX()) * divX;
    }
    else 
    {
        tmin = (m_Maximum.GetX() - ray.Origin.GetX()) * divX;
        tmax = (m_Minimum.GetX() - ray.Origin.GetX()) * divX;
    }

    divY = 1.0f / ray.Direction.GetY();
    if( divY >= 0 ) 
    {
        tymin = (m_Minimum.GetY() - ray.Origin.GetY()) * divY;
        tymax = (m_Maximum.GetY() - ray.Origin.GetY()) * divY;
    }
    else 
    {
        tymin = (m_Maximum.GetY() - ray.Origin.GetY()) * divY;
        tymax = (m_Minimum.GetY() - ray.Origin.GetY()) * divY;
    }

    if ( (tmin > tymax) || (tymin > tmax) )
        return -1.0f;

    if (tymin > tmin)
        tmin = tymin;

    if (tymax < tmax)
        tmax = tymax;

    divZ = 1.0f / ray.Direction.GetZ();
    if( divZ >= 0 ) 
    {
        tzmin = (m_Minimum.GetZ() - ray.Origin.GetZ()) * divZ;
        tzmax = (m_Maximum.GetZ() - ray.Origin.GetZ()) * divZ;
    }
    else 
    {
        tzmin = (m_Maximum.GetZ() - ray.Origin.GetZ()) * divZ;
        tzmax = (m_Minimum.GetZ() - ray.Origin.GetZ()) * divZ;
    }
    if ( (tmin > tzmax) || (tzmin > tmax) )
        return -1.0f;

    if (tzmin > tmin)
        tmin = tzmin;

    if (tzmax < tmax)
        tmax = tzmax;

    if( tmin < 0.0f )
        return -1.0f;

    return tmin;
}

Void CAABox::SetMinimum( const CVector3f& min )
{
	m_Minimum = min;
}

Void CAABox::SetMaximum( const CVector3f& min )
{
	m_Minimum = min;
}

const CVector3f& CAABox::GetMinimum( ) const
{
	return m_Minimum;
}

const CVector3f& CAABox::GetMaximum( ) const
{
	return m_Maximum;
}

Float32	CAABox::GetXSize() const
{
	return m_Maximum.GetX() - m_Minimum.GetX();
}

Float32	CAABox::GetYSize() const
{
	return m_Maximum.GetY() - m_Minimum.GetY();
}

Float32	CAABox::GetZSize() const
{
	return m_Maximum.GetZ() - m_Minimum.GetZ();
}

CVector3f CAABox::GetSize() const
{
	return m_Maximum - m_Minimum;
}

CVector3f CAABox::GetCenter() const
{
	return ( m_Maximum + m_Minimum ) / 2.0f;
}


Void CAABox::SetEmpty()
{
	m_Maximum = CVector3f::Zero;
	m_Minimum = CVector3f::Zero;
}

Bool CAABox::IsEmpty() const
{
    return m_Maximum == CVector3f::Zero && m_Minimum == CVector3f::Zero;
}

Void CAABox::AddPoint( const CVector3f& point )
{
    if( IsEmpty() )
    {
        m_Minimum = point;
        m_Maximum = point;
    }
    else
    {
	    if ( point.GetX() > m_Maximum.GetX() ) 
		    m_Maximum.SetX( point.GetX() );
	    if ( point.GetY() > m_Maximum.GetY() ) 
		    m_Maximum.SetY( point.GetY() );
	    if ( point.GetZ() > m_Maximum.GetZ() ) 
		    m_Maximum.SetZ( point.GetZ() );
    	
	    if ( point.GetX() < m_Minimum.GetX() ) 
		    m_Minimum.SetX( point.GetX() );
	    if ( point.GetY() < m_Minimum.GetY() ) 
		    m_Minimum.SetY( point.GetY() );
	    if ( point.GetZ() < m_Minimum.GetZ() ) 
		    m_Minimum.SetZ( point.GetZ() );
    }
}

Void CAABox::AddBox( const CAABox& other )
{
	AddPoint( other.GetMaximum() );
	AddPoint( other.GetMinimum() );
}

Bool CAABox::Serialize( CPersistentArchive& ar )
{
	if( ar.Serialize( m_Minimum, WT("Minimum") ) )
		if( ar.Serialize( m_Maximum, WT("Maximum") ) )
			return TRUE;

	return FALSE;
}

Bool CAABox::IsInside( const CVector3f& pos )const
{
    Float32 x = pos.GetX();
    Float32 y = pos.GetY();
    Float32 z = pos.GetZ();

    return  ( x>m_Minimum.GetX()&&x<m_Maximum.GetX() ) &&  
            ( y>m_Minimum.GetY()&&y<m_Maximum.GetY() ) &&  
            ( z>m_Minimum.GetZ()&&z<m_Maximum.GetZ() ) ;
}

Void CAABox::Transform( const CMatrix4x4f& m )
{
	CVector3f size = GetSize()/ 2.0f;
	CVector3f center = GetCenter() ;
	center.TransformPosition( m );

	m_Maximum = center + size;
	m_Minimum = center - size;
}

Void CAABox::Expand( const CVector3f& expand )
{
	m_Maximum = m_Maximum + expand;
	m_Minimum = m_Minimum - expand;
}