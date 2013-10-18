#include <Sable/Physic/Joint/Joint.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS( Sable, CPhysicJoint ) 

CPhysicJoint::CPhysicJoint( CPhysicWorld& world )
{
    m_World = &world;
	UserData = NULL;
}

CPhysicJoint::~CPhysicJoint()
{
	if( NXJoint )
		m_World->NXScene->releaseJoint( *NXJoint );
	NXJoint = NULL;
}
