#include <Sable\Game\Object\Object.h>

#include <Sable\Game\Service\Service.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS( Sable, CGameObject );

CGameObject::CGameObject()
{
}

CGameObject::~CGameObject()
{
}

CGameProperty*	CGameObject::GetParameter( const CStringIdentifier& id )
{
	return m_ParameterTable.GetItemPtr( id );
}


CGameService* CGameObject::GetService( const CStringIdentifier& s ) const
{
	const CRef<CGameService>* srv = m_ServiceTable.GetItemPtr( s );
	if( !srv )
		return NULL;

	return &**srv;
}
