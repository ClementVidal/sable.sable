#include <Sable/Physic/Shape/Sphere.h>

using namespace Sable;

CPhysicShapeSphere::CPhysicShapeSphere()
{
}

CPhysicShapeSphere::~CPhysicShapeSphere()
{
}

Void CPhysicShapeSphere::SetRadius( Float32 r )
{
    NXShapeDesc.radius = r;
}

NxShapeDesc& CPhysicShapeSphere::GetNxShapeDesc()
{
    return NXShapeDesc;
}