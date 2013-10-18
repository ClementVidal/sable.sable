#ifndef _SABLE_GAME_OBJECT_OBJECT_
#define _SABLE_GAME_OBJECT_OBJECT_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/ManagedObject/ManagedObject.h>
#include <Sable/Game/Property/Property.h>

namespace Sable
{

class CGameService;

/**  
\ingroup Game
GameObject
*/
class CGameObject : public CManagedObject
{

	DEFINE_MANAGED_CLASS( CGameObject );

public:

	/** @name Constructor/destructor */
	//@{
	CGameObject();
	~CGameObject();
	//@}

	/** @name Accessors*/
	//@{
	CGameService*	GetService( const CStringIdentifier& id ) const;
	CGameProperty*	GetParameter( const CStringIdentifier& id ) ;
	//@}

	/** @name Manipulator*/
	//@{
	//@}

private:

	// Friendship
	friend class CGameObjectPrototype;

	// Types
	typedef CHashTable< CStringIdentifier, CRef<CGameService> > ServiceTable;
	typedef CHashTable< CStringIdentifier, CGameProperty >		ParameterTable;

    // Methods

    // Attributes
	ServiceTable	m_ServiceTable;
	ParameterTable	m_ParameterTable;

};

}

#endif
