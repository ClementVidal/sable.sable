#include <Sable/Physic/Joint/Desc.h>

using namespace Sable;

CPhysicJointDesc::CPhysicJointDesc()
{

}

CPhysicJointDesc::~CPhysicJointDesc()
{
}

/**
Set one of the two joint's actors.
*/
Void CPhysicJointDesc::SetActors( CPhysicActor* actor1, CPhysicActor* actor2 )
{
    SetActor( 0, actor1 );
    SetActor( 1, actor2 );
}

/**
Set one of the two joint's actors.
\param id Actore id, could be either 0 or 1
\param actor A Ref to the actor
*/
Void CPhysicJointDesc::SetActor( UInt8 id, CPhysicActor* actor )
{
    if( actor )
        GetNxJointDesc().actor[id] = actor->NXActor;
    else 
        GetNxJointDesc().actor[id] =NULL;
}

/**
Set the joint axis  of rotation using a given world space axis
\warning The actor pointers must already be set!
*/
Void CPhysicJointDesc::SetGlobalAxis( const CVector3f& axis )
{
    GetNxJointDesc().setGlobalAxis( CPhysicHelper::ConvertVector( axis ) );
}

/**
Set the joint point of rotation using a given world space axis
\warning The actor pointers must already be set!
*/
Void CPhysicJointDesc::SetGlobalAnchor( const CVector3f& anchor )
{
    GetNxJointDesc().setGlobalAnchor( CPhysicHelper::ConvertVector( anchor ) );
}