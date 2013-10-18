#ifndef _SABLE_PHYSIC_SHAPE_SPHERE_
#define _SABLE_PHYSIC_SHAPE_SPHERE_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/Math/Vector3f.h>
#include <Sable/Physic/Shape/Shape.h>

#include <NxSphereShapeDesc.h>

namespace Sable
{

/** 
\ingroup PhysicShape
Physic shape sphere
*/
class CPhysicShapeSphere : public CPhysicShape
{

public:

    /** @name Constructor/Destructor*/
    //@{
    CPhysicShapeSphere();
    ~CPhysicShapeSphere();
    //@}

    /** @name Accessors*/
    //@{
    Void SetRadius( Float32 r );
    NxShapeDesc& GetNxShapeDesc();
    //@}

    /** @name Manipulator*/
    //@{
    //@}

	// Attributes
    NxSphereShapeDesc      NXShapeDesc;

private:



};


}

#endif


