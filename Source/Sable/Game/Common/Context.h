#ifndef _SABLE_GAME_COMMON_CONTEXT_
#define _SABLE_GAME_COMMON_CONTEXT_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Game/Script/Engine.h>

namespace Sable
{

class CGameObject;
class CGameEvent;

/**  
\ingroup Game
GameContext
*/
class CGameContext : public CManagedObject
{

	DEFINE_MANAGED_CLASS( CGameContext );

public:

	/** @name Constructor/destructor */
	//@{
	CGameContext();
	~CGameContext();
	//@}

	/** @name Accessors*/
	//@{
	CGameObject*	GetObject( const CStringIdentifier& id );
	//@}

	/** @name Manipulator*/
    //@{
	Void	SendEvent( CGameEvent& event );
	Void	Update();
	//@}

private:

	// Friendship
	friend class CGameObjectPrototype;

	// Types
	typedef CHashTable< CStringIdentifier, CRef<CGameObject> > ObjectTable;

	// Methods
	CGameObject*	AddObject( const CStringIdentifier& id );

    // Attributes
	ObjectTable		m_ObjectTable;
	CScriptEngine	m_ScriptEngine;
};

}

#endif
