#ifndef _SABLE_PHYSIC_SHAPE_BOX_
#define _SABLE_PHYSIC_SHAPE_BOX_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\Math\Vector3f.h>
#include <Sable\Physic\Shape\Shape.h>

#include <NxBoxShapeDesc.h>

namespace Sable
{

/** 
\ingroup PhysicShape
Physic shape box
*/
class CPhysicShapeBox : public CPhysicShape
{

public:

    /** @name Constructor/Destructor*/
    //@{
    CPhysicShapeBox();
    ~CPhysicShapeBox();
    //@}

    /** @name Accessors*/
    //@{
    Void SetSize( const CVector3f& s );
    Void SetSize( Float32 x, Float32 y, Float32 z );
    NxShapeDesc& GetNxShapeDesc() ;
    //@}

    /** @name Manipulator*/
    //@{
    //@}

	// Attributes
    NxBoxShapeDesc      NXShapeDesc;

private:



};


}

#endif


