#include <Sable/Physic/Common/Manager.h>

#include <Sable/Physic/Common/World.h>

using namespace Sable;

CPhysicManager::CPhysicManager()
{
    m_LastFrame = 0.0f;
}

CPhysicManager::~CPhysicManager()
{
}

Void CPhysicManager::StartSimulation()
{
    m_Timer.Start();
    m_LastFrame = m_Timer.GetElapsedSeconds();
}

Void CPhysicManager::SetWorld( CPhysicWorld* world )
{
    m_World = world;
}

CPhysicWorld* CPhysicManager::GetWorld() const
{
	return m_World;
}

#include <Sable/Graphics/Common/Manager.h>
Void CPhysicManager::Update()
{
	DebugProfile("CPhysicManager::Update" );

	if( !m_Timer.IsStarted() )
       return;

    Float64 deltaTime, currentTime;

    currentTime = m_Timer.GetElapsedSeconds();

    deltaTime = currentTime - m_LastFrame;
    m_LastFrame = currentTime;

    if( m_World )
        m_World->Update( deltaTime  );
}

Void CPhysicManager::Initialize()
{   
    // Initialize PhysicsSDK
    NxPhysicsSDKDesc desc;
    NxSDKCreateError errorCode = NXCE_NO_ERROR;
    NXSdk = NxCreatePhysicsSDK(NX_PHYSICS_SDK_VERSION, &m_Allocator, &m_UserOutputStream, desc, &errorCode);
    if( NXSdk == NULL )
		return;

    NXSdk->setParameter(NX_SKIN_WIDTH, 0.05f);

    NXSdk->setParameter(NX_VISUALIZATION_SCALE, 1);
    NXSdk->setParameter(NX_VISUALIZE_COLLISION_SHAPES, 1);
    NXSdk->setParameter(NX_VISUALIZE_ACTOR_AXES, 1);
    NXSdk->setParameter(NX_VISUALIZE_JOINT_LOCAL_AXES, 1);
    NXSdk->setParameter(NX_VISUALIZE_JOINT_WORLD_AXES, 1);
    NXSdk->setParameter(NX_VISUALIZE_JOINT_LIMITS, 1);
	NXSdk->setParameter(NX_VISUALIZE_FORCE_FIELDS, 1);

    StartSimulation();
}

/**
Define the scale factor used to display the various visual debug information ( joint axis ... )
*/
Void CPhysicManager::SetVisualizationScale( Float32 scale )
{
    if( NXSdk )
		NXSdk->setParameter( NX_VISUALIZATION_SCALE, scale );
}

Void CPhysicManager::UnInitialize()
{
    // Release ref to the world
    // Assert that Physic wolrd will be destroyed right after
    if( m_World )
    {
        DebugAssert( m_World->GetRefCount() == 1 );
        m_World = NULL;
    }

    if(NXSdk != NULL)
    {
        NxReleasePhysicsSDK(NXSdk);
        NXSdk = NULL;
    }
}
