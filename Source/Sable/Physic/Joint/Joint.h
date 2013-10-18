#ifndef _SABLE_PHYSIC_JOINT_JOINT_
#define _SABLE_PHYSIC_JOINT_JOINT_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/ManagedObject/ManagedObject.h>

#include <NxJoint.h> 

namespace Sable
{

class CPhysicActor;
class CPhysicWorld;

/** 
\ingroup PhysicJoint
Physic joint base class
*/
class CPhysicJoint : public CManagedObject
{

    DEFINE_MANAGED_CLASS( CPhysicJoint )

public:

    /** @name Constructor/Destructor*/
    //@{
    CPhysicJoint( CPhysicWorld& world );
    virtual ~CPhysicJoint();
    //@}

    /** @name Accessors*/
    //@{
    //@}

    /** @name Manipulator*/
    //@{
    //@}

	// Attributes
	Void*			UserData;
    NxJoint*        NXJoint;

private:

    // Attributes
    CPhysicWorld*	m_World;
};


}

#endif


