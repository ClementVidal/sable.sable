#ifndef _SABLE_AUDIO_COMMON_LISTENER_
#define _SABLE_AUDIO_COMMON_LISTENER_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/Math/Vector3f.h>
#include <Sable/Core/ManagedObject/ManagedObject.h>

namespace Sable
{

class CAudioWorld;

/** 
\ingroup AudioCommon
Audio actor
*/
class CAudioListener : public CManagedObject
{

    DEFINE_MANAGED_CLASS( CAudioListener )

public:

    /** @name DataTypes*/
    //@{
    //@}

    /** @name Constructor/Destructor*/
    //@{
    CAudioListener( CAudioWorld& world );
    virtual ~CAudioListener();
    //@}

    /** @name Accessors*/
    //@{
    //@}

    /** @name Manipulator*/
    //@{
    Void SetWorldOrientation( const CVector3f& p );
    Void SetWorldPosition( const CVector3f& p );
    Void SetWorldVelocity( const CVector3f& p );
    //@}

private:

    // Attributes
    CAudioWorld*    m_World;
};


}

#endif


