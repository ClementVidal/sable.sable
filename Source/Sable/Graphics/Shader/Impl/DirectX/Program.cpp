#include <Sable\Graphics\Shader\Impl\DirectX\Program.h>

using namespace Sable;

CImplDirectXShaderProgram::CImplDirectXShaderProgram( CShaderProgram& publicImpl ) :
    CImplStubShaderProgram( publicImpl )
{
	m_SamplerCount = 0;
	m_CBufferCount = 0;
	m_TextureCount = 0;
}

CImplDirectXShaderProgram::~CImplDirectXShaderProgram()
{
}

Void CImplDirectXShaderProgram::ParseParameters( CImplDirectXShader& shader )
{
	UInt32 index, parameterCount;
	CStringIdentifier name;
	parameterCount  = GetParameterCount( );

	for( index = 0; index < parameterCount ; index++ )
	{
		GetParameterNameAtIndex( index, name );

		if( shader.m_PublicImpl->m_ParameterMap.HasItem( name ) == FALSE )
		{
			EShaderParameterType type = GetParameterDataType( name );
			DebugAssert( type != nShaderParameterType_None );

			{
				CShaderParameter& p = shader.m_PublicImpl->m_ParameterMap.AddItem( name );
				p.SetParameterDataType( type );
				p.SetArraySize( GetParameterArraySize( name ) );
				p.SetName( name );
				p.GetImpl().SetProgram( *this );
				p.SetShader( *shader.m_PublicImpl );
			}
		}
	}
}

Bool CImplDirectXShaderProgram::Initialize( )
{
    const Byte* data = m_PublicImpl->GetRawData().GetBuffer();
    UInt32 byteCount = m_PublicImpl->GetRawData().GetByteCount();

    if( m_PublicImpl->GetType() == nShaderProgramType_Vertex )
    {
        AssertDXCall( CImplDirectXGraphicsManagerHelper::GetDevice()->CreateVertexShader( data, byteCount, (ID3D10VertexShader **)&m_Program ) );
    }
    else if( m_PublicImpl->GetType() == nShaderProgramType_Pixel )
    {
        AssertDXCall( CImplDirectXGraphicsManagerHelper::GetDevice()->CreatePixelShader( data, byteCount, (ID3D10PixelShader **)&m_Program ) );
    }
    else if( m_PublicImpl->GetType() == nShaderProgramType_Geometry )
    {
        AssertDXCall( CImplDirectXGraphicsManagerHelper::GetDevice()->CreateGeometryShader( data, byteCount, (ID3D10GeometryShader **)&m_Program ) );
    }

	m_Reflection = NULL;
    AssertDXCall( D3D10ReflectShader( data, byteCount, &m_Reflection ) );
	ExtractParametersInfo();
    return TRUE;
}

Void CImplDirectXShaderProgram::FlushCBuffer()
{
	DebugGraphicCommandGroup( "CImplDirectXShaderProgram::FlushCBuffer" );
	for( UInt32 i=0 ;i<m_CBufferCount; i++ )
	{
		if( m_CBufferTable[i].IsDirty )
		{
			Byte* data;
			AssertDXCall( m_CBufferTable[i].Buffer->Map( D3D10_MAP_WRITE_DISCARD, 0, (void**)&data ) );
			MemoryCopy( m_CBufferTable[i].RawData.GetBuffer(), data, m_CBufferTable[i].RawData.GetItemCount() );
			m_CBufferTable[i].Buffer->Unmap();
			m_CBufferTable[i].IsDirty = FALSE;
		}
	}
}

