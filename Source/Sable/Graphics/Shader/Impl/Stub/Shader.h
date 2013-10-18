#ifndef _SABLE_GRAPHICS_SHADER_IMPL_STUB_SHADER_
#define _SABLE_GRAPHICS_SHADER_IMPL_STUB_SHADER_

#include <Sable/Core/Common/DataTypes.h>

namespace Sable
{

class CShader;
class CShaderProgram;
class CShaderParameter;
class CShaderParameterData;

/** 
*/
class CImplStubShader
{

public:

    /** @name Constructor\Destructor*/
    //@{
    CImplStubShader( CShader& publicImpl ) { m_PublicImpl = &publicImpl; }
    virtual ~CImplStubShader() {};
    //@}

	/** @name Manipulator*/
	//@{
	virtual Void						ParseParameters() {}
	virtual Bool						Initialize( ) { return FALSE; }
	virtual Void						Activate( ) {}
    virtual UInt32						GetParameterCount( ) { return 0; }
    virtual Void        				GetParameterNameAtIndex( UInt32 index, CStaticString<64>& name ) { }
    virtual EShaderParameterType	GetParameterDataType( String semantic ) { return nShaderParameterType_None; }
    virtual UInt8						GetParameterArraySize( String semantic ) { return 0; };
    virtual Void						SetParameterValue( const CShaderParameter& parameter, const CShaderParameterData& data) const {}
	//@}

protected:

	//Method

	//Attribute
    CShader  *m_PublicImpl;

};

}

#endif
