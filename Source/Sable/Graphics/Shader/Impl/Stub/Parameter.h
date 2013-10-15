#ifndef _SABLE_GRAPHICS_SHADER_IMPL_STUB_PARAMETER_
#define _SABLE_GRAPHICS_SHADER_IMPL_STUB_PARAMETER_

#include <Sable\Core\Common\DataTypes.h>

namespace Sable
{

/** 
*/
class CImplStubShaderParameter
{

public:

    /** @name Constructor\Destructor*/
    //@{
    CImplStubShaderParameter( CShaderParameter& publicImpl ) { m_PublicImpl = &publicImpl; }
    virtual ~CImplStubShaderParameter() {};
    //@}

	/** @name Manipulator*/
	//@{
	//@}

protected:

	//Method

	//Attribute
    CShaderParameter  *m_PublicImpl;

};

}

#endif
