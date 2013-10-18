#include <Sable/Graphics/Shader/ParameterData.h>

using namespace Sable;

CShaderParameterData::CShaderParameterData( )
{
	m_DataType = nShaderParameterType_None;
	m_Float32 = NULL;
}

CShaderParameterData::CShaderParameterData( const Bool& data )
{
	m_DataType = nShaderParameterType_Bool;
	m_Bool = &data;
}

CShaderParameterData::CShaderParameterData( const Float32& data )
{
	m_DataType = nShaderParameterType_Float32;
	m_Float32 = &data;
}

CShaderParameterData::CShaderParameterData( const CColor& data )
{
	m_DataType = nShaderParameterType_Vector4;
	m_Vector4 = ( CVector4f*) &data;
}

CShaderParameterData::CShaderParameterData( const STuple2f& data )
{
	m_DataType = nShaderParameterType_Vector2;
	m_Vector2 = (CVector2f*)&data;
}

CShaderParameterData::CShaderParameterData( const CVector2f& data )
{
	m_DataType = nShaderParameterType_Vector2;
	m_Vector2 = &data;
}

CShaderParameterData::CShaderParameterData( const CVector3f& data )
{
	m_DataType = nShaderParameterType_Vector3;
	m_Vector3 = &data;
}

CShaderParameterData::CShaderParameterData( const STuple3f& data )
{
	m_DataType = nShaderParameterType_Vector3;
	m_Vector3 = (CVector3f*)&data;
}

CShaderParameterData::CShaderParameterData( const CVector4f& data )
{
	m_DataType = nShaderParameterType_Vector4;
	m_Vector4 = &data;
}

CShaderParameterData::CShaderParameterData( const STuple4f& data )
{
	m_DataType = nShaderParameterType_Vector4;
	m_Vector4 = (CVector4f*)&data;
}

CShaderParameterData::CShaderParameterData( const CArray<Float32>& data )
{
	m_DataType = nShaderParameterType_Float32Array;
	m_Float32Array = &data;
}

CShaderParameterData::CShaderParameterData( const CArray<CVector3f>& data )
{
	m_DataType = nShaderParameterType_Vector3Array;
	m_Vector3Array = &data;
}

CShaderParameterData::CShaderParameterData( const CArray<CVector4f>& data )
{
	m_DataType = nShaderParameterType_Vector4Array;
	m_Vector4Array = &data;
}

CShaderParameterData::CShaderParameterData( const Int32& data )
{
	m_DataType = nShaderParameterType_Int32;
	m_Int32 = &data;
}

CShaderParameterData::CShaderParameterData( const CMatrix4x4f& data )
{
	m_DataType = nShaderParameterType_Matrix4x4;
	m_Matrix4x4 = &data;
}

CShaderParameterData::CShaderParameterData( const CTexture2D& data )
{
	m_DataType = nShaderParameterType_Texture2d;
	m_Texture2D = &data;
}

CShaderParameterData::CShaderParameterData( const CTexture3D& data )
{
	m_DataType = nShaderParameterType_Texture3d;
	m_Texture3D = &data;
}

CShaderParameterData::CShaderParameterData( const CTextureCube& data )
{
	m_DataType = nShaderParameterType_TextureCube;
	m_TextureCube = &data;
}

CShaderParameterData::CShaderParameterData( const CStatesSampler& data )
{
	m_DataType = nShaderParameterType_Sampler;
	m_Sampler = &data;
}

CShaderParameterData::CShaderParameterData( const CRenderTargetTexture& data )
{
	m_DataType = nShaderParameterType_RenderTargetTexture;
	m_RenderTargetTexture = &data;
}

CShaderParameterData& CShaderParameterData::operator = ( const CShaderParameterData& other )
{
	m_DataType = other.m_DataType;
	m_Float32 = other.m_Float32;
	return *this;
}

Bool CShaderParameterData::operator != ( const CShaderParameterData& p ) const
{
	if( m_DataType != p.m_DataType )
		return TRUE;

	if( m_DataType ==  nShaderParameterType_Vector2 )
	{
		if( *m_Vector2 == *p.m_Vector2 )
			return FALSE;
	}
	else if( m_DataType ==  nShaderParameterType_Vector3 )
	{
		if( *m_Vector3 == *p.m_Vector3 )
			return FALSE;
	}
	else if( m_DataType ==  nShaderParameterType_Vector4 )
	{
		if( *m_Vector4 == *p.m_Vector4 )
			return FALSE;
	}
	else if( m_DataType ==  nShaderParameterType_Float32Array )
	{
		if( *m_Float32Array == *p.m_Float32Array )
			return FALSE;
	}
	else if( m_DataType ==  nShaderParameterType_Float32 )
	{
		if( *m_Float32 == *p.m_Float32 )
			return FALSE;
	}

	return TRUE;
}