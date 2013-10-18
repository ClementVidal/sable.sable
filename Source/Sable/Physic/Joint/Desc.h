#ifndef _SABLE_PHYSIC_JOINT_DESC_
#define _SABLE_PHYSIC_JOINT_DESC_

#include <Sable/Core/Common/DataTypes.h>

#include <NxJointDesc.h> 

namespace Sable
{

class CPhysicActor;

/** 
\ingroup PhysicJoint
Physic joint base class
*/
class CPhysicJointDesc 
{

public:

    /** @name Constructor/Destructor*/
    //@{
    CPhysicJointDesc() ;
    virtual ~CPhysicJointDesc() ;
    //@}

    /** @name Accessors*/
    //@{
    Void SetGlobalAnchor( const CVector3f& anchor );
    Void SetGlobalAxis( const CVector3f& axis );
    Void SetActor( UInt8 id, CPhysicActor* actor );
    Void SetActors( CPhysicActor* actor1, CPhysicActor* actor2 );
    virtual NxJointDesc& GetNxJointDesc() = 0;
    //@}

    /** @name Manipulator*/
    //@{
    //@}

	// Attributes

private:



};


}

#endif


