#ifndef _SABLE_GRAPHICS_SHADER_IMPL_STUB_PROGRAM_
#define _SABLE_GRAPHICS_SHADER_IMPL_STUB_PROGRAM_

#include <Sable/Core/Common/DataTypes.h>

namespace Sable
{

class CShaderProgram;

/** 
Interface Wrapper for Shader program
*/
class CImplStubShaderProgram
{

public:

    /** @name Constructor\Destructor*/
    //@{
    CImplStubShaderProgram( CShaderProgram& publicImpl ) { m_PublicImpl = &publicImpl; }
    virtual ~CImplStubShaderProgram() {};
    //@}

	/** @name Manipulator*/
	//@{
	virtual Bool						Initialize( ) { return FALSE; }
        virtual Void						Activate( ) {}
	//@}

protected:

	//Method

	//Attribute
    CShaderProgram  *m_PublicImpl;

};

}

#endif
