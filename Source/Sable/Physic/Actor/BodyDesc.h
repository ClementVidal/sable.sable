#ifndef _SABLE_PHYSIC_ACTOR_BODYDESC_
#define _SABLE_PHYSIC_ACTOR_BODYDESC_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Physic/Common/DataTypes.h>

namespace Sable
{

class CPhysicActorDesc;

/** 
\ingroup PhysicActor
Rigid body attribute descriptor
*/
class CPhysicBodyDesc
{

public:

    /** @name Constructor/Destructor*/
    //@{
    CPhysicBodyDesc();
    //@}

    /** @name Accessors*/
    //@{
    //@}

    /** @name Manipulator*/
    //@{
    Void FrozeTranslationAxis( UInt32 mask );
    Void FrozeRotationAxis( UInt32 mask );
    Void UseKinematicMode( Bool onOff );
    //@}

	// Attributes
	NxBodyDesc      NXBodyDesc;

private:

    // Friendship
    friend CPhysicActorDesc;


};


}

#endif


