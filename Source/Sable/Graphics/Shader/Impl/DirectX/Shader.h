#ifndef _SABLE_GRAPHICS_SHADER_IMPL_MSW_SHADER_
#define _SABLE_GRAPHICS_SHADER_IMPL_MSW_SHADER_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Graphics\Shader\Impl\Stub\Shader.h>
#include <Sable\Graphics\Common\Impl\DirectX\GraphicsManagerHelper.h>
#include <Sable\Graphics\Common\Impl\DirectX\GraphicsManager.h>

namespace Sable
{

class CShaderParameterData;

/** 

*/
class CImplDirectXShader : public CImplStubShader
{

public:

	/** @name Constructor\Destructor*/
	//@{
	CImplDirectXShader( CShader& publicImpl );
	~CImplDirectXShader();
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

	// FriendShip
	friend class CImplDirectXShaderProgram;

	// Struct 

	// Method

	// Attribute
};

}

#endif
