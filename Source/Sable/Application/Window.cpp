#include <Sable\Application\Window.h>

#include <Sable\Graphics\Scene\View.h>
#include <Sable\Graphics\Common\Manager.h>

using namespace Sable;

CApplicationWindow::CApplicationWindow( )
{
}

CApplicationWindow::~CApplicationWindow()
{
}

Void CApplicationWindow::SetRenderer( CRenderer* renderer )
{
    m_Renderer = renderer;
}

CRenderer* CApplicationWindow::GetRenderer() const
{
    return m_Renderer;
}

/**
Resize the window to a given resolution.
This will resize the windows swapchain and the current renderer if any
*/
Void CApplicationWindow::Resize( const CVector2i& newSize )
{
	GetSwapChain().Resize( newSize );
	if( m_Renderer )
		m_Renderer->Resize( newSize );
}

Bool CApplicationWindow::Initialize( const CSwapChainInfo& swapChainDesc )
{
    m_SwapChain.Initialize( *this, swapChainDesc );
    return TRUE;
}

/**
Update and render the content of the attached view into this window
*/
Bool CApplicationWindow::Update()
{
    Bool rt = TRUE;

    if( m_Renderer && m_Renderer->GetView() )
    {
        if( m_Renderer->GetView()->Update() )
        {
			m_SwapChain.Clear( 1.0f, 0, CColor::Blue );

            m_Renderer->Render( m_SwapChain.GetBackBuffer(), m_SwapChain.GetDepthStencil(), m_SwapChain.GetViewport() );

            rt = TRUE;
        }
		else
		{
			rt = FALSE;
		}
    }

    m_SwapChain.Present();

    return rt;
}

CSwapChain& CApplicationWindow::GetSwapChain()
{
    return m_SwapChain;
}
