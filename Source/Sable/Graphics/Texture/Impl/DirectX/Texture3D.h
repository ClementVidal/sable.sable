#ifndef _SABLE_GRAPHICS_TEXTURE_IMPL_DIRECTX_TEXTURE3D_
#define _SABLE_GRAPHICS_TEXTURE_IMPL_DIRECTX_TEXTURE3D_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Graphics\Texture\Impl\Stub\Texture3D.h>

struct ID3D10Texture3D;

namespace Sable
{

/** 
Interface Wrapper for both static and dynamic index buffer	 
*/
class CImplDirectXTexture3D : public CImplStubTexture3D
{

public:

	/** @name Constructor/Destructor*/
	//@{
	CImplDirectXTexture3D();
	~CImplDirectXTexture3D();
	//@}

	/** @name Accessors*/
	//@{
    //@}

	/** @name Accessors*/
	//@{
	ID3D10Texture3D* 			GetD3D3DTexture() const;
	ID3D10ShaderResourceView*	GetD3DTextureShaderView() const;
	//@}

	/** @name Manipulator*/
	//@{
	Void	Initialize( const CTextureInfo& info, const Byte* data );
	//@}

private:

	// Attributes
	ID3D10Texture3D*		        m_Texture;
	UInt32							m_Width;
	UInt32							m_Height;
	UInt32							m_SliceCount;

};

Inline
ID3D10Texture3D* CImplDirectXTexture3D::GetD3D3DTexture() const
{
	return m_Texture;
}

}

#endif
