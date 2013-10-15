#ifndef _SABLE_GRAPHICS_TEXTURE_IMPL_MSW_TEXTURE2D_
#define _SABLE_GRAPHICS_TEXTURE_IMPL_MSW_TEXTURE2D_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Graphics\Texture\Impl\Stub\Texture2D.h>

struct ID3D10Texture2D;
struct ID3D10ShaderResourceView;

namespace Sable
{

/** 

*/
class CImplDirectXTexture2D : public CImplStubTexture2D
{

public:

	/** @name Constructor/Destructor*/
	//@{
	CImplDirectXTexture2D();
	~CImplDirectXTexture2D();
	//@}

	/** Operator */
	//@{
	//@}

	/** @name Accessors*/
	//@{
	ID3D10Texture2D* 	GetD3DTexture() const;
	ID3D10ShaderResourceView* GetD3DTextureShaderView() const;
	//@}

	/** @name Manipulator*/
	//@{
	Void	Initialize( const CTextureInfo& info, Bool lockable, const Byte* data );
	Void*	Lock( const UInt8 mipmaplevel, const EBufferAcces acces, UInt32& pitch ) ;
	Void	UnLock( ) ;
	//@}

private:

	// Attributes
	ID3D10Texture2D*			m_Texture;
	ID3D10ShaderResourceView*	m_ShaderView;
	Int8						m_CurrentLevelLocked;
    UInt8						m_MipMapLevel;

};

Inline
ID3D10Texture2D* CImplDirectXTexture2D::GetD3DTexture() const
{
	return m_Texture;
}

}

#endif
