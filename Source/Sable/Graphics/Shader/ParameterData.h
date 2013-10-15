#ifndef _SABLE_GRAPHICS_SHADER_SHADERPARAMETERDATA_
#define _SABLE_GRAPHICS_SHADER_SHADERPARAMETERDATA_

#include <Sable\Core\Common\DataTypes.h>

namespace Sable
{

class CVector2f;
class CVector3f;
class CVector4f;
class CMatrix4x4f;
class CTexture2D;
class CTexture3D;
class CTextureCube;
class CRenderTargetTexture;
class CStatesSampler;

/** 
\ingroup GraphicsShader
Bas class of the shader system.
*/
class CShaderParameterData
{

public:

	/** @name Constructor/Destructor*/
	//@{
	CShaderParameterData( );
	CShaderParameterData( const Float32& data );
	CShaderParameterData( const CColor& data );
	CShaderParameterData( const STuple2f& data );
	CShaderParameterData( const CVector2f& data );
	CShaderParameterData( const CVector3f& data );
	CShaderParameterData( const STuple3f& data );
	CShaderParameterData( const CVector4f& data );
	CShaderParameterData( const STuple4f& data );
	CShaderParameterData( const CArray<Float32>& data );
	CShaderParameterData( const CArray<CVector3f>& data );
	CShaderParameterData( const CArray<CVector4f>& data );
	CShaderParameterData( const Int32& data );
	CShaderParameterData( const CMatrix4x4f& data );
	CShaderParameterData( const CTexture2D& data );
	CShaderParameterData( const CTexture3D& data );
	CShaderParameterData( const CTextureCube& data );
	CShaderParameterData( const CStatesSampler& data );
	CShaderParameterData( const CRenderTargetTexture& data );
	CShaderParameterData( const Bool& data );
	//@}

	/** @name Operator*/
	//@{
	CShaderParameterData& operator = ( const CShaderParameterData& other );
	Bool operator != ( const CShaderParameterData& p ) const;
	//@}

	/** @name Accessor*/
	//@{
	EShaderParameterType	GetDataType( ) const;
	const Float32&				GetFloat32() const ;
	const CVector2f&				GetVector2() const ;
	const CVector3f&				GetVector3() const ;
	const CVector4f&				GetVector4() const ;
	const CArray<CVector4f>&		GetVector4Array() const ;
	const CArray<CVector3f>&		GetVector3Array() const ;
	const CArray<Float32>&		GetFloat32Array() const ;
	const Int32&				GetInt32() const ;
	const CMatrix4x4f&			GetMatrix4x4() const ;
	const CTexture2D&			GetTexture2D() const ;
	const CTexture3D&			GetTexture3D() const ;
	const CTextureCube&			GetTextureCube() const ;
	const CStatesSampler&		GetSampler() const ;
	const Bool&					GetBool() const ;
	const CRenderTargetTexture&	GetRenderTargetTexture() const ;
	//@}

private:

	// Attribute	
	union
	{
		const Float32*					m_Float32;
		const CVector2f*					m_Vector2;
		const CVector3f*					m_Vector3;
		const CVector4f*					m_Vector4;
		const Bool*						m_Bool;
		const CArray<Float32>*			m_Float32Array;
		const CArray<CVector3f>*			m_Vector3Array;
		const CArray<CVector4f>*			m_Vector4Array;
		const Int32*					m_Int32;
		const CMatrix4x4f*				m_Matrix4x4;
		const CTexture2D*				m_Texture2D;
		const CTexture3D*				m_Texture3D;
		const CTextureCube*				m_TextureCube;
		const CRenderTargetTexture*		m_RenderTargetTexture;
		const CStatesSampler*			m_Sampler;
	};

	EShaderParameterType	m_DataType;

};

Inline
EShaderParameterType CShaderParameterData::GetDataType( ) const
{
	return m_DataType;
}

Inline
const Bool& CShaderParameterData::GetBool() const 
{
	return *m_Bool;
}

Inline
const Float32& CShaderParameterData::GetFloat32() const
{
	return *m_Float32;
}

Inline
const CVector2f& CShaderParameterData::GetVector2() const 
{
	return *m_Vector2;
}

Inline
const CVector3f& CShaderParameterData::GetVector3() const 
{
	return *m_Vector3;
}

Inline
const CVector4f&	CShaderParameterData::GetVector4() const 
{
	return *m_Vector4;
}

Inline
const CArray<CVector4f>&	CShaderParameterData::GetVector4Array() const 
{
	return *m_Vector4Array;
}

Inline
const CArray<CVector3f>&	CShaderParameterData::GetVector3Array() const 
{
	return *m_Vector3Array;
}

Inline
const CArray<Float32>& CShaderParameterData::GetFloat32Array() const 
{
	return *m_Float32Array;
}

Inline
const Int32& CShaderParameterData::GetInt32() const 
{
	return *m_Int32;
}

Inline
const CMatrix4x4f& CShaderParameterData::GetMatrix4x4() const 
{
	return *m_Matrix4x4;
}

Inline
const CStatesSampler& CShaderParameterData::GetSampler() const
{
	return *m_Sampler;
}

Inline
const CTexture2D& CShaderParameterData::GetTexture2D() const 
{
	return *m_Texture2D;
}

Inline
const CTexture3D& CShaderParameterData::GetTexture3D() const 
{
	return *m_Texture3D;
}


Inline
const CTextureCube& CShaderParameterData::GetTextureCube() const 
{
	return *m_TextureCube;
}

Inline
const CRenderTargetTexture&	CShaderParameterData::GetRenderTargetTexture() const 
{
	return *m_RenderTargetTexture;
}


}
#endif
