#include <Sable/Graphics/Light/Light.h>

#include <Sable/Graphics/Texture/Texture.h>
#include <Sable/Graphics/Common/Manager.h>
#include <Sable/Graphics/Texture/Texture2D.h>

using namespace Sable;


IMPLEMENT_MANAGED_CLASS1( Sable, CLight, CNodeSpatial );

CLight::CLight( ):
CNodeSpatial()
{
	m_ShadowDepthMap.SetNull();
	m_DiffuseColor = CColor::White;
	m_AmbientColor = CColor::White;
	m_SpecularColor = CColor::White;
}

CLight::CLight( CNode& parent  ):
CNodeSpatial( parent )
{  
	m_ShadowDepthMap.SetNull();
}

CLight::~CLight()
{
}

Void CLight::Activate( const Bool& onoff )
{

}

Float32	CLight::GetIntensityAtPoint( const CVector3f& point )
{
	return 1.0f;
}

Bool CLight::IsPointUnderInfluence( const CVector3f& point )
{
    DebugError( "Must be re implemented" );
    return TRUE;
}