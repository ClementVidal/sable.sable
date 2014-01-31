#ifndef _SABLE_APPLICATION_APPLICATION_
#define _SABLE_APPLICATION_APPLICATION_

#include <Sable/Core/Common/DataTypes.h>

#include <Sable/Core/Collection/Array.h>
#include <Sable/Core/Common/Manager.h>
#include <Sable/Core/ManagedObject/Ref.h>

#ifdef SETUP_PACKAGE_SABLE_GRAPHICS
#include <Sable/Graphics/Common/Manager.h>
#endif

#ifdef SETUP_PACKAGE_SABLE_INPUT
#include <Sable/Input/Common/Manager.h>
#endif

#ifdef SETUP_PACKAGE_SABLE_PHYSIC
#include <Sable/Physic/Common/Manager.h>
#endif

#ifdef SETUP_PACKAGE_SABLE_AUDIO
#include <Sable/Audio/Common/Manager.h>
#endif

#ifdef SETUP_PACKAGE_SABLE_GAME
#include <Sable/Game/Common/Context.h>
#endif

#include <Sable/Application/Impl/Header.h>

namespace Sable
{

class CSceneView;
class CApplicationWindow;

/**  
\ingroup Application
*/
class CApplication
{

public:

    /** @name Constructor/destructor */
    //@{
    CApplication();
    virtual ~CApplication();
    //@}

    /** @name Manipulator*/
    //@{
    Void                AddWindow( CApplicationWindow& window );
    CApplicationWindow* Initialize( CSwapChainInfo* mainWindowInfo = NULL );
    Void                UnInitialize();
    Bool                Update();
    //@}

    /** @name Accessors*/
    //@{
    CApplicationWindow* GetWindow( UInt32 index ) const;
    CApplicationWindow* GetWindowByHandle( UInt32 handle ) const;
    CImplApplication&   GetImpl();
    //@}

private:

    //Attribute
    CCoreManager        m_CoreManager;

#ifdef SETUP_PACKAGE_SABLE_INPUT
    CInputManager       m_InputManager;
#endif

#ifdef SETUP_PACKAGE_SABLE_GRAPHICS
    CGraphicsManager    m_GraphicsManager;
#endif

#ifdef SETUP_PACKAGE_SABLE_PHYSIC
    CPhysicManager      m_PhysicManager;
#endif

#ifdef SETUP_PACKAGE_SABLE_AUDIO
    CAudioManager      m_AudioManager;
#endif

#ifdef SETUP_PACKAGE_SABLE_GAME
	CGameContext      m_GameContext;
#endif

    // Impl
    CImplApplication    m_Impl;

    CRef<CApplicationWindow>    m_WindowTable[16];

};

}

#endif
