#include <Sable/Graphics/Texture/Impl/GLES/Texture2D.h>

#include <Sable/Graphics/Common/Impl/GLES/GraphicsManagerHelper.h>

using namespace Sable;

CImplGLESTexture2D::CImplGLESTexture2D()
{
	m_TextureID = 0;
}

CImplGLESTexture2D::~CImplGLESTexture2D()
{
	UnInitialize();
}

UInt32	CImplGLESTexture2D::GetGLTextureName() const
{
	return m_TextureID;
}

Void CImplGLESTexture2D::Initialize( const CTextureInfo& info, Bool lockable, const Byte* data )
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glPixelStorei(GL_PACK_ALIGNMENT, 1);

	DebugAssertGLCall( glGenTextures( 1, &m_TextureID ) );
	DebugAssertGLCall( glBindTexture( GL_TEXTURE_2D, m_TextureID ) );

	if( CImplGLESGraphicsManagerHelper::IsCompressedTextureFormat( info.Format ) )
	{
		GLenum type = CImplGLESGraphicsManagerHelper::TranslatePixelType( info.Format );

		if( info.MipMapCount == 0 || info.MipMapCount == 1 )
		{
			DebugAssertGLCall( glCompressedTexImage2D(GL_TEXTURE_2D, 0, type, info.Width, info.Height, 0, info.GetMipMapByteCount(0), data ) );
		}
		else
		{
			UInt32 offset = 0;
			for( UInt32 i=0;i<info.MipMapCount;i++ )
			{
				DebugAssertGLCall( glCompressedTexImage2D( GL_TEXTURE_2D, i, type, info.GetMipMapWidth( i ), info.GetMipMapHeight( i ), 0, info.GetMipMapByteCount(i), data + offset ) );
				offset += info.GetMipMapByteCount( i );
			}
		}
	}
	else
	{
		GLenum format = CImplGLESGraphicsManagerHelper::TranslatePixelFormat( info.Format );
		GLenum type = CImplGLESGraphicsManagerHelper::TranslatePixelType( info.Format );
		if( info.MipMapCount == 0 || info.MipMapCount == 1 )
		{
			DebugAssertGLCall( glTexImage2D( GL_TEXTURE_2D, 0, format, info.Width, info.Height, 0, format, type, data ) );
			DebugAssertGLCall( glGenerateMipmap(GL_TEXTURE_2D) );
		}
		else 
		{
			UInt32 offset = 0;
			for( UInt32 i=0;i<info.MipMapCount;i++ )
			{
				DebugAssertGLCall( glTexImage2D( GL_TEXTURE_2D, i, format, info.GetMipMapWidth( i ), info.GetMipMapHeight( i ), 0, format, type, data + offset ) );
				offset += info.GetMipMapByteCount( i );
			}
		}

	}
}

Void CImplGLESTexture2D::UnInitialize( )
{
	if( m_TextureID != 0 )
		glDeleteTextures( 1, &m_TextureID );

	m_TextureID = 0;
}

Void* CImplGLESTexture2D::Lock( const UInt8 mipmaplevel, const EBufferAcces acces, UInt32& pitch )
{
	return NULL;
}

Void CImplGLESTexture2D::UnLock( )
{

}
