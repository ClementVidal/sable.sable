#ifndef _SABLE_GRAPHICS_RENDERTARGET_IMPL_MSW_DEPTHSTENCIL_
#define _SABLE_GRAPHICS_RENDERTARGET_IMPL_MSW_DEPTHSTENCIL_

#include <Sable/Graphics/RenderTarget/Impl/Stub/DepthStencil.h>
#include <Sable/Core/Common/DataTypes.h>

struct ID3D10Texture2D;
struct ID3D10RenderTargetView;

namespace Sable
{

/** 
DirectX9 Wrapper for Render Target
*/
class CImplDirectXRenderTargetDepthStencil : public CImplStubRenderTargetDepthStencil
{  

public:

	/* @name Constructor/Destructor*/
	//@{
	CImplDirectXRenderTargetDepthStencil( CRenderTargetDepthStencil& publicImpl );
	~CImplDirectXRenderTargetDepthStencil();
	//@}

	/** Operator*/
	//@{
	//@}

	/* @name Mutator*/
	//@{
	ID3D10Texture2D* GetD3DTexture( );
	//@}

	/* @name Manipulator*/
	//@{
	Void		Activate( );
	Void		Initialize( const CRenderTargetInfo& info );
    Void        Clear( Float32 depth, UInt8 stencil );
	Void		Resize( const CVector2i& newSize );
	//@}

private:

	//Method
	friend class CImplDirectXSwapChain;

	//Attribute
	ID3D10Texture2D* m_Texture;
    ID3D10DepthStencilView* m_DepthStencilView;

	//Static method

};

}

#endif

