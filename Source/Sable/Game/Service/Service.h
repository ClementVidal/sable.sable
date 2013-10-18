#ifndef _SABLE_GAME_SERVICE_SERVICE_
#define _SABLE_GAME_SERVICE_SERVICE_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/ManagedObject/ManagedObject.h>

namespace Sable
{

class CGameObject;

/**  
\ingroup Game
GameObject
*/
class CGameService : public CManagedObject
{

	DEFINE_MANAGED_CLASS( CGameService );

public:

	/** @name Constructor/destructor */
	//@{
	CGameService( );
	CGameService( CGameObject& obj );
	~CGameService();
	//@}

	/** @name Accessors*/
	//@{
	//@}

	/** @name Manipulator*/
	//@{
	Void	Update();
	//@}

protected:

	// Methods
	CGameObject*	GetObj() const;

private:

	// Types

    // Methods

    // Attributes
	CGameObject*	m_Object;

};

}

#endif
