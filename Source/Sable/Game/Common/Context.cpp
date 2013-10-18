#include <Sable/Game/Common/Context.h>

#include <Sable/Game/Object/Object.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS( Sable, CGameContext );

CGameContext::CGameContext()
{
}

CGameContext::~CGameContext()
{
}

CGameObject* CGameContext::AddObject( const CStringIdentifier& id )
{
	if( m_ObjectTable.HasItem( id ) )
		return NULL;

	CRef<CGameObject> obj = NEWOBJ( CGameObject, () );
	m_ObjectTable.AddItem( id, obj );

	return &*obj;
}

CGameObject* CGameContext::GetObject( const CStringIdentifier& id )
{
	CRef<CGameObject>* obj = m_ObjectTable.GetItemPtr( id );
	if( obj )
		return &(**obj);

	return NULL;
}

Void CGameContext::SendEvent( CGameEvent& event )
{
	ObjectTable::Iterator it;

	ForEachItem( it, m_ObjectTable )
	{
//		(*it)->OnEvent( event );
	}
}
