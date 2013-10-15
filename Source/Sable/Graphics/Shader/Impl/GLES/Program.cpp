#include <Sable\Graphics\Shader\Impl\GLES\Program.h>

using namespace Sable;

CImplGLESShaderProgram::CImplGLESShaderProgram( CShaderProgram& publicImpl ) :
    CImplStubShaderProgram( publicImpl )
{
	m_ShaderObjID = 0;
}

CImplGLESShaderProgram::~CImplGLESShaderProgram()
{
	if( m_ShaderObjID )
		glDeleteShader( m_ShaderObjID );
}


Void CImplGLESShaderProgram::Activate()
{

}

GLuint CImplGLESShaderProgram::GetShaderObjectID() const
{
	return m_ShaderObjID;
}

Bool CImplGLESShaderProgram::Initialize( )
{
	if( m_PublicImpl->GetType() == nShaderProgramType_Pixel )
		m_ShaderObjID = glCreateShader( GL_FRAGMENT_SHADER );
	else if( m_PublicImpl->GetType() == nShaderProgramType_Vertex )
		m_ShaderObjID = glCreateShader( GL_VERTEX_SHADER );
	else
	{
		DebugError( "CImplGLESShaderProgram::Initialize - Unssoported program type");
		return FALSE;
	}

	DebugAssert( m_ShaderObjID != 0 );

	int length = m_PublicImpl->GetRawData().GetByteCount();
	const char* code = (const char*)m_PublicImpl->GetRawData().GetBuffer();

	DebugAssertGLCall( glShaderSource(m_ShaderObjID, 1, &code, &length ) );

	DebugAssertGLCall( glCompileShader(m_ShaderObjID ) );

	GLint compileStatus;
	glGetShaderiv( m_ShaderObjID, GL_COMPILE_STATUS, &compileStatus );
	if( !compileStatus )
	{
		char error[2048];
		GLsizei len = 0;
		glGetShaderInfoLog( m_ShaderObjID, 2948, &len, error );
		return FALSE;
	}

    return TRUE;
}