Void CImplDirectXShaderProgram::Activate( )
{
    if( m_PublicImpl->GetType() == nShaderProgramType_Vertex )
    {
		for( UInt32 i=0 ;i<m_CBufferCount; i++ )
		{
			DebugAssert( m_CBufferTable[i].BindDesc.BindCount == 1 );
			CImplDirectXGraphicsManagerHelper::GetDevice()->VSSetConstantBuffers( m_CBufferTable[i].BindDesc.BindPoint, 1, &m_CBufferTable[i].Buffer );
		}
        CImplDirectXGraphicsManagerHelper::GetDevice()->VSSetShader( (ID3D10VertexShader *)m_Program );
    }
    else if( m_PublicImpl->GetType() == nShaderProgramType_Pixel )
    {
		for( UInt32 i=0 ;i<m_CBufferCount; i++ )
		{
			DebugAssert( m_CBufferTable[i].BindDesc.BindCount == 1 );
			CImplDirectXGraphicsManagerHelper::GetDevice()->PSSetConstantBuffers( m_CBufferTable[i].BindDesc.BindPoint, 1, &m_CBufferTable[i].Buffer );
		}
        CImplDirectXGraphicsManagerHelper::GetDevice()->PSSetShader( (ID3D10PixelShader *)m_Program );
    }
    else if( m_PublicImpl->GetType() == nShaderProgramType_Geometry )
    {
		for( UInt32 i=0 ;i<m_CBufferCount; i++ )
		{
			DebugAssert( m_CBufferTable[i].BindDesc.BindCount == 1 );
			CImplDirectXGraphicsManagerHelper::GetDevice()->GSSetConstantBuffers( m_CBufferTable[i].BindDesc.BindPoint, 1, &m_CBufferTable[i].Buffer );
		}
        CImplDirectXGraphicsManagerHelper::GetDevice()->GSSetShader( (ID3D10GeometryShader *)m_Program );
    }
}

Void CImplDirectXShaderProgram::ExtractParametersInfo()
{
	DebugGraphicCommandGroup( "CImplDirectXShaderProgram::ExtractParametersInfo" );

	UInt32 pCount = 0;

	D3D10_SHADER_DESC desc;
	m_Reflection->GetDesc( &desc );

    m_CBufferCount = 0;
    m_SamplerCount = 0;
    m_TextureCount = 0;

	for( UInt32 i=0;i<desc.BoundResources; i++ )
	{
		D3D10_SHADER_INPUT_BIND_DESC bindDesc;
		m_Reflection->GetResourceBindingDesc( i, &bindDesc );

		if( bindDesc.Type == D3D10_SIT_CBUFFER )
		{
			D3D10_SHADER_BUFFER_DESC bufferDesc;
			ID3D10ShaderReflectionConstantBuffer* reflectionCBuffer = m_Reflection->GetConstantBufferByName( bindDesc.Name );
			reflectionCBuffer->GetDesc( &bufferDesc );

			m_CBufferTable[m_CBufferCount].BindDesc = bindDesc;
			m_CBufferTable[m_CBufferCount].BufferDesc = bufferDesc;
			m_CBufferTable[m_CBufferCount].Buffer = CreateCBuffer( bufferDesc );

			m_CBufferTable[m_CBufferCount].Variables.SetItemCount( bufferDesc.Variables );

			m_CBufferTable[m_CBufferCount].RawData.SetItemCount( bufferDesc.Size );

			m_CBufferTable[m_CBufferCount].IsDirty = TRUE;

			// Pour chaque variables dans chaques CBuffer
			for( UInt32 j = 0;j<bufferDesc.Variables; j++ )
			{
				ID3D10ShaderReflectionVariable* var = reflectionCBuffer->GetVariableByIndex( j );
				D3D10_SHADER_VARIABLE_DESC varDesc;
				var->GetDesc( &varDesc );

				D3D10_SHADER_TYPE_DESC varTypeDesc;
				ID3D10ShaderReflectionType* type = var->GetType();
				type->GetDesc( &varTypeDesc );
				
				m_CBufferTable->Variables[j].TypeDesc = varTypeDesc;
				m_CBufferTable->Variables[j].VariableDesc = varDesc;
			}

			m_CBufferCount++;
		}
		else if( bindDesc.Type == D3D10_SIT_TEXTURE )
		{
			m_TextureTable[m_TextureCount++] = bindDesc;
		}
		else if( bindDesc.Type == D3D10_SIT_SAMPLER )
		{
			m_SamplerTable[m_SamplerCount++] = bindDesc;
		}
		else
		{
			DebugError("Unsuported resource binding");
		}
	}


	m_ParameterCount = 0;
	m_ParameterCount += m_SamplerCount + m_TextureCount;

	for( UInt32 i=0;i<m_CBufferCount;i++ )
	{
		m_ParameterCount += m_CBufferTable[i].BufferDesc.Variables;
	}

}

ID3D10Buffer* CImplDirectXShaderProgram::CreateCBuffer( const D3D10_SHADER_BUFFER_DESC& desc )
{
	DebugAssert( desc.Type == D3D10_CT_CBUFFER );
	D3D10_BUFFER_DESC cbDesc;
	cbDesc.ByteWidth = desc.Size;
	cbDesc.Usage = D3D10_USAGE_DYNAMIC;
	cbDesc.BindFlags = D3D10_BIND_CONSTANT_BUFFER;
	cbDesc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	cbDesc.MiscFlags = 0;

	ID3D10Buffer* buffer;
	// Create the buffer.
	AssertDXCall( CImplDirectXGraphicsManagerHelper::GetDevice()->CreateBuffer( &cbDesc, NULL, &buffer ) );

	return buffer;
}

