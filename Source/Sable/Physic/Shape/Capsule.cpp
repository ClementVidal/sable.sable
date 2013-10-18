#include <Sable/Physic/Shape/Capsule.h>

using namespace Sable;

CPhysicShapeCapsule::CPhysicShapeCapsule()
{
}

CPhysicShapeCapsule::~CPhysicShapeCapsule()
{
}

/**
Radius of the capsule's hemispherical ends and its trunk.
*/
Void CPhysicShapeCapsule::SetRadius( Float32 r )
{
    NXShapeDesc.radius = r;
}

/**
The distance between the two hemispherical ends of the capsule. 
The height is along the capsule's Y axis.
*/
Void CPhysicShapeCapsule::SetHeight( Float32 h )
{
    NXShapeDesc.height = h;
}
    
NxShapeDesc& CPhysicShapeCapsule::GetNxShapeDesc()
{
    return NXShapeDesc;
}