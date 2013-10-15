#include <Sable\Graphics\Texture\Impl\GLES\TextureCube.h>

using namespace Sable;

CImplGLESTextureCube::CImplGLESTextureCube()
{

}

CImplGLESTextureCube::~CImplGLESTextureCube()
{
	UnInitialize();
}

Void CImplGLESTextureCube::UnInitialize( )
{
	if( m_TextureID != 0 )
		glDeleteTextures( 1, &m_TextureID );

	m_TextureID = 0;
}

Void CImplGLESTextureCube::Initialize( const CTextureInfo& info, const Byte* data )
{
	DebugAssertGLCall( glGenTextures( 1, &m_TextureID ) );
	DebugAssertGLCall( glBindTexture( GL_TEXTURE_CUBE_MAP, m_TextureID ) );

	if( CImplGLESGraphicsManagerHelper::IsCompressedTextureFormat( info.Format ) )
	{
		GLenum pixelFormat = CImplGLESGraphicsManagerHelper::TranslatePixelFormat( info.Format );
		GLenum pixelType = CImplGLESGraphicsManagerHelper::TranslatePixelType( info.Format );

		DebugAssertGLCall( glCompressedTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, pixelType, info.Width, info.Height, 0, info.GetMipMapByteCount(0), data + info.GetSurfaceByteCount() * 0 ) );
		DebugAssertGLCall( glCompressedTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, pixelType, info.Width, info.Height, 0, info.GetMipMapByteCount(0), data + info.GetSurfaceByteCount() * 1 ) );
		DebugAssertGLCall( glCompressedTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, pixelType, info.Width, info.Height, 0, info.GetMipMapByteCount(0), data + info.GetSurfaceByteCount() * 2 ) );
		DebugAssertGLCall( glCompressedTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, pixelType, info.Width, info.Height, 0, info.GetMipMapByteCount(0), data + info.GetSurfaceByteCount() * 3 ) );
		DebugAssertGLCall( glCompressedTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, pixelType, info.Width, info.Height, 0, info.GetMipMapByteCount(0), data + info.GetSurfaceByteCount() * 4 ) );
		DebugAssertGLCall( glCompressedTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, pixelType, info.Width, info.Height, 0, info.GetMipMapByteCount(0), data + info.GetSurfaceByteCount() * 5 ) );
	}
	else
	{
		GLenum pixelFormat = CImplGLESGraphicsManagerHelper::TranslatePixelFormat( info.Format );
		GLenum pixelType = CImplGLESGraphicsManagerHelper::TranslatePixelType( info.Format );
		DebugAssertGLCall( glTexImage2D( GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, pixelFormat, info.Width, info.Height, 0, pixelFormat, pixelType, data + info.GetSurfaceByteCount() * 0 ) );
		DebugAssertGLCall( glTexImage2D( GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, pixelFormat, info.Width, info.Height, 0, pixelFormat, pixelType, data + info.GetSurfaceByteCount() * 1 ) );
		DebugAssertGLCall( glTexImage2D( GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, pixelFormat, info.Width, info.Height, 0, pixelFormat, pixelType, data + info.GetSurfaceByteCount() * 2 ) );
		DebugAssertGLCall( glTexImage2D( GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, pixelFormat, info.Width, info.Height, 0, pixelFormat, pixelType, data + info.GetSurfaceByteCount() * 3 ) );
		DebugAssertGLCall( glTexImage2D( GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, pixelFormat, info.Width, info.Height, 0, pixelFormat, pixelType, data + info.GetSurfaceByteCount() * 4 ) );
		DebugAssertGLCall( glTexImage2D( GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, pixelFormat, info.Width, info.Height, 0, pixelFormat, pixelType, data + info.GetSurfaceByteCount() * 5 ) );
	}
}

UInt32	CImplGLESTextureCube::GetGLTextureName() const
{
	return m_TextureID;
}
