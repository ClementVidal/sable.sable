#ifndef _SABLE_PHYSIC_COMMON_MANAGER_
#define _SABLE_PHYSIC_COMMON_MANAGER_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/ManagedObject/Singleton.h>
#include <Sable/Core/ManagedObject/Ref.h>
#include <Sable/Core/Time/Timer.h>
#include <Sable/Physic/Common/Helper.h>
#include <Sable/Setup.h>

#include <NxPhysics.h>

#define		PhysicManager  Sable::CPhysicManager::GetInstance()

namespace Sable
{

class CPhysicWorld;

/** 
\ingroup Physic
Physic manager
*/
class CPhysicManager : public CSingleton<CPhysicManager>
{

public:

	/** @name Constructor/Destructor*/
	//@{
	CPhysicManager();
	virtual ~CPhysicManager();
	//@}

	/** @name Operator*/
	//@{
	//@}

	/** @name Accessors*/
	//@{
    Void			SetWorld( CPhysicWorld* world );
	CPhysicWorld*	GetWorld() const;
    Void			SetVisualizationScale( Float32 scale );
    //@}

	/** @name Manipulator*/
	//@{
    Void        StartSimulation();
    Void        Initialize();
    Void        UnInitialize();
    Void        Update();
	//@}

	// Attributes
	NxPhysicsSDK* NXSdk;

private:

    // Attributes
    CPhysicAllocator            m_Allocator;
    CPhysicUSerOutputStream     m_UserOutputStream;
    CTimer                      m_Timer;
    Float64                     m_LastFrame;
    CRef<CPhysicWorld>          m_World;

};


}

#endif


