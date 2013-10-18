#include <Sable/Graphics/Common/Manager.h>

#include <Sable/Graphics/Common/Impl/Stub/GraphicsManager.h>

using namespace Sable;

CGraphicsManager::CGraphicsManager( )
{
    m_LastFrameTime = 0.0;
	m_LastFrameDuration = 0.0;
    m_LastAFPSTime = 0.0;
    m_AFPSTemp = 0.0;
    m_AFPSSamples = 0;
    m_AFPS = 0.0;
}

CGraphicsManager::~CGraphicsManager()
{

}

/**
Initialize the graphics manager.\n
- Start the internal timer \n
- Initialize the platform specific graphics wrapper
- Create the main back buffer render target
*/
Void CGraphicsManager::Initialize( )
{
    CList< CRef<CRenderer> >::Iterator it;

    m_Timer.Start();

    // Initialize Display System
    m_Impl.Initialize( *this );

    m_OverlayRenderer.Initialize();

	// Load default font
	m_DefaultFont.Load( CoreManager.GetFileSystem().GetFilePath( "System", "Font/Default.dfnt" ) );	
}

CTextFont& CGraphicsManager::GetDefaultFont()
{
	return m_DefaultFont;
}

Void CGraphicsManager::UnInitialize()
{
    m_OverlayRenderer.UnInitialize();

    //Shutdown DisplaySystem
    GetImpl().UnInitialize();
}

/**
Recompute the average fps
*/
Void CGraphicsManager::RecomputeAFPS()
{
    Float64 time = m_Timer.GetElapsedMilliseconds();

    m_AFPSTemp += GetFPS();
    m_AFPSSamples ++;

    // Update average FPS every 500 milliseconds
    if( time - m_LastAFPSTime >= 500.0 )
    {
        m_AFPS = m_AFPSTemp / m_AFPSSamples;
        m_AFPS = MathClamp( m_AFPS, 0.0f, 1000000.0f );
        m_AFPSTemp = 0.0f;
        m_AFPSSamples = 0;
        m_LastAFPSTime = time;
    }
}

/**
Update the scene before next render.\n
- Call CRenderer::Update for all registered CRenderer
- Update frame timing value
*/
Void CGraphicsManager::Update()
{
	DebugProfile("CGraphicsManager::Update" );

	Float64 currentTime;
    CList< CRef<CRenderer> >::Iterator it;

    RecomputeAFPS();

    currentTime = GetTimer().GetElapsedSeconds();

    if(currentTime<=m_LastFrameTime)
        currentTime = m_LastFrameTime + 0.00001;

    m_LastFrameDuration = currentTime - m_LastFrameTime;
    m_LastFrameTime = currentTime;
}

Void CGraphicsManager::DrawFullScreenQuad( CRenderer& renderer, CShader& shader )
{
    m_OverlayRenderer.Render( renderer, CVector2f( 0.0f, 0.0f ), CVector2f( 1.0f, 1.0f ), shader );
}
