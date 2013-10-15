#include <Sable\Physic\Shape\Plane.h>

using namespace Sable;

CPhysicShapePlane::CPhysicShapePlane()
{

}

CPhysicShapePlane::~CPhysicShapePlane()
{
}

Void CPhysicShapePlane::SetNormal( const CVector3f& n )
{
    NXShapeDesc.normal.x = n.GetX();
    NXShapeDesc.normal.y = n.GetY();
    NXShapeDesc.normal.z = n.GetZ();
}

Void CPhysicShapePlane::SetDistance( Float32 d )
{
    NXShapeDesc.d = d;
}

NxShapeDesc& CPhysicShapePlane::GetNxShapeDesc()
{
    return NXShapeDesc;
}