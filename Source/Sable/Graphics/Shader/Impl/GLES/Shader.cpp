#include <Sable\Graphics\Shader\Impl\GLES\Shader.h>

using namespace Sable;

Char* CImplGLESShader::m_StdAttributesNames[] = 
{ 
	"Attr_Position", 
	"Attr_Normal", 
	"Attr_BiNormal", 
	"Attr_Tangent", 
	"Attr_TexCoord0", 
	"Attr_TexCoord1", 
	"Attr_TexCoord2", 
	"Attr_TexCoord3", 
	"Attr_TexCoord4", 
	"Attr_TexCoord5", 
	"Attr_TexCoord6", 
	"Attr_TexCoord7",
	"Attr_Color0",
	NULL
};

CImplGLESShader::CImplGLESShader( CShader& publicImpl ) :
    CImplStubShader( publicImpl )
{
	m_ProgramID = 0;
}

CImplGLESShader::~CImplGLESShader()
{
	if( m_ProgramID )
		glDeleteProgram( m_ProgramID );
}

Bool CImplGLESShader::Initialize( )
{
	m_ProgramID = glCreateProgram();

	DebugAssert( m_ProgramID != 0 );

	GLuint vtxShaderID = m_PublicImpl->GetVertexShaderProgram()->GetImpl().GetShaderObjectID();
	GLuint pixelShaderID = m_PublicImpl->GetPixelShaderProgram()->GetImpl().GetShaderObjectID();
	
	DebugAssert( pixelShaderID != 0 );
	DebugAssert( vtxShaderID != 0 );

	DebugAssertGLCall( glAttachShader( m_ProgramID, vtxShaderID ) );
	DebugAssertGLCall( glAttachShader( m_ProgramID, pixelShaderID ) );

	// This call is necessary otherwise, glGetAttribLocation is not able to return active attributes ...
	DebugAssertGLCall( glLinkProgram( m_ProgramID ) );

	// Remap attribute source index to correct values
	int id = 0;
	int i = 0;
	while( m_StdAttributesNames[i] )
	{
		int loc = DebugAssertGLCall( glGetAttribLocation( m_ProgramID, m_StdAttributesNames[i] ) );
		if( loc != -1 )
		{
			DebugAssertGLCall( glBindAttribLocation( m_ProgramID, id, m_StdAttributesNames[i] ) );
			id++;
		}
		i++;
	}
	
	// Recall link to flush attributes binding
	DebugAssertGLCall( glLinkProgram( m_ProgramID ) );

	GLint status;
	DebugAssertGLCall( glGetProgramiv( m_ProgramID, GL_LINK_STATUS, &status ) );
	if( status == FALSE )
	{
		DebugLogError("Failed to link program");
		return FALSE;
	}
    return TRUE;
}

Void CImplGLESShader::Activate( )
{
	DebugAssertGLCall( glUseProgram( m_ProgramID ) );

}

UInt32 CImplGLESShader::GetParameterCount( )
{
	GLint pCount = 0;

	DebugAssertGLCall( glGetProgramiv( m_ProgramID, GL_ACTIVE_UNIFORMS, &pCount ) );

    return pCount;
}

Void CImplGLESShader::GetParameterNameAtIndex( UInt32 index, CStaticString<64>& name )
{
	Char tmp[64];
	GLsizei length;
	int size;
	GLenum type;

	DebugAssertGLCall( glGetActiveUniform( m_ProgramID, index,64, &length, &size, &type, tmp ) );
}

EShaderParameterType CImplGLESShader::TranslateType( GLenum type )
{
	if( type == GL_FLOAT )
	{
		return nShaderParameterType_Float32;
	}
	else if( type == GL_FLOAT_VEC2 )
	{
		return nShaderParameterType_Vector2;
	}
	else if( type == GL_FLOAT_VEC3 )
	{
		return nShaderParameterType_Vector3;
	}
	else if( type == GL_FLOAT_VEC4 )
	{
		return nShaderParameterType_Vector4;
	}
	else if( type == GL_INT )
	{
		return nShaderParameterType_Int32;
	}
	else if( type == GL_INT_VEC2 )
	{
		DebugError("Unssupported type");
		return nShaderParameterType_None;
	}
	else if( type == GL_INT_VEC3 )
	{
		DebugError("Unssupported type");
		return nShaderParameterType_None;
	}
	else if( type == GL_INT_VEC4 )
	{
		DebugError("Unssupported type");
		return nShaderParameterType_None;
	}
	else if( type == GL_BOOL )
	{
		return nShaderParameterType_Bool;
	}
	else if( type == GL_BOOL_VEC2 )
	{
		DebugError("Unssupported type");
		return nShaderParameterType_None;
	}
	else if( type == GL_BOOL_VEC3 )
	{
		DebugError("Unssupported type");
		return nShaderParameterType_None;
	}
	else if( type == GL_BOOL_VEC4 )
	{
		DebugError("Unssupported type");
		return nShaderParameterType_None;
	}
	else if( type == GL_FLOAT_MAT2 )
	{
		DebugError("Unssupported type");
		return nShaderParameterType_None;
	}
	else if( type == GL_FLOAT_MAT3 )
	{
		DebugError("Unssupported type");
		return nShaderParameterType_None;
	}
	else if( type == GL_FLOAT_MAT4 )
	{
		return nShaderParameterType_Matrix4x4;
	}
	else if( type == GL_SAMPLER_2D )
	{
		return nShaderParameterType_Texture2d;
	}
	else if( type == GL_SAMPLER_CUBE )
	{
		return nShaderParameterType_TextureCube;
	}

	return nShaderParameterType_None;
}

