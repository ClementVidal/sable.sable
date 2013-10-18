#ifndef _SABLE_GRAPHICS_SHADER_IMPL_MSW_PROGRAM_
#define _SABLE_GRAPHICS_SHADER_IMPL_MSW_PROGRAM_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Graphics/Shader/Impl/Stub/Program.h>
#include <Sable/Graphics/Common/Impl/DirectX/GraphicsManagerHelper.h>
#include <Sable/Graphics/Common/Impl/DirectX/GraphicsManager.h>

#define MAX_TEXTURE_COUNT 8
#define MAX_SAMPLER_COUNT 8
#define MAX_CBUFFER_COUNT 4

struct ID3D10DeviceChild;
struct ID3D11ShaderReflection;

namespace Sable
{

class CShaderParameter;
class CShaderParameterData;
class CImplDirectXShader;

/** 

*/
class CImplDirectXShaderProgram : public CImplStubShaderProgram
{

public:

	/** @name Constructor\Destructor*/
	//@{
	CImplDirectXShaderProgram( CShaderProgram& publicImpl );
	~CImplDirectXShaderProgram();
	//@}

	/** @name Manipulator*/
	//@{
	Bool						Initialize( );
	Void						Activate( );
	Void						ParseParameters( CImplDirectXShader& shader );
    UInt32						GetParameterCount( );
    Void        				GetParameterNameAtIndex( UInt32 index, CStaticString<64>& name );
    EShaderParameterType	GetParameterDataType( String semantic ); 
    UInt8						GetParameterArraySize( String semantic );
    Void						SetParameterValue( const CShaderParameter& parameter, const CShaderParameterData& data) ;
	//@}
	
protected:

	// Struct 
	struct SVariable
	{
		D3D10_SHADER_VARIABLE_DESC	VariableDesc;
		D3D10_SHADER_TYPE_DESC		TypeDesc;
	};
	struct SCBuffer
	{
		D3D10_SHADER_INPUT_BIND_DESC BindDesc;
		D3D10_SHADER_BUFFER_DESC	BufferDesc;
		ID3D10Buffer*				Buffer;
		CArray<SVariable>			Variables;
		CArray<Byte>				RawData;
		Bool						IsDirty;
	};

	//Method
	Void			ExtractParametersInfo();
	ID3D10Buffer*	CreateCBuffer( const D3D10_SHADER_BUFFER_DESC& desc );
	EShaderParameterType	ConvertType( const D3D10_SHADER_TYPE_DESC& type ) const;
    Void						SetSamplerParameterValue( const CShaderParameter& parameter, const CShaderParameterData& data);
	Void						SetTextureParameterValue( const CShaderParameter& parameter, const CShaderParameterData& data);
	Void						SetCBufferParameterValue( const CShaderParameter& parameter, const CShaderParameterData& data);
	Void			FlushCBuffer();

	//Attribute
	D3D10_SHADER_INPUT_BIND_DESC			m_Desc;
    ID3D10DeviceChild*                      m_Program;
    ID3D10ShaderReflection*                 m_Reflection;

	SCBuffer								m_CBufferTable[MAX_CBUFFER_COUNT];		
	UInt32									m_CBufferCount;		
	D3D10_SHADER_INPUT_BIND_DESC			m_SamplerTable[MAX_SAMPLER_COUNT];
	UInt32									m_SamplerCount;
	D3D10_SHADER_INPUT_BIND_DESC			m_TextureTable[MAX_TEXTURE_COUNT];
	UInt32									m_TextureCount;

	UInt32									m_ParameterCount;
};

}

#endif
