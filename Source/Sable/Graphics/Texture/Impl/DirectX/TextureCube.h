#ifndef _SABLE_GRAPHICS_TEXTURE_IMPL_DIRECTX_TEXTURECUBE_
#define _SABLE_GRAPHICS_TEXTURE_IMPL_DIRECTX_TEXTURECUBE_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Graphics/Texture/Impl/Stub/TextureCube.h>

struct ID3D10Texture2D;
struct ID3D10ShaderResourceView;

namespace Sable
{

/** 
Interface Wrapper for both static and dynamic index buffer	 
*/
class CImplDirectXTextureCube : public CImplStubTextureCube
{

public:

	/** @name Constructor/Destructor*/
	//@{
	CImplDirectXTextureCube();
	~CImplDirectXTextureCube();
	//@}

	/** @name Operator*/
	//@{
	//@}
	
	/** @name Accessors*/
	//@{
	ID3D10Texture2D* 	GetD3DTexture() const;
	ID3D10ShaderResourceView* GetD3DTextureShaderView() const;
	//@}

	/** @name Manipulator*/
	//@{
	Void	Initialize( const CTextureInfo& info, const Byte* data );
	//@}

private:

	// Attributes
	ID3D10Texture2D*			m_Texture;
	ID3D10ShaderResourceView*	m_ShaderView;
	UInt8						m_CurrentLevelLocked;
    UInt8						m_MipMapLevel;
};

Inline
ID3D10Texture2D* CImplDirectXTextureCube::GetD3DTexture() const
{
	return m_Texture;
}

}

#endif
