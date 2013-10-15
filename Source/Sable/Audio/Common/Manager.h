#ifndef _SABLE_AUDIO_COMMON_MANAGER_
#define _SABLE_AUDIO_COMMON_MANAGER_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\ManagedObject\Singleton.h>
#include <Sable\Core\ManagedObject\Ref.h>
#include <Sable\Setup.h>

#include <alc.h>

#define		AudioManager  Sable::CAudioManager::GetInstance()

namespace Sable
{

class CAudioWorld;

/** 
\ingroup AudioCommon
Audio manager
*/
class CAudioManager : public CSingleton<CAudioManager>
{

public:

	/** @name Constructor/Destructor*/
	//@{
	CAudioManager();
	virtual ~CAudioManager();
	//@}

	/** @name Operator*/
	//@{
	//@}

	/** @name Accessors*/
	//@{
    ALCdevice&  GetDevice() const;
    Void        SetWorld( CAudioWorld* world );
    //@}

	/** @name Manipulator*/
	//@{
    Void        Initialize();
    Void        UnInitialize();
    Void        Update();
	//@}

	// Attributes

private:

    // Attributes
    CRef<CAudioWorld>       m_World;
    ALCdevice*              m_OALDevice;
    ALCcontext*             m_OALContext;
};


}

#endif


