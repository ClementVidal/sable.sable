#ifndef _SABLE_GRAPHICS_SHADER_IMPL_GLES_SHADER_
#define _SABLE_GRAPHICS_SHADER_IMPL_GLES_SHADER_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Graphics\Shader\Impl\Stub\Shader.h>
#include <Sable\Graphics\Common\Impl\GLES\GraphicsManagerHelper.h>
#include <Sable\Graphics\Common\Impl\GLES\GraphicsManager.h>

namespace Sable
{

class CShader;
class CShaderParameterData;

/** 

*/
class CImplGLESShader : public CImplStubShader
{

public:

	/** @name Constructor\Destructor*/
	//@{
	CImplGLESShader( CShader& publicImpl );
	~CImplGLESShader();
	//@}

	/** @name Manipulator*/
	//@{
	Void						ParseParameters();
	Bool						Initialize( );
	Void						Activate( );
    UInt32						GetParameterCount( );
    Void        				GetParameterNameAtIndex( UInt32 index, CStaticString<64>& name );
    EShaderParameterType	GetParameterDataType( String semantic ); 
    UInt8						GetParameterArraySize( String semantic );
    Void						SetParameterValue( const CShaderParameter& parameter, const CShaderParameterData& data) ;
	//@}
	
protected:

	// Struct 

	// Method
	EShaderParameterType TranslateType( GLenum type );

	// Attribute
	GLuint		m_ProgramID;

	// Static attributes
	static Char* m_StdAttributesNames[];
};

}

#endif
