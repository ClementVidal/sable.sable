#include <Sable/Graphics/Light/Point.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1( Sable, CLightPoint, CLight );

CLightPoint::CLightPoint():
CLight()
{
	m_Radius = 1.0f;
}

CLightPoint::CLightPoint( const CLightPoint& other)
{
	DebugError( "Not Implemented" );
}

CLightPoint& CLightPoint::operator=( const CLightPoint& other )
{
	return *this;
}

CLightPoint::~CLightPoint()
{
}

Bool CLightPoint::IsPointUnderInfluence( const CVector3f& point )
{
	return TRUE;
}
