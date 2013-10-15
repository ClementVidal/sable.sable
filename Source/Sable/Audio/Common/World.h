#ifndef _SABLE_AUDIO_COMMON_WORLD_
#define _SABLE_AUDIO_COMMON_WORLD_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\ManagedObject\ManagedObject.h>
#include <Sable\Core\ManagedObject\Ref.h>
#include <Sable\Audio\Common\Listener.h>

namespace Sable
{

/** 
\ingroup AudioCommon
Audio world
*/
class CAudioWorld : public CManagedObject
{

    DEFINE_MANAGED_CLASS( CAudioWorld );

public:

	/** @name Constructor/Destructor*/
	//@{
	CAudioWorld( );
	virtual ~CAudioWorld();
	//@}

	/** @name Operator*/
	//@{
	//@}

	/** @name Accessors*/
	//@{
    CAudioListener& GetListener();
    //@}

	/** @name Manipulator*/
	//@{
    Void            Update( );
	//@}

    // Attributes

private:

    // Methods

    // Attributes
    CRef<CAudioListener>    m_Listener;

};


}

#endif


