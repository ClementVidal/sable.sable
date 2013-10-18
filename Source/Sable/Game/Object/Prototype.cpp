#include <Sable/Game/Object/Prototype.h>

#include <Sable/Game/Service/Service.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS( Sable, CGameObjectPrototype );

CGameObjectPrototype::CGameObjectPrototype()
{
}

CGameObjectPrototype::~CGameObjectPrototype()
{
}

String CGameObjectPrototype::GetScriptCode() const
{
	return m_ScriptCode;
}

Void CGameObjectPrototype::SetScriptCode( const CString& c )
{
	m_ScriptCode = c;
}

Void CGameObjectPrototype::RemoveAllParameter()
{
	m_ParameterTable.ClearAllItems();
}

CGameProperty*	CGameObjectPrototype::AddParameter( const CStringIdentifier& id )
{
	CGameProperty* p = m_ParameterTable.GetItemPtr( id );
	if( !p )
		p = &m_ParameterTable.AddItem( id );

	return p;
}

CGameProperty*	CGameObjectPrototype::GetParameter( const CStringIdentifier& id )
{
	return m_ParameterTable.GetItemPtr( id );
}

CGameService* CGameObjectPrototype::AddService( const CStringIdentifier& type )
{
	if( m_ServiceTable.HasItem( type ) == FALSE )
		return NULL;

	const CTypeInfo& t = CGameService::GetStaticTypeInfo().GetDerivedClass( type );
	if( t != CTypeInfo::NullType )
	{
		CGameService* s = (CGameService*)t.CreateObject( NULL );
		m_ServiceTable.AddItem( type, s );
		return s;
	}

	return NULL;
}

CGameService* CGameObjectPrototype::GetService( const CStringIdentifier& s ) const
{
	const CRef<CGameService>* srv = m_ServiceTable.GetItemPtr( s );
	if( !srv )
		return NULL;

	return &**srv;
}


CGameObject* CGameObjectPrototype::Instanciate( CGameContext& context, const CStringIdentifier& id ) const
{
	CGameObject* obj = context.AddObject( id );
	if( obj == NULL )
		return NULL;

	return NULL;
}