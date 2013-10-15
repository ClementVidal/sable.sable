#ifndef _SABLE_PHYSIC_ACTOR_DESC_
#define _SABLE_PHYSIC_ACTOR_DESC_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\Math\Vector3f.h>

#include <NxActorDesc.h> 

namespace Sable
{

class CPhysicBodyDesc;
class CPhysicShape;
class CSphere;
class CAABox;
class CPlane;

/** 
\ingroup PhysicActor
Physic actor description
*/
class CPhysicActorDesc 
{

public:

    /** @name Constructor/Destructor*/
    //@{
    CPhysicActorDesc();
    virtual ~CPhysicActorDesc();
    //@}

    /** @name Accessors*/
    //@{
    Void SetRigidBody( CPhysicBodyDesc& rb );
    Void SetDensity( Float32 d );
    Void SetWorldTransformation( const CMatrix4x4f& t );
    NxActorDesc& GetNxActorDesc() ;
    //@}

    /** @name Manipulator*/
    //@{
    Void AddShape( CPhysicShape& shape );
    //@}

private:

	// Attributes
    NxActorDesc     NXActorDesc;

};


}

#endif


