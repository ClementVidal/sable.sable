#ifndef _SABLE_GRAPHICS_SHADER_SHADERPARAMETER_
#define _SABLE_GRAPHICS_SHADER_SHADERPARAMETER_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/ManagedObject/Ref.h>
#include <Sable/Core/String/String.h>
#include <Sable/Graphics/Common/DataTypes.h>
#include <Sable/Core/Math/Matrix4x4f.h>
#include <Sable/Graphics/Texture/Texture.h>
#include <Sable/Core/Math/Vector3f.h>
#include <Sable/Core/Math/Vector4f.h>
#include <Sable/Graphics/Shader/Shader.h>
#include <Sable/Graphics/Shader/ParameterData.h>
#include <Sable/Graphics/Shader/Impl/Header.h>

#define SHADERPARAMETER_SEMANTIC_LENGTH 64

namespace Sable
{

class CShader;
class CRenderer;

/** 
\ingroup GraphicsShader
Store data to be transfered to the Shader
*/
class CShaderParameter
{

public:

	/** @name Constructor/Destructor*/
    //@{
	CShaderParameter( );
	~CShaderParameter();
    //@}

    /** @name Operator*/
    //@{
	CShaderParameter& operator = (const CShaderParameter& p ) ;
    //@}

    /** @name Accessor*/
    //@{
	Void						SetValue( const CShaderParameterData& data );
	Int32						GetArraySize() const;
	EShaderParameterType		GetParameterDataType() const;
	String    					GetName() const;
	HashValue    				GetNameHash() const;
	//@}

	/** @name Manipulator*/
	//@{
	//@}

    /** @name System only*/
    //@{
	CImplShaderParameter&		GetImpl();
	Void						SetName( String s );
    Void						SetParameterDataType( const EShaderParameterType type );
	Void						SetShader( CShader& shader );
	Void						SetArraySize( Int32 size );
    //@}

private: 

    //Methods
	
    //Attributes
	CImplShaderParameter		m_Impl;
	CStringIdentifier			m_Name;
	HashValue					m_NameHash;
	EShaderParameterType		m_Type;
	Int32						m_ArraySize;

	CShader*					m_OwnerShader;
};

Inline
Void CShaderParameter::SetParameterDataType( const EShaderParameterType type ) 
{ 
	DebugAssert( type != nShaderParameterType_None );
	m_Type = type; 
}

Inline
Void CShaderParameter::SetArraySize( Int32 count ) 
{
	m_ArraySize = count; 
}

Inline
Int32 CShaderParameter::GetArraySize() const 
{ 
	return m_ArraySize; 
}

Inline
EShaderParameterType CShaderParameter::GetParameterDataType() const 
{ 
	return m_Type; 
}

Inline
HashValue CShaderParameter::GetNameHash() const
{
	return m_NameHash;
}

Inline
String CShaderParameter::GetName() const 
{ 
    return (String) m_Name.GetBuffer(); 
}

Inline
Void CShaderParameter::SetName( String s )
{
	m_Name = s;
	m_NameHash = Sable::StringGetHashCode( m_Name );
}

}
#endif
