#include <Sable/Graphics/Material/Parameter.h>

#include<Sable/Graphics/Texture/Header.h>

using namespace Sable;

CMaterialParameter::CMaterialParameter( )
{
}

CMaterialParameter::CMaterialParameter( String name )
{
	m_Name = name;
}

CMaterialParameter::~CMaterialParameter( )
{
}

Void CMaterialParameter::SetValue( const CMaterialParameter& data )
{
	m_NumericalData = data.m_NumericalData;
	m_ObjectData = data.m_ObjectData;
	m_Name = data.m_Name;

	switch( data.GetShaderParameterData().GetDataType() )
	{
	case nShaderParameterType_Float32:
	    m_Parameter = CShaderParameterData(m_NumericalData.Float32Data);
		break;

	case nShaderParameterType_Int32:
	    m_Parameter = CShaderParameterData(m_NumericalData.Int32Data);
		break;

	case nShaderParameterType_Vector2:
	    m_Parameter = CShaderParameterData(m_NumericalData.Vector2Data);
		break;

	case nShaderParameterType_Vector3:
	    m_Parameter = CShaderParameterData(m_NumericalData.Vector3Data);
		break;

	case nShaderParameterType_Vector4:
	    m_Parameter = CShaderParameterData(m_NumericalData.Vector4Data);
		break;

	case nShaderParameterType_Texture2d:
	    m_Parameter = CShaderParameterData( (CTexture2D&)*m_ObjectData);
		break;

	case nShaderParameterType_Texture3d:
	    m_Parameter = CShaderParameterData( (CTexture3D&)*m_ObjectData);
		break;

	case nShaderParameterType_TextureCube:
	    m_Parameter = CShaderParameterData( (CTextureCube&)*m_ObjectData);
		break;

	case nShaderParameterType_None:
		break;

	default:
		DebugError("Unsuported type");
	}
}

Void CMaterialParameter::SetValue( const Float32 data )
{
    m_NumericalData.Float32Data = data;
    m_Parameter = CShaderParameterData(m_NumericalData.Float32Data);
}

Void CMaterialParameter::SetValue( const STuple2f& data )
{
	SetValue( CVector2f( data.x, data.y ) );
}

Void CMaterialParameter::SetValue( const STuple3f& data )
{
	SetValue( CVector3f( data.x, data.y, data.z ) );
}

Void CMaterialParameter::SetValue( const STuple4f& data )
{
	SetValue( CVector4f( data.x, data.y, data.z, data.w  ) );
}

Void CMaterialParameter::SetValue( const CVector2f& data )
{
	m_NumericalData.Vector3Data.x = data.GetX();
	m_NumericalData.Vector3Data.y = data.GetY();
	m_Parameter = CShaderParameterData(m_NumericalData.Vector2Data);
}

Void CMaterialParameter::SetValue( const CVector3f& data )
{
    m_NumericalData.Vector3Data.x = data.GetX();
    m_NumericalData.Vector3Data.y = data.GetY();
    m_NumericalData.Vector3Data.z = data.GetZ();
    m_Parameter = CShaderParameterData(m_NumericalData.Vector3Data);
}

Void CMaterialParameter::SetValue( const CVector4f& data )
{
    m_NumericalData.Vector4Data.x = data.GetX();
    m_NumericalData.Vector4Data.y = data.GetY();
    m_NumericalData.Vector4Data.z = data.GetZ();
    m_NumericalData.Vector4Data.w = data.GetW();

    m_Parameter = CShaderParameterData(m_NumericalData.Vector4Data);
}

Void CMaterialParameter::SetValue( const CColor& data )
{
	m_NumericalData.Vector4Data.x = ( data.r );
	m_NumericalData.Vector4Data.y = ( data.g );
	m_NumericalData.Vector4Data.z = ( data.b );
	m_NumericalData.Vector4Data.w = ( data.a );
    m_Parameter = CShaderParameterData(m_NumericalData.Vector4Data);
}

Void CMaterialParameter::SetValue( const Int32 data )
{
    m_NumericalData.Int32Data = data;
    m_Parameter = CShaderParameterData(m_NumericalData.Int32Data);
}

Void CMaterialParameter::SetValue( const CTexture2D& data )
{
    m_ObjectData = (CTexture*) &data;
    m_Parameter = CShaderParameterData((CTexture2D&)*m_ObjectData);
}

Void CMaterialParameter::SetValue( const CStatesSampler& sampler )
{
	m_ObjectData = (CStatesSampler*) &sampler;
	m_Parameter = CShaderParameterData((CStatesSampler&)*m_ObjectData);
}

Void CMaterialParameter::SetValue( const CTexture3D& data )
{
    m_ObjectData = (CTexture*) &data;
    m_Parameter = CShaderParameterData((CTexture3D&)*m_ObjectData);
}

Void CMaterialParameter::SetValue( const CTextureCube& data )
{
    m_ObjectData = (CTexture*) &data;
    m_Parameter = CShaderParameterData((CTextureCube&)*m_ObjectData);
}

Bool CMaterialParameter::Serialize( CPersistentArchive& ar )
{
	Int16 version = 0;
	UInt32 dataType = m_Parameter.GetDataType();

	if( ar.BeginScope( WT("MaterialParameters"), version ) == version )
	{
		ar.Serialize( dataType, WT("Type") );

		ar.Serialize( m_Name, WT("Name") );
		ar.Serialize( (Byte*)&m_NumericalData, sizeof( SNumericalData ), WT("NumData") );
		ar.Serialize( m_ObjectData, WT("ObjectData") );

		ar.EndScope();

		if( m_ObjectData )
		{
			if( m_ObjectData->GetTypeInfo().IsKindOf( CTexture3D::GetStaticTypeInfo() ) )
			{
				int a = 0;
			}
		}

		if( ar.IsLoading() )
		{
			BindShaderParameterFromType( (EShaderParameterType) dataType );
		}

		return TRUE;
	}

	return FALSE;
}

Void CMaterialParameter::BindShaderParameterFromType( EShaderParameterType type )
{
	switch( type )
	{
	case nShaderParameterType_Float32:
		SetValue( m_NumericalData.Float32Data );
		break;

	case nShaderParameterType_Int32:
		SetValue( m_NumericalData.Int32Data );
		break;

	case nShaderParameterType_Vector3:
		SetValue( m_NumericalData.Vector3Data );
		break;

	case nShaderParameterType_Vector4:
		SetValue( m_NumericalData.Vector4Data );
		break;

	case nShaderParameterType_Texture2d:
		{
			CTexture2D* t = SafeCastRef( m_ObjectData, CTexture2D );
			SetValue( *t );
		}
		break;

	case nShaderParameterType_Texture3d:
		{
			CTexture3D* t = SafeCastRef( m_ObjectData, CTexture3D );
			SetValue( *t );
		}
		break;

	case nShaderParameterType_TextureCube:
		{
			CTextureCube* t = SafeCastRef( m_ObjectData, CTextureCube );
			SetValue( *t );
		}
		break;

	case nShaderParameterType_Sampler:
		{
			CStatesSampler* t = SafeCastRef( m_ObjectData, CStatesSampler );
			SetValue( *t );
		}
		break;

	default:
		DebugError("Unsupported type");
	}
}

String CMaterialParameter::GetName() const
{
	return m_Name;
}