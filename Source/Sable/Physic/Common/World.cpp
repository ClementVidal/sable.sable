#include <Sable\Physic\Common\World.h>

#include <Sable\Graphics\Debug\RenderPass.h>
#include <Sable\Physic\Joint\Header.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS( Sable, CPhysicWorld );

CPhysicWorld::SInfo::SInfo()
{
	DebugRenderer = NULL;
	MaxActorCount = 0;
	MaxJointCount = 0;
}

CPhysicWorld::CPhysicWorld( const SInfo& info ) :
	m_ActorHeap( "PhysicWorld-Actor"),
	m_JointHeap( "PhysicWorld-Joint")
{
    // Create the scene
    NxSceneDesc sceneDesc;

	NxHWVersion hwVersion = PhysicManager.NXSdk->getHWVersion( )  ;
	if( hwVersion == NX_HW_VERSION_ATHENA_1_0 )
	{
		sceneDesc.simType = NX_SIMULATION_HW;
	}
	else
	{
		sceneDesc.simType = NX_SIMULATION_SW;
	}

	sceneDesc.flags = NX_SF_DISABLE_SCENE_MUTEX;
	//sceneDesc.flags |= NX_SF_SIMULATE_SEPARATE_THREAD;
	
    NXScene = PhysicManager.NXSdk->createScene(sceneDesc);
	PhysicManager.NXSdk->setParameter(NX_MAX_ANGULAR_VELOCITY, 1000);

    // Create the default material
    NxMaterial* defaultMaterial = NXScene->getMaterialFromIndex(0); 
    defaultMaterial->setRestitution(0.0);
    defaultMaterial->setStaticFriction(0.00);
    defaultMaterial->setDynamicFriction(1.);
	PhysicManager.NXSdk->setParameter(NX_MAX_ANGULAR_VELOCITY, 1000);

    m_DebugRenderer = info.DebugRenderer;

    m_UseDebugDraw = FALSE;
    if( m_DebugRenderer )
        m_UseDebugDraw = TRUE;

    SetGravity( CVector3f( 0.0f, -9.81f, 0.0f ) );

	NXScene->setTiming( 1.f / 40.f, 1, NX_TIMESTEP_FIXED ); 

	m_JointHeap.Initialize( NULL, info.MaxJointCount, sizeof( CPhysicJoint ), 4 );
	m_ActorHeap.Initialize( NULL, info.MaxActorCount, sizeof( CPhysicActor ), 4 );
}

CPhysicWorld::~CPhysicWorld()
{
	if( PhysicManager.GetWorld() == this )
	{
		PhysicManager.SetWorld( NULL );
	}

    if(NXScene != NULL)     
        PhysicManager.NXSdk->releaseScene(*NXScene);

    NXScene = NULL;
}

Void CPhysicWorld::DebugDraw()
{
    CVector3f a, b, c;
    CColor col;
    if( !m_UseDebugDraw )
        return;

	DebugAssert( m_DebugRenderer );

    m_DebugRenderer->PushViewProjMatrix();

    const NxDebugRenderable& data = *NXScene->getDebugRenderable();

    // Render points
    {
        UInt32 nbPoints = data.getNbPoints();
        if( nbPoints )
        {
            const NxDebugPoint* points = data.getPoints();

            m_DebugRenderer->BeginPointList();
            while(nbPoints--)
            {
                a.SetX( points->p.x );
                a.SetY( points->p.y );
                a.SetZ( points->p.z );

                col.SetFromUInt32Color( points->color );

                m_DebugRenderer->PushColor( col );
                m_DebugRenderer->DrawPoint( a );
                m_DebugRenderer->PopColor();
                points++;
            }
            m_DebugRenderer->EndPointList();
        }
    }
    
    // Render lines
    {
        UInt32 nbLines = data.getNbLines();
        if( nbLines )
        {
            const NxDebugLine* lines = data.getLines();
            
            m_DebugRenderer->BeginLineList();
            while(nbLines--)
            {
                a.SetX( lines->p0.x );
                a.SetY( lines->p0.y );
                a.SetZ( lines->p0.z );
                b.SetX( lines->p1.x );
                b.SetY( lines->p1.y );
                b.SetZ( lines->p1.z );

                col.SetFromUInt32Color( lines->color );

                m_DebugRenderer->PushColor( col );
                m_DebugRenderer->DrawLine( a, b );
                m_DebugRenderer->PopColor();

                lines++;
            }
            m_DebugRenderer->EndLineList();
        }
    }
    
    // Render triangles
    {
        NxU32 nbTris = data.getNbTriangles();
        if( nbTris )
        {
            const NxDebugTriangle* triangles = data.getTriangles();

            m_DebugRenderer->BeginTriangleList();
            while(nbTris--)
            {
                a.SetX( triangles->p0.x );
                a.SetY( triangles->p0.y );
                a.SetZ( triangles->p0.z );

                b.SetX( triangles->p1.x );
                b.SetY( triangles->p1.y );
                b.SetZ( triangles->p1.z );

                c.SetX( triangles->p2.x ) ;
                c.SetY( triangles->p2.y );
                c.SetZ( triangles->p2.z );

                col.SetFromUInt32Color( triangles->color );

                m_DebugRenderer->PushColor( col );
                m_DebugRenderer->DrawTriangle( a, b, c );
                m_DebugRenderer->PopColor();

                triangles++;
            }
            m_DebugRenderer->EndTriangleList();
        }
    }

    m_DebugRenderer->PopViewProjMatrix();

}

