#include <Sable\Graphics\Light\Orthographic.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1( Sable, CLightOrthographic, CLight );

CLightOrthographic::CLightOrthographic():
CLight()
{
}

CLightOrthographic::CLightOrthographic( CLightOrthographic& other):
CLight( other )
{
	DebugError( "Not Implemented" );
}

CLightOrthographic& CLightOrthographic::operator=( const CLightOrthographic& other )
{
	return *this;
}

CLightOrthographic::~CLightOrthographic()
{
}

Bool CLightOrthographic::IsPointUnderInfluence( const CVector3f& point )
{
	return TRUE;
}
