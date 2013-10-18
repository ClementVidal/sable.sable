#include <Sable/Physic/Shape/Box.h>

using namespace Sable;

CPhysicShapeBox::CPhysicShapeBox()
{
}

CPhysicShapeBox::~CPhysicShapeBox()
{
}

/**
The dimensions are the 'radii' of the box, meaning 1/2 extents in x dimension, 
1/2 extents in y dimension, 1/2 extents in z dimension. All three must be positive.
*/
Void CPhysicShapeBox::SetSize( const CVector3f& s )
{
    SetSize( s.GetX(), s.GetY(), s.GetZ() );
}

/**
The dimensions are the 'radii' of the box, meaning 1/2 extents in x dimension, 
1/2 extents in y dimension, 1/2 extents in z dimension. All three must be positive.
*/
Void CPhysicShapeBox::SetSize( Float32 x, Float32 y, Float32 z )
{
    NXShapeDesc.dimensions.x = x;
    NXShapeDesc.dimensions.y = y;
    NXShapeDesc.dimensions.z = z;
}

NxShapeDesc& CPhysicShapeBox::GetNxShapeDesc()
{
    return NXShapeDesc;
}