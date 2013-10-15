#include <Sable\Graphics\RenderTarget\Impl\DirectX\Helper.h>

#include <Sable\Graphics\Common\Impl\DirectX\GraphicsManagerHelper.h>

using namespace Sable;

CImplDirectXRenderTargetHelper  ImplMswRenderTargetHelper;

CImplDirectXRenderTargetHelper::CImplDirectXRenderTargetHelper()
{
    MemoryFill( ActiveRenderTarget, 0, sizeof( ID3D10RenderTargetView** ) * 8 );
    ActiveDepthStencil = NULL;
}

CImplDirectXRenderTargetHelper::~CImplDirectXRenderTargetHelper()
{

}

Void CImplDirectXRenderTargetHelper::Flush()
{
    ID3D10RenderTargetView* rtView[8];
    UInt32 rtCount = 0;

    for(UInt32 i=0;i<8;i++)
    {
		rtView[i] = NULL;

		if( ActiveRenderTarget[i] )
			rtView[i] = *(ActiveRenderTarget[i]);

        if( rtView[i] )
            rtCount++;
    }

    CImplDirectXGraphicsManagerHelper::GetDevice()->OMSetRenderTargets( rtCount, rtView, *ActiveDepthStencil );

}

Void CImplDirectXRenderTargetHelper::ActivateRenderTarget( UInt32 index, ID3D10RenderTargetView** rt )
{
    ActiveRenderTarget[index] = rt;

    Flush();
}

Void CImplDirectXRenderTargetHelper::ActivatedepthStencil( ID3D10DepthStencilView** rt )
{
    ActiveDepthStencil = rt;

    Flush();
}