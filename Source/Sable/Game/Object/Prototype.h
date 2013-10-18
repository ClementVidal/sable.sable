#ifndef _SABLE_GAME_OBJECT_PROTOTYPE_
#define _SABLE_GAME_OBJECT_PROTOTYPE_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/ManagedObject/ManagedObject.h>
#include <Sable/Game/Property/Property.h>

namespace Sable
{

class CGameEvent;
class CGameService;
class CGameContext;

/**  
\ingroup Game
GameObject
*/
class CGameObjectPrototype : public CManagedObject
{

	DEFINE_MANAGED_CLASS( CGameObjectPrototype );

public:

	/** @name Constructor/destructor */
	//@{
	CGameObjectPrototype();
	~CGameObjectPrototype();
	//@}

	/** @name Accessors*/
	//@{
	String			GetScriptCode() const;
	Void			SetScriptCode( const CString& c );
	CGameService*	AddService( const CStringIdentifier& id );
	CGameService*	GetService( const CStringIdentifier& id ) const;
	CGameProperty*	AddParameter( const CStringIdentifier& id ) ;
	CGameProperty*	GetParameter( const CStringIdentifier& id ) ;
	Void			RemoveAllParameter();
	//@}

	/** @name Manipulator*/
	//@{
	CGameObject*	Instanciate( CGameContext& context, const CStringIdentifier& id ) const;
	//@}

private:

	// Types
	typedef CHashTable< CStringIdentifier, CRef<CGameService> > ServiceTable;
	typedef CHashTable< CStringIdentifier, CGameProperty >		ParameterTable;

    // Methods

    // Attributes
	ServiceTable	m_ServiceTable;
	ParameterTable	m_ParameterTable;
	CString			m_ScriptCode;

};

}

#endif
