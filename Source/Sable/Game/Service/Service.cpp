#include <Sable/Game/Service/Service.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS( Sable, CGameService );

CGameService::CGameService( )
{
	m_Object = NULL;
}

CGameService::CGameService( CGameObject& obj )
{
	m_Object = &obj;
}

CGameService::~CGameService()
{
}

Void CGameService::Update()
{

}

CGameObject* CGameService::GetObj() const
{
	return m_Object;
}