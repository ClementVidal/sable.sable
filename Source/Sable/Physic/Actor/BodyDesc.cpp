#include <Sable\Physic\Actor\BodyDesc.h>

#include <NxBodyDesc.h>

using namespace Sable;

CPhysicBodyDesc::CPhysicBodyDesc( ) 
{

}

Void CPhysicBodyDesc::UseKinematicMode( Bool onOff )
{
    if( onOff )
    {
        NXBodyDesc.flags |= NX_BF_KINEMATIC;
    }
    else
    {
        NXBodyDesc.flags &= ~NX_BF_KINEMATIC;
    }
}

/**
Use a combination of EPhysicAxis to specify translation constraint.

FrozeTranslationAxis( nPhysicAxis_X | nPhysicAxis_Z )
*/
Void CPhysicBodyDesc::FrozeTranslationAxis( UInt32 mask )
{
    if( mask & nPhysicAxis_X )
        NXBodyDesc.flags |= NX_BF_FROZEN_POS_X;
    else
        NXBodyDesc.flags &= ~NX_BF_FROZEN_POS_X;

    if( mask & nPhysicAxis_Y )
        NXBodyDesc.flags |= NX_BF_FROZEN_POS_Y;
    else
        NXBodyDesc.flags &= ~NX_BF_FROZEN_POS_Y;

    if( mask & nPhysicAxis_Z )
        NXBodyDesc.flags |= NX_BF_FROZEN_POS_Z;
    else
        NXBodyDesc.flags &= ~NX_BF_FROZEN_POS_Z;

}

/**
Use a combination of EPhysicAxis to specify rotation constraint.

FrozeRotationAxis( nPhysicAxis_X | nPhysicAxis_Z )
*/
Void CPhysicBodyDesc::FrozeRotationAxis( UInt32 mask )
{
    if( mask & nPhysicAxis_X )
        NXBodyDesc.flags |= NX_BF_FROZEN_ROT_X;
    else
        NXBodyDesc.flags &= ~NX_BF_FROZEN_ROT_X;

    if( mask & nPhysicAxis_Y )
        NXBodyDesc.flags |= NX_BF_FROZEN_ROT_Y;
    else
        NXBodyDesc.flags &= ~NX_BF_FROZEN_ROT_Y;

    if( mask & nPhysicAxis_Z )
        NXBodyDesc.flags |= NX_BF_FROZEN_ROT_Z;
    else
        NXBodyDesc.flags &= ~NX_BF_FROZEN_ROT_Z;

}