EShaderParameterType CImplGLESShader::GetParameterDataType( String semantic )
{
	Char tmp[64];
	GLsizei length;
	int size;
	GLenum type;

	int index = glGetUniformLocation( m_ProgramID, semantic );
	DebugAssertGLCall( glGetActiveUniform( m_ProgramID, index,64, &length, &size, &type, tmp ) );
    return TranslateType( type );
}

UInt8 CImplGLESShader::GetParameterArraySize( String semantic )
{
	DebugError("Not yet implemented" );
	/*Char tmp[64];
	GLsizei length;
	int size;
	GLenum type;

	DebugAssertGLCall( glGetActiveUniform( m_ProgramID, index,64, &length, &size, &type, tmp ) );
	*/
	return 0;
}

Void CImplGLESShader::SetParameterValue( const CShaderParameter& parameter, const CShaderParameterData& data) 
{
	int location = DebugAssertGLCall( glGetUniformLocation( m_ProgramID, parameter.GetName() ) );
	DebugAssert( location != -1 );

	int previousProgram = -1;
	
	DebugAssertGLCall( glGetIntegerv( GL_CURRENT_PROGRAM, &previousProgram ) );
	DebugAssertGLCall( glUseProgram( m_ProgramID ) );

	if( parameter.GetParameterDataType() == nShaderParameterType_Float32 )
	{
		DebugAssertGLCall( glUniform1f( location, data.GetFloat32() ) );
	}
	else if( parameter.GetParameterDataType() == nShaderParameterType_Vector2 )
	{
		DebugAssertGLCall( glUniform2f( location, data.GetVector2().GetX(), data.GetVector2().GetY() ) );
	}
	else if( parameter.GetParameterDataType() == nShaderParameterType_Vector3 )
	{
		DebugAssertGLCall( glUniform3f( location, data.GetVector3().GetX(), data.GetVector3().GetY(), data.GetVector3().GetZ() ) );
	}
	else if( parameter.GetParameterDataType() == nShaderParameterType_Vector4 )
	{
		DebugAssertGLCall( glUniform4f( location, data.GetVector4().GetX(), data.GetVector4().GetY(), data.GetVector4().GetZ(), data.GetVector4().GetW()  ) );
	}
	else if( parameter.GetParameterDataType() == nShaderParameterType_Int32 )
	{
		DebugAssertGLCall( glUniform1i( location, data.GetInt32() ) );
	}
	else if( parameter.GetParameterDataType() == nShaderParameterType_Bool )
	{
		DebugAssertGLCall( glUniform1i( location, data.GetBool() ) );
	}
	else if( parameter.GetParameterDataType() == nShaderParameterType_Matrix4x4 )
	{
		CMatrix4x4f tmp = data.GetMatrix4x4();
		tmp.Transpose();
		DebugAssertGLCall( glUniformMatrix4fv( location, 1, false, (const GLfloat*)&tmp ) );
	}
	else if( parameter.GetParameterDataType() == nShaderParameterType_TextureCube )
	{
		UInt32 glName = data.GetTextureCube().GetImpl().GetGLTextureName();		
		DebugAssertGLCall( glActiveTexture(GL_TEXTURE0) );
		DebugAssertGLCall( glBindTexture(GL_TEXTURE_CUBE_MAP, glName) );
		DebugAssertGLCall( glUniform1i( location, 0 ) );
	}
	else if( parameter.GetParameterDataType() == nShaderParameterType_Texture2d )
	{
		UInt32 glName = data.GetTexture2D().GetImpl().GetGLTextureName();		
		DebugAssertGLCall( glActiveTexture(GL_TEXTURE0) );
		DebugAssertGLCall( glBindTexture(GL_TEXTURE_2D, glName) );
		DebugAssertGLCall( glUniform1i( location, 0 ) );
	}
	else
	{
		DebugError( "Unssuported data type" );
	}

	DebugAssertGLCall( glUseProgram( previousProgram ) );
}

Void CImplGLESShader::ParseParameters()
{
	GLint pCount = 0;
	Char name[64];
	GLsizei length;
	int size;
	GLenum type;

	DebugAssertGLCall( glGetProgramiv( m_ProgramID, GL_ACTIVE_UNIFORMS, &pCount ) );

	for( Int32 i=0; i<pCount; i++ )
	{
		glGetActiveUniform( m_ProgramID, i,64, &length, &size, &type, name );

		CShaderParameter& p = m_PublicImpl->m_ParameterMap.AddItem( name );
		p.SetParameterDataType( TranslateType( type ) );
		p.SetArraySize( length );
		p.SetName( name );
		p.SetShader( *m_PublicImpl );
	
	}
}