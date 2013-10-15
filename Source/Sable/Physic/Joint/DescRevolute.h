#ifndef _SABLE_PHYSIC_JOINT_DESCREVOLUTE_
#define _SABLE_PHYSIC_JOINT_DESCREVOLUTE_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\Math\Vector3f.h>
#include <Sable\Physic\Joint\Desc.h>
#include <Sable\Core\Math\Range.h>

#include <NxRevoluteJointDesc.h> 
#include <NxJointDesc.h> 

namespace Sable
{

/** 
\ingroup PhysicJoint
Revolute joint descriptor
*/
class CPhysicJointDescRevolute : public CPhysicJointDesc
{

public:

    /** @name Constructor/Destructor*/
    //@{
    CPhysicJointDescRevolute();
    ~CPhysicJointDescRevolute();
    //@}

    /** @name Accessors*/
    //@{
    Void        SetSpring( Float32 spring, Float32 damper, Float32 targetValue );
    Void        SetLimit( const CFloat32Range* range );
    NxJointDesc& GetNxJointDesc();
    //@}

    /** @name Manipulator*/
    //@{
    //@}

	// Attributes
    NxRevoluteJointDesc       NXJointDesc;

private:



};


}

#endif


