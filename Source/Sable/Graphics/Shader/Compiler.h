#ifndef _SABLE_GRAPHICS_SHADER_COMPILER_
#define _SABLE_GRAPHICS_SHADER_COMPILER_

#include <Sable\Core\String\String.h>
#include <Sable\Core\File\FilePath.h>
#include <Sable\Core\Collection\Array.h>
#include <Sable\Graphics\Common\DataTypes.h>

namespace Sable
{

/** 
\ingroup GraphicsShader
Class used to compile a textual shader effect descritption to be compiled
*/
class CShaderCompiler
{

public:

    /** @name Constructor/Destructor*/
    //@{
    CShaderCompiler( );
    virtual ~CShaderCompiler();
    //@}

    /** @name Operator*/
    //@{
    //@}

    /** @name Accessors*/
    //@{
    String              GetErrorString() const;
	const CArray<Byte>&	GetByteCode()const;
	//@}

	/** @name Manipulator*/
	//@{
	Bool Compile( EShaderProgramType programType, const CFilePath& filePath  );
	Bool Compile( EShaderProgramType programType, String buffer  );
	//@}

private: 

    //Methods

    //Attributes
	CArray<Byte>	    m_ByteCode;
    CString             m_ErrorString;

};

}
#endif
