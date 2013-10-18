#include <Sable/Physic/Actor/Actor.h>

#include <Sable/Physic/Common/Helper.h>
#include <Sable/Physic/Common/World.h>

#include <Sable/Core/Log/Header.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS( Sable, CPhysicActor )

/**
\note Ctr/Dtr are private.
So user cannot directly create CPhysicActor.
CPhysicActor can ONLY be created via the CSceneWorld::AddActor() 
*/
CPhysicActor::CPhysicActor( CPhysicWorld& world ) 
{
    NXActor = NULL;
    m_World = &world;
	UserData = NULL;
}

/**
\note Ctr/Dtr are private.
So user cannot directly create CPhysicActor.
CPhysicActor can ONLY be created via the CSceneWorld::AddActor() 
*/
CPhysicActor::~CPhysicActor()
{
    if( NXActor )
        m_World->NXScene->releaseActor( *NXActor );
	NXActor = NULL;
}

Void CPhysicActor::SetWorldPosition( const CVector3f& p )
{
    DebugAssert( NXActor );
    NXActor->setGlobalPosition( CPhysicHelper::ConvertVector( p ) );
}

Void CPhysicActor::WakeUp()
{
    DebugAssert( NXActor );
	NXActor->wakeUp();
}

Void CPhysicActor::SetWorldMatrix( const CMatrix4x4f& m )
{
	DebugAssert( NXActor );
	NXActor->setGlobalPose( CPhysicHelper::ConvertMatrix( m ) );
}

/**
Return the current orientation matrix of the actor in world space.
*/
Void CPhysicActor::GetWorldMatrix( CMatrix4x4f& m )
{
    DebugAssert( NXActor );
    CPhysicHelper::ConvertMatrix( NXActor->getGlobalPose( ), m );
}

/**
Return the current world position of the actor
*/
CVector3f CPhysicActor::GetWorldPosition() const
{
    DebugAssert( NXActor );
    return CPhysicHelper::ConvertVector( NXActor->getGlobalPosition() );
}

/**
Sets the linear velocity of the actor.
*/
Void CPhysicActor::SetLinearVelocity( const CVector3f& v )
{
    DebugAssert( NXActor );
    NXActor->setLinearVelocity( CPhysicHelper::ConvertVector( v ) );
}

/**
Get the linear velocity of the actor.
*/
CVector3f CPhysicActor::GetLinearVelocity() const
{
    DebugAssert( NXActor );
    return CPhysicHelper::ConvertVector( NXActor->getLinearVelocity( ) );
}

/**
Sets the angular velocity of the actor.
*/
Void CPhysicActor::SetAngularVelocity( const CVector3f& v )
{
    DebugAssert( NXActor );
    NXActor->setAngularVelocity( CPhysicHelper::ConvertVector( v )  );
}

/**
Get the angulat velocity of the actor.
*/
CVector3f CPhysicActor::GetAngularVelocity() const
{
    DebugAssert( NXActor );
    return CPhysicHelper::ConvertVector( NXActor->getAngularVelocity( ) );
}

/**
Sets the linear damping coefficient. 
Zero represents no damping. The damping coefficient must be nonnegative.
*/
Void CPhysicActor::SetLinearDamping( Float32 d )
{
    DebugAssert( NXActor );
    NXActor->setLinearDamping( d );
}

/**
Gets the linear damping coefficient. 
*/
Float32 CPhysicActor::GetLinearDamping() const
{
    DebugAssert( NXActor );
    return NXActor->getLinearDamping();
}

Void CPhysicActor::SetAngularDamping( Float32 d )
{
	DebugAssert( NXActor );
	return NXActor->setAngularDamping( d );	
}

Float32 CPhysicActor::GetAngularDamping() const
{
	DebugAssert( NXActor );
	return NXActor->getAngularDamping( );
}

Void CPhysicActor::SetSolverIterationCount( UInt32 count )
{
	DebugAssert( NXActor );
	NXActor->setSolverIterationCount( count );
}

Void CPhysicActor::SetMass( Float32 m )
{
	DebugAssert( NXActor );
	NXActor->setMass( m );
}

Float32	CPhysicActor::GetMass()const
{
	DebugAssert( NXActor );
	return NXActor->getMass( );
}

/**
Explicitly put the actor in sleeping mode
*/
Void CPhysicActor::PutToSleep()
{
	DebugAssert( NXActor );
	NXActor->putToSleep();
}

/**
Apply a force to the actor.
The force is specified in world space
*/
Void CPhysicActor::AddLinearForce( const CVector3f& f, Bool wakeUp )
{
    DebugAssert( NXActor );
    NXActor->addForce( CPhysicHelper::ConvertVector( f ), NX_FORCE, wakeUp!=0 );
}

/**
Apply an impulse to the actor.
The impulse is specified in world space
*/
Void CPhysicActor::AddLinearImpulse( const CVector3f& f, Bool wakeUp )
{
    DebugAssert( NXActor );
    NXActor->addForce( CPhysicHelper::ConvertVector( f ), NX_IMPULSE, wakeUp!=0 );
}
