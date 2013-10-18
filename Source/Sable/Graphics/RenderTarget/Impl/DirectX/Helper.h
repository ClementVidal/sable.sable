#ifndef _SABLE_GRAPHICS_RENDERTARGET_IMPL_MSW_HELPER_
#define _SABLE_GRAPHICS_RENDERTARGET_IMPL_MSW_HELPER_

#include <Sable/Core/Common/DataTypes.h>

struct ID3D10RenderTargetView;
struct ID3D10DepthStencilView;

namespace Sable
{

class CImplDirectXRenderTargetHelper
{
public:

    CImplDirectXRenderTargetHelper();
    ~CImplDirectXRenderTargetHelper();

    Void ActivateRenderTarget( UInt32 index, ID3D10RenderTargetView** rt );
    Void ActivatedepthStencil( ID3D10DepthStencilView** rt );
    Void Flush();

    ID3D10RenderTargetView**  ActiveRenderTarget[8];
    ID3D10DepthStencilView**  ActiveDepthStencil;

};

}

#endif