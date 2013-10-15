#ifndef _SABLE_GRAPHICS_RENDERTARGET_IMPL_DIRECTX_BACKBUFFER_
#define _SABLE_GRAPHICS_RENDERTARGET_IMPL_DIRECTX_BACKBUFFER_

#include <Sable\Graphics\RenderTarget\Impl\Stub\BackBuffer.h>
#include <Sable\Core\Common\DataTypes.h>

struct ID3D10RenderTargetView;
struct ID3D10Texture2D;

namespace Sable
{

class CSwapChain;

/** 
DirectX9 Wrapper for Render Target
*/
class CImplDirectXRenderTargetBackBuffer : public CImplStubRenderTargetBackBuffer
{  

public:

	/* @name Constructor/Destructor*/
	//@{
	CImplDirectXRenderTargetBackBuffer( CRenderTargetBackBuffer& publicImpl );
	~CImplDirectXRenderTargetBackBuffer();
	//@}

	/* @name Mutator*/
	//@{
	//@}

	/* @name Manipulator*/
	//@{
	Void		Activate( Int32 index );
	Void		Initialize( );
    Void        Clear( const CColor& col );
	Void		Resize( const CVector2i& newSize );
	//@}

private:

	// Friendship
	friend class CImplDirectXSwapChain;

	//Method

	//Attribute
    ID3D10RenderTargetView*     m_RenderTargetView;
    ID3D10Texture2D*            m_Texture;

	//Static method

};

}
#endif