UInt32 CImplDirectXShaderProgram::GetParameterCount( )
{
	return m_ParameterCount;
}

Void CImplDirectXShaderProgram::GetParameterNameAtIndex( UInt32 index, CStaticString<64>& name )
{
	UInt32 currentIndex = 0;
	// Pour chaque CBuffer
    for( UInt32 i = 0; i<m_CBufferCount; i++ )
	{
		// Pour chaque variables dans chaques CBuffer
		for( UInt32 j = 0;j<m_CBufferTable[i].BufferDesc.Variables; j++ )
		{
			if( currentIndex == index )
			{
				name = m_CBufferTable[i].Variables[j].VariableDesc.Name;
				return;
			}
			currentIndex++;
		}
	}

	// Pour chaque texture
	for( UInt32 i = 0; i<m_TextureCount; i++ )
	{
		if( currentIndex == index )
		{
			name = m_TextureTable[i].Name;
			return;
		}
		currentIndex++;
	}

	// Pour chaque sampler
	for( UInt32 i = 0; i<m_SamplerCount; i++ )
	{
		if( currentIndex == index )
		{
			name = m_SamplerTable[i].Name;
			return;
		}
		currentIndex++;
	}
}

EShaderParameterType CImplDirectXShaderProgram::ConvertType( const D3D10_SHADER_TYPE_DESC& type ) const
{
	if( type.Elements == 0 )
	{
		if( type.Class == D3D10_SVC_SCALAR )
		{
			if( type.Type == D3D10_SVT_FLOAT )
				return nShaderParameterType_Float32;
			else if( type.Type == D3D10_SVT_BOOL )
				return nShaderParameterType_Bool;
		}
		else if( type.Class == D3D10_SVC_VECTOR )
		{
			if( type.Type == D3D10_SVT_FLOAT )
			{
				if( type.Columns == 2 )
					return nShaderParameterType_Vector2;
				else if( type.Columns == 3 )
					return nShaderParameterType_Vector3;
				else if( type.Columns == 4 )
					return nShaderParameterType_Vector4;
			}
		}
		else if( type.Class == D3D10_SVC_MATRIX_ROWS )
		{
			if( type.Columns == 4 && type.Rows == 4 )
				return nShaderParameterType_Matrix4x4;
		}
		else if( type.Class == D3D10_SVC_MATRIX_COLUMNS )
		{
			if( type.Columns == 4 && type.Rows == 4 )
				return nShaderParameterType_Matrix4x4;
		}
	}
	else
	{
		if( type.Class == D3D10_SVC_SCALAR )
		{
			if( type.Type == D3D10_SVT_FLOAT )
				return nShaderParameterType_Float32Array;
		}
		else if( type.Class == D3D10_SVC_VECTOR )
		{
			if( type.Type == D3D10_SVT_FLOAT )
			{
				if( type.Columns == 2 )
					return nShaderParameterType_Vector2Array;
				else if( type.Columns == 3 )
					return nShaderParameterType_Vector3Array;
				else if( type.Columns == 4 )
					return nShaderParameterType_Vector4Array;
			}
		}
		else if( type.Class == D3D10_SVC_MATRIX_ROWS )
		{
		}	
	}

	DebugError("Invalid datatype");
	return nShaderParameterType_None;
}

