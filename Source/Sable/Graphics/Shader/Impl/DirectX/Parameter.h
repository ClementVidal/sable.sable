#ifndef _SABLE_GRAPHICS_SHADER_IMPL_DIRECTX_PARAMETER_
#define _SABLE_GRAPHICS_SHADER_IMPL_DIRECTX_PARAMETER_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Graphics\Shader\Impl\Stub\Parameter.h>

namespace Sable
{

/** 
*/
class CImplDirectXShaderParameter : public CImplStubShaderParameter
{

public:

    /** @name Constructor\Destructor*/
    //@{
    CImplDirectXShaderParameter( CShaderParameter& publicImpl );
    ~CImplDirectXShaderParameter();
    //@}

	/** @name Accessors*/
	//@{
	Void SetProgram( CImplDirectXShaderProgram& p );
	CImplDirectXShaderProgram& GetProgram();
	//@}

protected:

	//Method

	//Attribute
	CImplDirectXShaderProgram*		m_Program;
};

}

#endif
