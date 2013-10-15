#include <Sable\Graphics\Shader\SystemConnector.h>

#define ShaderConnector_MaximumInputTexture 4

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1( Sable, CShaderSystemConnector, CManagedObject );

CShaderSystemConnector::CShaderSystemConnector( )
{
}

CShaderSystemConnector::~CShaderSystemConnector()
{
}

Void CShaderSystemConnector::FlushParametersValues( CShader& shader ) const
{
	const CShader::ParameterMap& pMap = shader.GetParameterMap();
	CShader::ParameterMap::Iterator it;

	ForEachItem( it, pMap )
	{
		FlushParametersValues( *it );
	}
}

Void CShaderSystemConnector::FlushParametersValues( CShaderParameter& parameter ) const
{
	if( !GetItSupportParameter( parameter  ) )
		return;

	switch( parameter.GetParameterDataType() )
	{

	case nShaderParameterType_Bool:
		{
			DebugProfile( "Connect Bool" );
			Bool data;
			EvaluateParameterValue( parameter, data );
			parameter.SetValue( data );
		}
		return;

	case nShaderParameterType_Float32Array:
		{
			DebugProfile( "Connect Float32array" );
			CArray<Float32>	data;
			EvaluateParameterValue( parameter, data );
			parameter.SetValue( data );
		}
		return;

	case nShaderParameterType_Float32:
		{
			DebugProfile( "Connect Float32" );
			Float32 data;
			EvaluateParameterValue( parameter, data );
			parameter.SetValue( data );
		}
		return;

	case nShaderParameterType_Int32:
		{
			DebugProfile( "Connect Int32" );
			Int32 data;
			EvaluateParameterValue( parameter, data );
			parameter.SetValue( data );
		}
		return;

	case nShaderParameterType_Matrix4x4:
		{
			DebugProfile( "Connect Matrix4x4" );
			CMatrix4x4f data;
			EvaluateParameterValue( parameter, data );
			parameter.SetValue( data );
		}
		return;

	case nShaderParameterType_Texture2d:
		{
			DebugProfile( "Connect Texture2D" );
			CRef<CTexture> data;
			EvaluateParameterValue( parameter, data );
			if(data)
				parameter.SetValue( (CTexture2D&) *data );
		}
		return;

	case nShaderParameterType_RenderTargetTexture:
		{
			DebugProfile( "Connect RenderTarget" );
			CRef<CRenderTargetTexture> data;
			EvaluateParameterValue( parameter, data );
			if(data)
				parameter.SetValue( (CRenderTargetTexture&) *data );
		}
		return;


	case nShaderParameterType_Texture3d:
		{
			DebugProfile( "Connect Texture3D" );
			CRef<CTexture> data;
			EvaluateParameterValue( parameter, data );
			if(data)
				parameter.SetValue( (CTexture3D&) *data );
		}
		return;

	case nShaderParameterType_TextureCube:
		{
			DebugProfile( "Connect TextureCube" );

			CRef<CTexture> data;
			EvaluateParameterValue( parameter, data );
			if(data)
				parameter.SetValue( (CTextureCube&) *data );
		}
		return;

	case nShaderParameterType_Vector3Array:
		{
			DebugProfile( "Connect Vector3Array" );
			CArray<CVector3f> data;
			EvaluateParameterValue( parameter, data );
			parameter.SetValue( data );
		}
		return;

	case nShaderParameterType_Vector3:
		{
			DebugProfile( "Connect Vector3" );
			CVector3f data;
			EvaluateParameterValue( parameter, data );
			parameter.SetValue( data );
		}
		return;

	case nShaderParameterType_Vector4:
		{
			DebugProfile( "Connect Vector4" );
			CVector4f data;
			EvaluateParameterValue( parameter, data );
			parameter.SetValue( data );
		}
		return;

	case nShaderParameterType_Vector4Array:
		{
			DebugProfile( "Connect Vector4Array" );
			CArray<CVector4f> data;
			EvaluateParameterValue( parameter, data );
			parameter.SetValue( data );
		}
		return;

	}

	DebugError("Unable to connect parameter value, undefined type");
}

