#ifndef _SABLE_GRAPHICS_RENDERTARGET_IMPL_DIRECTX_TEXTURE_
#define _SABLE_GRAPHICS_RENDERTARGET_IMPL_DIRECTX_TEXTURE_

#include <Sable/Graphics/RenderTarget/Impl/Stub/Texture.h>
#include <Sable/Core/Common/DataTypes.h>

struct ID3D10Texture2D;
struct ID3D10RenderTargetView;

namespace Sable
{

/** 
DirectX9 Wrapper for Render Target
*/
class CImplDirectXRenderTargetTexture : public CImplStubRenderTargetTexture
{  

public:

	/* @name Constructor/Destructor*/
	//@{
	CImplDirectXRenderTargetTexture( CRenderTargetTexture& publicImpl );
	~CImplDirectXRenderTargetTexture();
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
	Void		Activate( Int32 index );
	Void		Initialize( const CRenderTargetInfo& info );
    Void        Clear( const CColor& col );
	//@}

private:

	//Method

	//Attribute
	ID3D10Texture2D* m_Texture;
    ID3D10RenderTargetView* m_RenderTargetView;

	//Static method

};

}

#endif

