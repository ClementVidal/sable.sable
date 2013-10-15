#ifndef _SABLE_GRAPHICS_SHADER_IMPL_GLES_PROGRAM_
#define _SABLE_GRAPHICS_SHADER_IMPL_GLES_PROGRAM_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Graphics\Shader\Impl\Stub\Program.h>
#include <Sable\Graphics\Common\Impl\GLES\GraphicsManagerHelper.h>
#include <Sable\Graphics\Common\Impl\GLES\GraphicsManager.h>

namespace Sable
{

class CShaderParameter;
class CShaderParameterData;

/** 

*/
class CImplGLESShaderProgram : public CImplStubShaderProgram
{

public:

	/** @name Constructor\Destructor*/
	//@{
	CImplGLESShaderProgram( CShaderProgram& publicImpl );
	~CImplGLESShaderProgram();
	//@}

	/** @name Accessors*/
	//@{
	//Void						SetParameterValue( const CShaderParameter& parameter, const CShaderParameterData& data) ;
	GLuint						GetShaderObjectID() const;
	//@}

	/** @name Manipulator*/
	//@{
	Void						Activate();
	Bool						Initialize( );
 	//@}
	
protected:

	// Struct 

	// Method

	// Attribute
	GLuint			m_ShaderObjID;
};

}

#endif
