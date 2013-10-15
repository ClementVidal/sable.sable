#ifndef _SABLE_PHYSIC_SHAPE_CAPSULE_
#define _SABLE_PHYSIC_SHAPE_CAPSULE_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\Math\Vector3f.h>
#include <Sable\Physic\Shape\Shape.h>

#include <NxCapsuleShapeDesc.h>

namespace Sable
{

/** 
\ingroup PhysicShape
Capsule shape descriptor
*/
class CPhysicShapeCapsule : public CPhysicShape
{

public:

    /** @name Constructor/Destructor*/
    //@{
    CPhysicShapeCapsule();
    ~CPhysicShapeCapsule();
    //@}

    /** @name Accessors*/
    //@{
    Void SetRadius( Float32 r );
    Void SetHeight( Float32 h );
    NxShapeDesc& GetNxShapeDesc() ;
    //@}

    /** @name Manipulator*/
    //@{
    //@}

	// Attributes
    NxCapsuleShapeDesc      NXShapeDesc;

private:


};


}

#endif


