#ifndef _SABLE_AUDIO_ACTOR_ACTOR_
#define _SABLE_AUDIO_ACTOR_ACTOR_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\Collection\BitArray.h>
#include <Sable\Core\ManagedObject\Ref.h>
#include <Sable\Core\Math\Vector3f.h>
#include <Sable\Core\ManagedObject\ManagedObject.h>

namespace Sable
{

class CAudioWorld;
class CAudioBuffer;
class CAudioQueue;

/** 
\ingroup AudioActor
Audio actor
*/
class CAudioSource : public CManagedObject
{

    DEFINE_MANAGED_CLASS( CAudioSource )

public:

    /** @name DataTypes*/
    //@{
    enum EState
    {
        nState_Playing = 0,
        nState_Pause
    };
    //@}

    /** @name Constructor/Destructor*/
    //@{
    CAudioSource( CAudioWorld& world );
    virtual ~CAudioSource();
    //@}

    /** @name Accessors*/
    //@{
    UInt32  GetName() const;
    Void    SetIsLooping( Bool onOff );
    Void    SetPitch( Float32 p );
    Void    SetGain( Float32 g );
    Void    SetWorldPosition( const CVector3f& p );
    Void    SetWorldVelocity( const CVector3f& p );
    Void    SetBuffer( CAudioBuffer& buffer );
    Void    SetQueue( CAudioQueue& queue );
    Bool    IsPlaying() const;
    //@}

    /** @name Manipulator*/
    //@{
    Void Play( Bool onOff );
    Void Pause( Bool onOff );
    Void Update();
    //@}

private:

    // Methods

    // Attributes
    CAudioWorld*                m_World;
    CRef<CAudioBuffer>          m_Buffer;
    CRef<CAudioQueue>     m_Queue;
    UInt32                      m_OALName;
    CBitArray32                   m_State;
};


}

#endif


