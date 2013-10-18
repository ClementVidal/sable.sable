#include <Sable/Graphics/RenderTarget/Impl/GLES/Texture.h>

#include <Sable/Graphics/Common/Impl/GLES/GraphicsManagerHelper.h>

using namespace Sable;

CImplGLESRenderTargetTexture::CImplGLESRenderTargetTexture( CRenderTargetTexture& publicImpl ):
    CImplStubRenderTargetTexture( publicImpl )
{
	m_TextureID = 0;
}

CImplGLESRenderTargetTexture::~CImplGLESRenderTargetTexture()
{
	UnInitialize();
}

Void CImplGLESRenderTargetTexture::Activate( Int32 index )
{
}

Void CImplGLESRenderTargetTexture::Initialize( const CRenderTargetInfo& info )
{
	glGenTextures( 1, &m_TextureID );
	glBindTexture( GL_TEXTURE_2D, m_TextureID );
	glTexImage2D( GL_TEXTURE_2D, 0, CImplGLESGraphicsManagerHelper::TranslatePixelFormat( info.TextureInfo.Format ), info.TextureInfo.Width, info.TextureInfo.Height, 0,
			CImplGLESGraphicsManagerHelper::TranslatePixelFormat( info.TextureInfo.Format ), CImplGLESGraphicsManagerHelper::TranslatePixelType( info.TextureInfo.Format ), NULL );

}

Void CImplGLESRenderTargetTexture::UnInitialize( )
{
	if( m_TextureID != 0 )
		glDeleteTextures( 1, &m_TextureID );

	m_TextureID = 0;
}

Void CImplGLESRenderTargetTexture::Clear( const CColor& col )
{
	 glClearColor( col.GetR(), col.GetG(), col.GetB(), col.GetA() );
	 glClear(GL_COLOR_BUFFER_BIT);
}
