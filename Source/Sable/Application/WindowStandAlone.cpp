#include <Sable\Application\WindowStandAlone.h>

using namespace Sable;

CApplicationWindowStandAlone::CApplicationWindowStandAlone() :
    CApplicationWindow( )
{

}

CApplicationWindowStandAlone::~CApplicationWindowStandAlone()
{
}

UInt32 CApplicationWindowStandAlone::GetHandle() const
{
    return m_Impl.GetHandle();
}

Bool CApplicationWindowStandAlone::Initialize( const CSwapChainInfo& swapChainDesc )
{
    m_Impl.Initialize( swapChainDesc.RenderTargetInfo.TextureInfo );
    return CApplicationWindow::Initialize( swapChainDesc );
}

Bool CApplicationWindowStandAlone::Update()
{
    if( CApplicationWindow::Update() )
        return m_Impl.Update();

    return FALSE;
}
