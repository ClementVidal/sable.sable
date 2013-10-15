#include <Sable\Physic\Joint\DescRevolute.h>

#include <Sable\Physic\Common\Helper.h>

using namespace Sable;

CPhysicJointDescRevolute::CPhysicJointDescRevolute()
{
    NXJointDesc.jointFlags |= NX_JF_VISUALIZATION;
//    NXJointDesc.jointFlags |= NX_JF_COLLISION_ENABLED;
/*
    NXJointDesc.projectionMode = NX_JPM_POINT_MINDIST;
	NXJointDesc.projectionDistance = 1.0f;
	NXJointDesc.projectionAngle = 0.0872f;	//about 5 degrees in radians.
*/
}

CPhysicJointDescRevolute::~CPhysicJointDescRevolute()
{
}

/**
Set the spring coeficients for the joint.

If spring < 0.0f, then spring coeficient are disabled for this particular joint.

\param spring spring coefficient 
\param damper damper coefficient 
\param targetValue target value (angle) of spring where the spring force is zero. 
*/
Void CPhysicJointDescRevolute::SetSpring( Float32 spring, Float32 damper, Float32 targetValue )
{
    if( spring >= 0.0f )
    {
        NxSpringDesc springDesc;

        springDesc.spring = spring;
        springDesc.damper = damper;
        springDesc.targetValue = targetValue;

        NXJointDesc.spring = springDesc;
        NXJointDesc.flags = NXJointDesc.flags | NX_RJF_SPRING_ENABLED;
    }
    else
    {
        NXJointDesc.spring.spring = -1.0f;
        NXJointDesc.spring.damper = -1.0f;
        NXJointDesc.spring.targetValue = -1.0f;
        NXJointDesc.flags = NXJointDesc.flags & ~NX_RJF_SPRING_ENABLED;
    }
}

/** 
Set the rotation limit of the revolute joint.
Values are specified in degree
*/
Void CPhysicJointDescRevolute::SetLimit( const CFloat32Range* range )
{
    if( range )
    {
        NxJointLimitPairDesc limitDesc;

        limitDesc.high.value = (NxReal)MathDegreeToRadian( range->GetHighValue() );
        limitDesc.low.value =  (NxReal)MathDegreeToRadian( range->GetLowValue() );

        NXJointDesc.limit = limitDesc;
        NXJointDesc.flags = NXJointDesc.flags | NX_RJF_LIMIT_ENABLED;
    }
    else
    {
        NXJointDesc.limit.high.value = (NxReal)0.0f;
        NXJointDesc.limit.low.value =  (NxReal)0.0f;
        NXJointDesc.flags = NXJointDesc.flags & ~NX_RJF_LIMIT_ENABLED;
    }
}

NxJointDesc& CPhysicJointDescRevolute::GetNxJointDesc()
{
    return NXJointDesc;
}