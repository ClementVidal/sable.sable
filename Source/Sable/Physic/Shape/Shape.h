#ifndef _SABLE_PHYSIC_SHAPE_SHAPE_
#define _SABLE_PHYSIC_SHAPE_SHAPE_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\ManagedObject\ManagedObject.h>

class NxShapeDesc;

namespace Sable
{

/** 
\ingroup PhysicShape
Physic shape base class
*/
class CPhysicShape : public CManagedObject
{

	DEFINE_MANAGED_CLASS( CPhysicShape );

public:

    /** @name Constructor/Destructor*/
    //@{
    CPhysicShape();
    ~CPhysicShape();
    //@}

    /** @name Accessors*/
    //@{
    Void SetLocalMatrix( const CMatrix4x4f& t );
    virtual NxShapeDesc& GetNxShapeDesc() = 0;
    //@}

    /** @name Manipulator*/
    //@{
    //@}

	// Attributes

private:



};


}

#endif


