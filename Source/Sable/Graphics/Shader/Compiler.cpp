#include <Sable/Graphics/Shader/Compiler.h>

#include <Sable/Core/File/File.h>

using namespace Sable;


CShaderCompiler::CShaderCompiler()
{
}

CShaderCompiler::~CShaderCompiler()
{
}

const CArray<Byte>& CShaderCompiler::GetByteCode()const
{
	return m_ByteCode;
}

String CShaderCompiler::GetErrorString() const
{
    return m_ErrorString.GetBuffer();    
}

Bool CShaderCompiler::Compile( EShaderProgramType programType, String buffer  )
{

#if defined( SETUP_IMPLTYPE_DIRECTX )
    ID3D10Device* device = CImplDirectXGraphicsManagerHelper::GetDevice();

    HRESULT hr;
    ID3D10Blob* errorBuffer;
    ID3D10Blob* effectBuffer;

    if( programType == nShaderProgramType_Vertex )
    {
        hr = D3DX10CompileFromMemory( buffer, StringGetLength( buffer ), "None", NULL, NULL, "main", "vs_4_0", D3D10_SHADER_ENABLE_STRICTNESS|D3D10_SHADER_PACK_MATRIX_ROW_MAJOR, 0, NULL, &effectBuffer, &errorBuffer, NULL );
    }
    else if( programType == nShaderProgramType_Pixel )
    {
        hr = D3DX10CompileFromMemory( buffer, StringGetLength( buffer ), "None", NULL, NULL, "main", "ps_4_0", D3D10_SHADER_ENABLE_STRICTNESS|D3D10_SHADER_PACK_MATRIX_ROW_MAJOR, 0, NULL, &effectBuffer, &errorBuffer, NULL );
    }
    else if( programType == nShaderProgramType_Geometry )
    {
        hr = D3DX10CompileFromMemory( buffer, StringGetLength( buffer ), "None", NULL, NULL, "main", "gs_4_0", D3D10_SHADER_ENABLE_STRICTNESS|D3D10_SHADER_PACK_MATRIX_ROW_MAJOR, 0, NULL, &effectBuffer, &errorBuffer, NULL );
    }
    else
    {
        DebugError("Invalid shader program type");
    }

    if( hr != S_OK )
    {
        m_ErrorString = (const  char*) errorBuffer->GetBufferPointer();
        return FALSE;
    }

    m_ByteCode.SetFrom( (const Byte*) effectBuffer->GetBufferPointer(), effectBuffer->GetBufferSize() );
    return TRUE;
#else

    return FALSE;

#endif
}

Bool CShaderCompiler::Compile( EShaderProgramType programType, const CFilePath& filePath )
{
#if defined( SETUP_IMPLTYPE_DIRECTX )
    ID3D10Device* device = CImplDirectXGraphicsManagerHelper::GetDevice();

	HRESULT hr;
    ID3D10Blob* errorBuffer;
    ID3D10Blob* effectBuffer;
	WChar tmp[128];
	StringToWString( filePath.GetPath(), tmp, 128 );

    if( programType == nShaderProgramType_Vertex )
    {
        hr = D3DX10CompileFromFile( tmp, NULL, NULL, "main", "vs_4_0", D3D10_SHADER_ENABLE_STRICTNESS|D3D10_SHADER_PACK_MATRIX_ROW_MAJOR, 0, NULL, &effectBuffer, &errorBuffer, NULL );
    }
    else if( programType == nShaderProgramType_Pixel )
    {
        hr = D3DX10CompileFromFile( tmp, NULL, NULL, "main", "ps_4_0", D3D10_SHADER_ENABLE_STRICTNESS|D3D10_SHADER_PACK_MATRIX_ROW_MAJOR, 0, NULL, &effectBuffer, &errorBuffer, NULL );
    }
    else if( programType == nShaderProgramType_Geometry )
    {
        hr = D3DX10CompileFromFile( tmp, NULL, NULL, "main", "gs_4_0", D3D10_SHADER_ENABLE_STRICTNESS|D3D10_SHADER_PACK_MATRIX_ROW_MAJOR, 0, NULL, &effectBuffer, &errorBuffer, NULL );
    }
    else
    {
        DebugError("Invalid shader program type");
    }

    if( hr != S_OK )
    {
        m_ErrorString = (const  char*) errorBuffer->GetBufferPointer();
        return FALSE;
    }

    m_ByteCode.SetFrom( (const Byte*) effectBuffer->GetBufferPointer(), effectBuffer->GetBufferSize() );
	return TRUE;

#elif defined( SETUP_IMPLTYPE_GLES )

	CFile file;
	if( ! file.Open( filePath, nAccesMode_Read ) )
		return FALSE;

	file.ReadAll( m_ByteCode );

	// Just create a dummy shader to compile code and extract any compiler error information if any
	GLuint programID = 0;
	if( programType == nShaderProgramType_Pixel )
		programID = glCreateShader( GL_FRAGMENT_SHADER );
	else if( programType == nShaderProgramType_Vertex )
		programID = glCreateShader( GL_VERTEX_SHADER );
	else
	{
		DebugError( "CShaderCompiler::Compile - Unssoported program type");
		return FALSE;
	}

	DebugAssert( programID != 0 );

	int length = m_ByteCode.GetByteCount();
	const char* code = (const char*)m_ByteCode.GetBuffer();


	DebugAssertGLCall( glShaderSource(programID, 1, &code, &length ) );

	DebugAssertGLCall( glCompileShader(programID ) );

	GLint compileStatus;
	glGetShaderiv( programID, GL_COMPILE_STATUS, &compileStatus );
	if( !compileStatus )
	{
		char error[2048];
		GLsizei len = 0;
		glGetShaderInfoLog( programID, 2948, &len, error );
		m_ErrorString = error;

		glDeleteShader( programID );
		return FALSE;
	}

	glDeleteShader( programID );

	return TRUE;


#else

	return FALSE;

#endif



}
