#include <Sable\Graphics\Geometry\Impl\GLES\VertexLayout.h>

#include <Sable\Graphics\Geometry\VertexLayout.h>

using namespace Sable;

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

CImplGLESVertexLayout::CImplGLESVertexLayout( CGeometryVertexLayout& publicImpl ):
    CImplStubVertexLayout(publicImpl)
{
}

CImplGLESVertexLayout::~CImplGLESVertexLayout()
{

}

Void CImplGLESVertexLayout::Activate( )
{
	UInt16  id = 0;
	UInt32 stride = 0;

	if( m_PublicImpl->HasElement( nVertexComponent_Position ) )
	{
		const CGeometryVertexElement& element = m_PublicImpl->GetElementAtSemantic( nVertexComponent_Position );

		glEnableVertexAttribArray( id );
		glVertexAttribPointer( 	id, TranslateElementSize( element.Type ), TranslateElementType( element.Type ),
								FALSE, m_PublicImpl->GetVertexByteCount(), BUFFER_OFFSET( stride ) );

		stride += TranslateElementByteCount( element.Type  );
		id++;
	}
	if( m_PublicImpl->HasElement( nVertexComponent_Normal ) )
	{
		const CGeometryVertexElement& element = m_PublicImpl->GetElementAtSemantic( nVertexComponent_Normal );

		glEnableVertexAttribArray( id );
		glVertexAttribPointer( 	id, TranslateElementSize( element.Type ), TranslateElementType( element.Type ),
								FALSE, m_PublicImpl->GetVertexByteCount(), BUFFER_OFFSET( stride ) );

		stride += TranslateElementByteCount( element.Type  );
		id++;
	}
	if( m_PublicImpl->HasElement( nVertexComponent_BiNormal ) )
	{
		const CGeometryVertexElement& element = m_PublicImpl->GetElementAtSemantic( nVertexComponent_BiNormal );

		glEnableVertexAttribArray( id );
		glVertexAttribPointer( 	id, TranslateElementSize( element.Type ), TranslateElementType( element.Type ),
								FALSE, m_PublicImpl->GetVertexByteCount(), BUFFER_OFFSET( stride ) );

		stride += TranslateElementByteCount( element.Type  );
		id++;
	}
	if( m_PublicImpl->HasElement( nVertexComponent_Tangent ) )
	{
		const CGeometryVertexElement& element = m_PublicImpl->GetElementAtSemantic( nVertexComponent_Tangent );

		glEnableVertexAttribArray( id );
		glVertexAttribPointer( 	id, TranslateElementSize( element.Type ), TranslateElementType( element.Type ),
								FALSE, m_PublicImpl->GetVertexByteCount(), BUFFER_OFFSET( stride ) );

		stride += TranslateElementByteCount( element.Type  );
		id++;
	}

    for( UInt32 i=0;i<7;i++ )
    {
        EVertexComponent uvSemantic = (EVertexComponent)(nVertexComponent_TexCoord0 + i);
	    if( m_PublicImpl->HasElement( uvSemantic ) )
	    {
		    const CGeometryVertexElement& element = m_PublicImpl->GetElementAtSemantic( uvSemantic );

			glEnableVertexAttribArray( id );
			glVertexAttribPointer( 	id, TranslateElementSize( element.Type ), TranslateElementType( element.Type ),
									FALSE, m_PublicImpl->GetVertexByteCount(), BUFFER_OFFSET( stride ) );

			stride += TranslateElementByteCount( element.Type  );
			id++;
	    }
    }

	if( m_PublicImpl->HasElement( nVertexComponent_Color0 ) )
	{
		const CGeometryVertexElement& element = m_PublicImpl->GetElementAtSemantic( nVertexComponent_Color0 );

		glEnableVertexAttribArray( id );
		glVertexAttribPointer( 	id, TranslateElementSize( element.Type ), TranslateElementType( element.Type ),
								FALSE, m_PublicImpl->GetVertexByteCount(), BUFFER_OFFSET( stride ) );

		stride += TranslateElementByteCount( element.Type  );
		id++;
	}

}

Int32 CImplGLESVertexLayout::TranslateElementSize( EVertexComponentType type )
{
	switch( type )
	{
	case nVertexComponentType_Float2:
		return  2;

	case nVertexComponentType_Float3:
		return  3;

	case nVertexComponentType_Float4:
		return  4;
	}

	DebugError("Unsuported format");
	return  4;
}

Int32 CImplGLESVertexLayout::TranslateElementByteCount( EVertexComponentType type )
{
	switch( type )
	{
	case nVertexComponentType_Float2:
		return  sizeof( Float32 ) * 2;

	case nVertexComponentType_Float3:
		return  sizeof( Float32 ) * 3;

	case nVertexComponentType_Float4:
		return  sizeof( Float32 ) * 4;
	}

	DebugError("Unsuported format");
	return  0;
}

GLenum CImplGLESVertexLayout::TranslateElementType( EVertexComponentType type )
{
	switch( type )
	{
	case nVertexComponentType_Float2:
		return  GL_FLOAT;

	case nVertexComponentType_Float3:
		return  GL_FLOAT;

	case nVertexComponentType_Float4:
		return  GL_FLOAT;
	}

	DebugError("Unsuported format");
	return  GL_FLOAT;
}

Void CImplGLESVertexLayout::UnInitialize( )
{

}

Void CImplGLESVertexLayout::Initialize( )
{
}

Bool CImplGLESVertexLayout::IsInitialized() const
{
	return TRUE;
}

