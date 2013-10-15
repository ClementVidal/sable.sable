#include <Sable\Application\Application.h>

#include <Sable\\Application\WindowStandAlone.h>
#include <Sable\Input\Mouse\Mouse.h>
#include <Sable\Input\Keyboard\Keyboard.h>
#include <Sable\Input\Pad\Pad.h>

#include <Sable\Application\Window.h>
#include <Sable\Game\Script\Engine.h>

using namespace Sable;

CApplication::CApplication() :
#ifdef SETUP_PACKAGE_SABLE_GRAPHICS
    m_GraphicsManager( ),
#endif

#ifdef SETUP_PACKAGE_SABLE_INPUT
    m_InputManager( ),
#endif
    m_CoreManager( )
{

}

CApplication::~CApplication()
{
    UnInitialize();
}

CImplApplication& CApplication::GetImpl()
{
    return m_Impl;
}

Void CApplication::UnInitialize()
{
    for( UInt32 i=0;i<16;i++ )
    {
        m_WindowTable[i] = NULL;
    }

#ifdef SETUP_PACKAGE_SABLE_GRAPHICS
    m_GraphicsManager.UnInitialize();
#endif

#ifdef SETUP_PACKAGE_SABLE_INPUT
    m_InputManager.UnInitialize();
#endif
    
#ifdef SETUP_PACKAGE_SABLE_PHYSIC
    m_PhysicManager.UnInitialize();
#endif
    
#ifdef SETUP_PACKAGE_SABLE_AUDIO
    m_AudioManager.UnInitialize();
#endif

}

CApplicationWindow* CApplication::Initialize( CSwapChainInfo* mainWindowInfo )
{
	CApplicationWindow* window = NULL;

    m_Impl.Initialize( *this );

#ifdef SETUP_PACKAGE_SABLE_GRAPHICS
     m_GraphicsManager.Initialize( );
#endif

#ifdef SETUP_PACKAGE_SABLE_INPUT
    m_InputManager.Initialize( );
#endif
    
#ifdef SETUP_PACKAGE_SABLE_PHYSIC
    m_PhysicManager.Initialize();
#endif

#ifdef SETUP_PACKAGE_SABLE_AUDIO
    m_AudioManager.Initialize();
#endif

	return window;
}

Bool CApplication::Update()
{
	m_CoreManager.Update();

#ifdef SETUP_PACKAGE_SABLE_INPUT
	m_InputManager.Update();
#endif

#ifdef SETUP_PACKAGE_SABLE_GRAPHICS
	m_GraphicsManager.Update();
#endif

#ifdef SETUP_PACKAGE_SABLE_PHYSIC
	m_PhysicManager.Update();
#endif

#ifdef SETUP_PACKAGE_SABLE_AUDIO
	m_AudioManager.Update();
#endif

    {
        for( UInt32 i=0;i<16;i++ )
        {
            if( m_WindowTable[i] ) 
                if( ! m_WindowTable[i]->Update() )
                    return FALSE;
        }
    }
	return TRUE;
}

Void CApplication::AddWindow( CApplicationWindow& window )
{
    UInt32 i =0;
    while( m_WindowTable[i] && i < 16)
    {
        i++;
    }

    DebugAssert( i< 16 );
    m_WindowTable[i] = &window;
}

CApplicationWindow* CApplication::GetWindowByHandle( UInt32 handle ) const
{
	for( UInt32 i=0;i<16;i++ )
	{
		if( m_WindowTable[i] ) 
			if( m_WindowTable[i]->GetHandle() == handle )
				return m_WindowTable[i];
	}
	return NULL;
}

CApplicationWindow* CApplication::GetWindow( UInt32 index ) const
{
    return m_WindowTable[index];
}
