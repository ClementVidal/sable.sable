#include <Sable/Core/Geometry/Frustum.h>

#include <Sable/Core/Persistent/Archive.h>
#include <Sable/Core/Math/Matrix4x4f.h>

using namespace Sable;

CFrustum::CFrustum()
{

}

CFrustum::~CFrustum()
{
}

/**
Test for sphere intersection.
\return 1 if s in totally inside the frustum, -1 if s is totally outside the frustum, 0 is s intersect the frustum
*/
Int32 CFrustum::Intersect( const CSphere& s ) const
{
	Int32 a,b,c,d,e,f;

	a = m_Planes[nPlane_Left].Intersect( s );
	b = m_Planes[nPlane_Right].Intersect( s );
	c = m_Planes[nPlane_Top].Intersect( s );
	d = m_Planes[nPlane_Bottom].Intersect( s );
	e = m_Planes[nPlane_Near].Intersect( s );
	f = m_Planes[nPlane_Far].Intersect( s );

	if( (a==0) || (b==0) || (c==0) || (d==0) || (e==0) || (f==0) )
		return 0;

	if( (a==1) && (b==1) && (c==1) && (d==1) && (e==1) && (f==1) )
		return 1;

	return -1;
}

Void CFrustum::ExtractFrom( const CMatrix4x4f& worldViewMtx )
{
	m_Planes[nPlane_Left].Set( 
		worldViewMtx._14 + worldViewMtx._11,
		worldViewMtx._24 + worldViewMtx._21,	
		worldViewMtx._34 + worldViewMtx._31,
		worldViewMtx._44 + worldViewMtx._41
		);
	m_Planes[nPlane_Left].Normalize();

	m_Planes[nPlane_Right].Set( 
		worldViewMtx._14 - worldViewMtx._11,
		worldViewMtx._24 - worldViewMtx._21,	
		worldViewMtx._34 - worldViewMtx._31,
		worldViewMtx._44 - worldViewMtx._41
		);
	m_Planes[nPlane_Right].Normalize();

	m_Planes[nPlane_Bottom].Set( 
		worldViewMtx._14 + worldViewMtx._12,
		worldViewMtx._24 + worldViewMtx._22,	
		worldViewMtx._34 + worldViewMtx._32,
		worldViewMtx._44 + worldViewMtx._42
		);
	m_Planes[nPlane_Bottom].Normalize();

	m_Planes[nPlane_Top].Set( 
		worldViewMtx._14 - worldViewMtx._12,
		worldViewMtx._24 - worldViewMtx._22,	
		worldViewMtx._34 - worldViewMtx._32,
		worldViewMtx._44 - worldViewMtx._42
		);
	m_Planes[nPlane_Top].Normalize();

	m_Planes[nPlane_Near].Set( 
		worldViewMtx._13,
		worldViewMtx._23,	
		worldViewMtx._33,
		worldViewMtx._43
		);
	m_Planes[nPlane_Near].Normalize();

	m_Planes[nPlane_Far].Set( 
		worldViewMtx._14 - worldViewMtx._13,
		worldViewMtx._24 - worldViewMtx._23,	
		worldViewMtx._34 - worldViewMtx._33,
		worldViewMtx._44 - worldViewMtx._43
		);
	m_Planes[nPlane_Far].Normalize();
}