EShaderParameterType CImplDirectXShaderProgram::GetParameterDataType( String semantic )
{
	UInt32 currentIndex = 0;
	// Pour chaque CBuffer
	for( UInt32 i = 0; i<m_CBufferCount; i++ )
	{
		// Pour chaque variables dans chaques CBuffer
		for( UInt32 j = 0;j<m_CBufferTable[i].BufferDesc.Variables; j++ )
		{
			if( !StringCompare( semantic, m_CBufferTable[i].Variables[j].VariableDesc.Name ) )
			{
				return ConvertType( m_CBufferTable[i].Variables[j].TypeDesc );
			}
			currentIndex++;
		}
	}

	// Pour chaque texture
	for( UInt32 i = 0; i<m_TextureCount; i++ )
	{
		if( !StringCompare( m_TextureTable[i].Name, semantic ) )
		{
			if( m_TextureTable[i].Dimension == D3D10_SRV_DIMENSION_TEXTURE1D )
				return nShaderParameterType_Texture1d;
			else if( m_TextureTable[i].Dimension == D3D10_SRV_DIMENSION_TEXTURE2D )
				return nShaderParameterType_Texture2d;
			else if( m_TextureTable[i].Dimension == D3D10_SRV_DIMENSION_TEXTURE3D )
				return nShaderParameterType_Texture3d;
			else if( m_TextureTable[i].Dimension == D3D10_SRV_DIMENSION_TEXTURECUBE )
				return nShaderParameterType_TextureCube;
		}
		currentIndex++;
	}

	// Pour chaque sampler
	for( UInt32 i = 0; i<m_SamplerCount; i++ )
	{
		if( !StringCompare( m_SamplerTable[i].Name, semantic ) )
		{
			return nShaderParameterType_Sampler;
		}
		currentIndex++;
	}

    return nShaderParameterType_None;
}

UInt8 CImplDirectXShaderProgram::GetParameterArraySize( String semantic )
{
    return 0;
}

Void CImplDirectXShaderProgram::SetSamplerParameterValue( const CShaderParameter& parameter, const CShaderParameterData& data) 
{
	ID3D10SamplerState* samplerState = data.GetSampler().GetImpl().GetD3DState();
	for( UInt32 i=0; i<m_SamplerCount; i++ )
	{
		if( !StringCompare( m_SamplerTable[i].Name, parameter.GetName() ) )
		{
			if( m_PublicImpl->GetType() == nShaderProgramType_Vertex )
			{
				DebugAssert( m_TextureTable[i].BindCount == 1 );
				CImplDirectXGraphicsManagerHelper::GetDevice()->VSSetSamplers( m_SamplerTable[i].BindPoint, 1, &samplerState );
			}
			else if( m_PublicImpl->GetType() == nShaderProgramType_Pixel )
			{
				DebugAssert( m_TextureTable[i].BindCount == 1 );
				CImplDirectXGraphicsManagerHelper::GetDevice()->PSSetSamplers( m_SamplerTable[i].BindPoint, 1, &samplerState );
			}
			else if( m_PublicImpl->GetType() == nShaderProgramType_Geometry )
			{
				DebugAssert( m_TextureTable[i].BindCount == 1 );
				CImplDirectXGraphicsManagerHelper::GetDevice()->GSSetSamplers( m_SamplerTable[i].BindPoint, 1, &samplerState );
			}
		}
	}
}

Void CImplDirectXShaderProgram::SetTextureParameterValue( const CShaderParameter& parameter, const CShaderParameterData& data) 
{
	ID3D10ShaderResourceView* rscView = NULL;
	if( parameter.GetParameterDataType() == nShaderParameterType_Texture1d )
	{
		DebugError("Invalid data type");
		//rscView = data.GetTexture2D().GetImpl().GetD3DTextureShaderView();
	}
	else if( parameter.GetParameterDataType() == nShaderParameterType_Texture2d )
	{
		rscView = data.GetTexture2D().GetImpl().GetD3DTextureShaderView();
	}
	else if( parameter.GetParameterDataType() == nShaderParameterType_Texture3d )
	{
		rscView = data.GetTexture3D().GetImpl().GetD3DTextureShaderView();
	}
	else if( parameter.GetParameterDataType() == nShaderParameterType_TextureCube )
	{
		rscView = data.GetTextureCube().GetImpl().GetD3DTextureShaderView();
	}

	if( !rscView )
	{
		DebugLogError( "CImplDirectXShaderProgram::SetTextureParameterValue - Invalid texture" );
		return;
	}

	for( UInt32 i=0; i<m_TextureCount; i++ )
	{
		if( !StringCompare( m_TextureTable[i].Name, parameter.GetName() ) )
		{
			if( m_PublicImpl->GetType() == nShaderProgramType_Vertex )
			{
				DebugAssert( m_TextureTable[i].BindCount == 1 );
				CImplDirectXGraphicsManagerHelper::GetDevice()->VSSetShaderResources( m_TextureTable[i].BindPoint, 1, &rscView );
			}
			else if( m_PublicImpl->GetType() == nShaderProgramType_Pixel )
			{
				DebugAssert( m_TextureTable[i].BindCount == 1 );
				CImplDirectXGraphicsManagerHelper::GetDevice()->PSSetShaderResources( m_TextureTable[i].BindPoint, 1, &rscView );
			}
			else if( m_PublicImpl->GetType() == nShaderProgramType_Geometry )
			{
				DebugAssert( m_TextureTable[i].BindCount == 1 );
				CImplDirectXGraphicsManagerHelper::GetDevice()->GSSetShaderResources( m_TextureTable[i].BindPoint, 1, &rscView );
			}

			return;
		}
	}
}