Bool CShaderSystemConnector::CheckHashesUniqueness( HashValue* hashes, UInt32 count )const
{
	UInt32 i,j;
	for( i=0;i<count;i++ )
	{
		for( j=0;j<count;j++ )
		{
			if( j != i && hashes[i] == hashes[j] )
				return FALSE;
		}
	}
	return TRUE;
}

/**
Return TRUE if a specific parameter can be handled by the connector.\n
This method MUST be redefined correctly in all sub classes otherwise the
system won't be able to bind correctly the connectors to the parameters.
\param semantic The semantic identifying the parameter.
*/
Bool CShaderSystemConnector::GetItSupportParameter( const CShaderParameter& param  )const
{
	return FALSE;
}

/**
Evaluate the value of a parameter.
\param[in] semantic The semantic of the parameter.
\param[in] data The computed value of the parameter.
*/
Void CShaderSystemConnector::EvaluateParameterValue( const CShaderParameter& param, CArray<Float32>& data ) const
{
	DebugError( "Must Be implemented in inherited classes" );
}

/**
Evaluate the value of a parameter.
\param[in] semantic The semantic of the parameter.
\param[in] data The computed value of the parameter.
*/
Void CShaderSystemConnector::EvaluateParameterValue( const CShaderParameter& param, Float32& data ) const
{
	DebugError( "Must Be implemented in inherited classes" );
}

/**
Evaluate the value of a parameter.
\param[in] semantic The semantic of the parameter.
\param[in] data The computed value of the parameter.
*/
Void CShaderSystemConnector::EvaluateParameterValue( const CShaderParameter& param, Bool& data ) const
{
	DebugError( "Must Be implemented in inherited classes" );
}

/**
Evaluate the value of a parameter.
\param[in] semantic The semantic of the parameter.
\param[in] data The computed value of the parameter.
*/
Void CShaderSystemConnector::EvaluateParameterValue( const CShaderParameter& param, Int32& data ) const
{
	DebugError( "Must Be implemented in inherited classes" );
}

/**
Evaluate the value of a parameter.
\param[in] semantic The semantic of the parameter.
\param[in] data The computed value of the parameter.
*/
Void CShaderSystemConnector::EvaluateParameterValue( const CShaderParameter& param, CMatrix4x4f& data ) const
{
	DebugError( "Must Be implemented in inherited classes" );
}

/**
Evaluate the value of a parameter.
\param[in] semantic The semantic of the parameter.
\param[in] data The computed value of the parameter.
*/
Void CShaderSystemConnector::EvaluateParameterValue( const CShaderParameter& param, CRef<CRenderTargetTexture>& data ) const
{
	DebugError( "Must Be implemented in inherited classes" );
}

/**
Evaluate the value of a parameter.
\param[in] semantic The semantic of the parameter.
\param[in] data The computed value of the parameter.
*/
Void CShaderSystemConnector::EvaluateParameterValue( const CShaderParameter& param, CRef<CTexture>& data ) const
{
	DebugError( "Must Be implemented in inherited classes" );
}

/**
Evaluate the value of a parameter.
\param[in] semantic The semantic of the parameter.
\param[in] data The computed value of the parameter.
*/
Void CShaderSystemConnector::EvaluateParameterValue( const CShaderParameter& param, CArray<CVector4f>& data ) const
{
	DebugError( "Must Be implemented in inherited classes" );
}

/**
Evaluate the value of a parameter.
\param[in] semantic The semantic of the parameter.
\param[in] data The computed value of the parameter.
*/
Void CShaderSystemConnector::EvaluateParameterValue( const CShaderParameter& param, CArray<CVector3f>& data ) const
{
	DebugError( "Must Be implemented in inherited classes" );
}

/**
Evaluate the value of a parameter.
\param[in] semantic The semantic of the parameter.
\param[in] data The computed value of the parameter.
*/
Void CShaderSystemConnector::EvaluateParameterValue( const CShaderParameter& param, CVector3f& data ) const
{
	DebugError( "Must Be implemented in inherited classes" );
}

/**
Evaluate the value of a parameter.
\param[in] semantic The semantic of the parameter.
\param[in] data The computed value of the parameter.
*/
Void CShaderSystemConnector::EvaluateParameterValue( const CShaderParameter& param, CVector4f& data ) const
{
	DebugError( "Must Be implemented in inherited classes" );
}
