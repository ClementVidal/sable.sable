#include <Sable/Physic/Actor/Desc.h>

#include <Sable/Core/Geometry/Sphere.h>
#include <Sable/Core/Geometry/AABox.h>
#include <Sable/Core/Geometry/Plane.h>

#include <Sable/Physic/Common/Helper.h>
#include <Sable/Physic/Shape/Shape.h>
#include <Sable/Physic/Actor/BodyDesc.h>

#include <NxBoxShapeDesc.h>
#include <NxSphereShapeDesc.h> 
#include <NxPlaneShapeDesc.h> 

using namespace Sable;

CPhysicActorDesc::CPhysicActorDesc( ) 
{
    SetDensity( 1.0f );
}

CPhysicActorDesc::~CPhysicActorDesc()
{
}

Void CPhysicActorDesc::AddShape( CPhysicShape& shape )
{
    NXActorDesc.shapes.push_back( ( NxShapeDesc* ) & shape.GetNxShapeDesc() );
}

Void CPhysicActorDesc::SetRigidBody( CPhysicBodyDesc& rb )
{
    NXActorDesc.body = &rb.NXBodyDesc;
}

Void CPhysicActorDesc::SetDensity( Float32 d )
{
    NXActorDesc.density = d;
}

Void CPhysicActorDesc::SetWorldTransformation( const CMatrix4x4f& t )
{
    NXActorDesc.globalPose = CPhysicHelper::ConvertMatrix( t );
}

NxActorDesc& CPhysicActorDesc::GetNxActorDesc() 
{
    return NXActorDesc;
}