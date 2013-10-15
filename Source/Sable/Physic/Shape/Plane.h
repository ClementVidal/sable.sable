#ifndef _SABLE_PHYSIC_SHAPE_PLANE_
#define _SABLE_PHYSIC_SHAPE_PLANE_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\Math\Vector3f.h>
#include <Sable\Physic\Shape\Shape.h>

#include <Sable\Core\ManagedObject\Ref.h>

#include <NxPlaneShapeDesc.h>

namespace Sable
{

/** 
\ingroup PhysicShape
Physic shape plane
*/
class CPhysicShapePlane : public CPhysicShape
{

public:

    /** @name Constructor/Destructor*/
    //@{
    CPhysicShapePlane();
    ~CPhysicShapePlane();
    //@}

    /** @name Accessors*/
    //@{
    Void SetNormal( const CVector3f& n );
    Void SetDistance( Float32 d );
    NxShapeDesc& GetNxShapeDesc();
    //@}

    /** @name Manipulator*/
    //@{
    //@}

	// Attributes
    NxPlaneShapeDesc      NXShapeDesc;

private:

//    CRef<CNode>     m_Node;

};


}

#endif


