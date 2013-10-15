#ifndef _SABLE_GRAPHICS_COMMON_MANAGER_
#define _SABLE_GRAPHICS_COMMON_MANAGER_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\Time\Timer.h>

#include <Sable\Graphics\Common\Header.h>
#include <Sable\Graphics\Common\ScreenQuad.h>
#include <Sable\Graphics\Text\Font.h>
#include <Sable\Graphics\RenderTarget\Header.h>
#include <Sable\Graphics\SwapChain\SwapChain.h>
#include <Sable\Graphics\Renderer\Header.h>
#include <Sable\Core\ManagedObject\Singleton.h>
#include <Sable\Graphics\Common\Impl\Header.h>

namespace Sable
{

class CRenderTargetBackBuffer;
class CRenderer;
class CShader;

#define     GraphicsManager  Sable::CGraphicsManager::GetInstance()

#define     GraphicsManager_DesiredFramePerSecond ( 60.0 )

/**  
\ingroup GraphicsCommon
Display Manager.
*/
class CGraphicsManager : public CSingleton<CGraphicsManager>
{

public:

	/** @name Constructor/destructor */
	//@{
	//@}

    /** @name Constructor/destructor */
    //@{
    CGraphicsManager( );
    virtual ~CGraphicsManager();
    //@}
    
    /** @name Accessors*/
    //@{
	CTextFont&					GetDefaultFont();
    CTimer&                     GetTimer();
    Float64                     GetLastFrameDuration() const;
    Float64                     GetFPSRatio() const;
    Float64                     GetFPS() const;
    Float64                     GetAverageFPS() const;

    CImplGraphicsManager&	    GetImpl();
    //@}

    //@}
    /** @name Manipulator*/
    //@{
    Void                        Update();
    Void                        Initialize( );
    Void                        UnInitialize();
	Void	                    DrawFullScreenQuad( CRenderer& renderer, CShader& shader );
    //@}
    
    /** @name System*/
    //@{
    //@}
    
private:
    
    //Methods
    Void                            RecomputeAFPS();
    
    //Attributes
    CTimer                          m_Timer;
    Float64                         m_LastFrameDuration;
    Float64                         m_LastFrameTime;
    Float64                         m_AFPS;
    Float64                         m_AFPSTemp;
    UInt32                          m_AFPSSamples;
    Float64                         m_LastAFPSTime;
    CScreenQuad		                m_OverlayRenderer;
	CTextFont						m_DefaultFont;

    CImplGraphicsManager            m_Impl;


};

Inline
Float64 CGraphicsManager::GetAverageFPS() const
{
    return m_AFPS;
}

Inline
CImplGraphicsManager&	CGraphicsManager::GetImpl()
{
    return m_Impl;
}

/**
Return a a value between 0 and 1 representing the ratio between the last frame duration and the 
desired frame rate per second represented by GraphicsManager_DesiredFramePerSecond:\n
This value can be used to create frame rate independent movement.
\return GetFPS()/ GraphicsManager_DesiredFramePerSecond
*/
Inline
Float64 CGraphicsManager::GetFPSRatio() const
{
    return GetFPS() / GraphicsManager_DesiredFramePerSecond;
}

/**	
Return the number of frame by second
*/
Inline
Float64 CGraphicsManager::GetFPS() const
{
    return 1.0 / GetLastFrameDuration();
}

/**	
Return the duration in second of the last frame
*/
Inline
Float64 CGraphicsManager::GetLastFrameDuration() const
{
    return m_LastFrameDuration;
}

/**
Return the internal graphics manager.\n
The timer is started as soon as the graphics manager is initialized
*/
Inline
CTimer&	CGraphicsManager::GetTimer() 
{
    return m_Timer;
}

}

#endif
