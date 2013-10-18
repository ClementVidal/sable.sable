#include <Sable/Graphics/Light/Perspective.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1( Sable, CLightPerspective, CLight );

CLightPerspective::CLightPerspective():
CLight()
{
	m_OpeningAngle = MathPi;
}

CLightPerspective::CLightPerspective( CNode&  parent ):
CLight( parent )
{
	m_OpeningAngle = MathPi;
}

CLightPerspective::~CLightPerspective()
{
}

Bool CLightPerspective::IsPointUnderInfluence( const CVector3f& point )
{
	return TRUE;
}
