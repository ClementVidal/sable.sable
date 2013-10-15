#include <Sable\Physic\Shape\Shape.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1( Sable, CPhysicShape, CManagedObject );

CPhysicShape::CPhysicShape() :
	CManagedObject()
{
}

CPhysicShape::~CPhysicShape()
{
}

Void CPhysicShape::SetLocalMatrix( const CMatrix4x4f& t )
{
    GetNxShapeDesc().localPose = CPhysicHelper::ConvertMatrix( t );
}