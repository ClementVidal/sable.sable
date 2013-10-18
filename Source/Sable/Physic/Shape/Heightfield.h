#ifndef _SABLE_PHYSIC_SHAPE_HEIGHTFIELD_
#define _SABLE_PHYSIC_SHAPE_HEIGHTFIELD_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Physic/Shape/Shape.h>

#include <NxHeightFieldShapeDesc.h>

namespace Sable
{

/** 
\ingroup PhysicShape
Physic shape heightfield
*/
class CPhysicShapeHeightfield : public CPhysicShape
{

public:

    /** @name Constructor/Destructor*/
    //@{
    CPhysicShapeHeightfield( const CVector3f& size, UInt32 nbColumns, UInt32 nbRows, UInt16* buffer );
    ~CPhysicShapeHeightfield();
    //@}

    /** @name Accessors*/
    //@{
    NxShapeDesc& GetNxShapeDesc() ;
    //@}

    /** @name Manipulator*/
    //@{
    //@}

	// Attributes
    NxHeightFieldShapeDesc      NXShapeDesc;

private:

    // Methods
    Void NXCreate( const CVector3f& size, UInt32 nbColumns, UInt32 nbRows, UInt16* buffer );

};


}

#endif