Void CImplDirectXShaderProgram::SetCBufferParameterValue( const CShaderParameter& parameter, const CShaderParameterData& data)
{
	for( UInt32 i=0;i<m_CBufferCount;i++ )
	{
		// Pour chaque variables dans chaques CBuffer
		for( UInt32 j = 0;j<m_CBufferTable[i].BufferDesc.Variables; j++ )
		{
			if( !StringCompare( parameter.GetName(), m_CBufferTable[i].Variables[j].VariableDesc.Name ) )
			{
				const D3D10_SHADER_VARIABLE_DESC& vDesc = m_CBufferTable[i].Variables[j].VariableDesc;
				if( parameter.GetParameterDataType() == nShaderParameterType_Vector2 )
				{
					DebugAssert( vDesc.Size == sizeof( CVector2f ) );
					MemoryCopy(  &data.GetVector2(), m_CBufferTable[i].RawData.GetBuffer() + vDesc.StartOffset, vDesc.Size );
				}
				else if( parameter.GetParameterDataType() == nShaderParameterType_Vector3 )
				{
					DebugAssert( vDesc.Size == sizeof( CVector3f ) );
					MemoryCopy( &data.GetVector3(), m_CBufferTable[i].RawData.GetBuffer() + vDesc.StartOffset, vDesc.Size );
				}
				else if( parameter.GetParameterDataType() == nShaderParameterType_Vector4 )
				{
					DebugAssert( vDesc.Size == sizeof( CVector4f ) );
					MemoryCopy( &data.GetVector4(), m_CBufferTable[i].RawData.GetBuffer() + vDesc.StartOffset, vDesc.Size );
				}
				else if( parameter.GetParameterDataType() == nShaderParameterType_Float32 )
				{
					DebugAssert( vDesc.Size == sizeof( Float32 ) );
					MemoryCopy( &data.GetFloat32(), m_CBufferTable[i].RawData.GetBuffer() + vDesc.StartOffset, vDesc.Size );
				}	
				else if( parameter.GetParameterDataType() == nShaderParameterType_Int32 )
				{
					DebugAssert( vDesc.Size == sizeof( Int32 ) );
					MemoryCopy( &data.GetInt32(), m_CBufferTable[i].RawData.GetBuffer() + vDesc.StartOffset, vDesc.Size );
				}	
				else if( parameter.GetParameterDataType() == nShaderParameterType_Bool )
				{
					DebugAssert( vDesc.Size == sizeof( Bool ) );
					MemoryCopy( &data.GetBool(), m_CBufferTable[i].RawData.GetBuffer() + vDesc.StartOffset, vDesc.Size );
				}	
				else if( parameter.GetParameterDataType() == nShaderParameterType_Matrix4x4 )
				{
					DebugAssert( vDesc.Size == sizeof( CMatrix4x4f ) );
					MemoryCopy( &data.GetMatrix4x4(), m_CBufferTable[i].RawData.GetBuffer() + vDesc.StartOffset, vDesc.Size );
				}	
				else
				{
					DebugError("Unsupported datatype");
				}
				m_CBufferTable[i].IsDirty = TRUE;
			}
		}
	}
}

Void CImplDirectXShaderProgram::SetParameterValue( const CShaderParameter& parameter, const CShaderParameterData& data) 
{
	if( parameter.GetParameterDataType() == nShaderParameterType_Sampler )
	{
		SetSamplerParameterValue( parameter, data );
	}
	else if(	parameter.GetParameterDataType() == nShaderParameterType_TextureCube ||
				parameter.GetParameterDataType() == nShaderParameterType_Texture1d ||
				parameter.GetParameterDataType() == nShaderParameterType_Texture2d ||
				parameter.GetParameterDataType() == nShaderParameterType_Texture3d )
	{
		SetTextureParameterValue( parameter, data );
	}
	else
	{
		SetCBufferParameterValue( parameter, data );
	}

	FlushCBuffer();
}