Void CPhysicWorld::Update( Float64 delta )
{
	DebugProfile("CPhysicWorld::Update" );

    if( delta < 0.0f )
        return;

    NXScene->simulate( ( NxReal )delta );
    NXScene->flushStream();

    while (!NXScene->fetchResults(NX_RIGID_BODY_FINISHED, false));

    if( m_UseDebugDraw )
        DebugDraw( );
}

Void CPhysicWorld::UseDebugDraw( Bool onOff )
{
    m_UseDebugDraw = onOff;
}

Bool CPhysicWorld::UseDebugDraw( )
{
    return m_UseDebugDraw;
}

CVector3f CPhysicWorld::GetGravity() const
{
    NxVec3 vec;
    NXScene->getGravity( vec );

    CVector3f v;
    CPhysicHelper::ConvertVector( v, vec);
    return v;
}

Void CPhysicWorld::SetGravity( const CVector3f& v ) 
{
    NXScene->setGravity( CPhysicHelper::ConvertVector( CVector3f( 0.0f, -9.81f, 0.0f ) ) );
}

CPhysicActor* CPhysicWorld::AddActor( CPhysicActorDesc& desc )
{
    CPhysicActor* actor = NULL;

    NxActor* nxActor;

    nxActor = NXScene->createActor( desc.GetNxActorDesc() );

    if( nxActor )
    {
        actor = NEWOBJ_EX( &m_ActorHeap , CPhysicActor, ( *this ) );
        actor->NXActor = nxActor;
		actor->NXActor->userData = actor;
    }

    return actor;
}


CPhysicJoint* CPhysicWorld::AddJoint( CPhysicJointDesc& desc )
{
    CPhysicJoint* joint = NULL;

    NxJoint* nxJoint;

    nxJoint = NXScene->createJoint( desc.GetNxJointDesc() );

    if( nxJoint )
    {
        joint = NEWOBJ_EX( &m_JointHeap , CPhysicJoint, ( *this ) );
        joint->NXJoint = nxJoint;
		joint->NXJoint->userData = joint;
    }

    return joint;
}

UInt32 CPhysicWorld::OverlapSphere( const CSphere& s, EPhysicActorType type, UInt32 group, UInt32 bufferSize, CPhysicActor** buffer )
{
	NxShape** nxBuffer = (NxShape**) CoreManager.GetMemoryManager().GetStackHeap().PushMarkerAndAllocate( bufferSize * sizeof( NxShape* ) );

	NxSphere nxSphere;
	nxSphere.center = CPhysicHelper::ConvertVector( s.Center );
	nxSphere.radius = s.Radius;

	NxShapesType nxType = CPhysicHelper::ConvertActorType( type );

	UInt32 r = NXScene->overlapSphereShapes( nxSphere, nxType, bufferSize, nxBuffer, NULL, 0xffffffff, NULL, FALSE );

	UInt32 i, count = 0;

	MemoryFill( buffer, 0, bufferSize * sizeof( CPhysicActor* ) );

	r = MathMin( r, bufferSize );

	for( i=0;i<r;i++ )
	{
		NxActor* actor = &nxBuffer[i]->getActor();
		
		if( actor->getGroup() == group )
		{
			buffer[count] = (CPhysicActor*)actor->userData;
			count++;
		}
	}

	CoreManager.GetMemoryManager().GetStackHeap().PopMarkerAndFree( nxBuffer );
	return count;
}