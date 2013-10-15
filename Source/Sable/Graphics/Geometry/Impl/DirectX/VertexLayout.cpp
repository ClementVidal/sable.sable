#include <Sable\Graphics\Geometry\Impl\DirectX\VertexLayout.h>

#include <Sable\Graphics\Geometry\VertexLayout.h>
#include <Sable\Graphics\Common\Impl\DirectX\GraphicsManager.h>
#include <Sable\Graphics\Common\Impl\DirectX\GraphicsManagerHelper.h>

using namespace Sable;

CImplDirectXVertexLayout::CImplDirectXVertexLayout( CGeometryVertexLayout& publicImpl ):
    CImplStubVertexLayout( publicImpl )
{
	m_InputLayout = NULL;
}

CImplDirectXVertexLayout::~CImplDirectXVertexLayout()
{
	if( m_InputLayout )
	{
		UInt32 r  = m_InputLayout->Release();
        //REFACTORDX10
		//DebugAssert( r == 0 );
	}
	m_InputLayout = NULL;
}

Void CImplDirectXVertexLayout::Activate( )
{
	ID3D10Device* device = CImplDirectXGraphicsManagerHelper::GetDevice();

	device->IASetInputLayout( m_InputLayout );
}

Void CImplDirectXVertexLayout::UnInitialize( )
{
	if( m_InputLayout )
	{
		UInt32 r  = m_InputLayout->Release();
        //REFACTORDX10
        //DebugAssert( r == 0 );
	}
	m_InputLayout = NULL;
}

Void CImplDirectXVertexLayout::Initialize( )
{
	D3D10_INPUT_ELEMENT_DESC	inputElements[33];
	UInt16  Id = 0;

    CStaticString<64>   semanticString[nVertexComponent_Count];
    semanticString[nVertexComponent_Position] = "POSITION";
    semanticString[nVertexComponent_TexCoord0] = "TEXCOORD";
    semanticString[nVertexComponent_TexCoord1] = "TEXCOORD";
    semanticString[nVertexComponent_TexCoord2] = "TEXCOORD";
    semanticString[nVertexComponent_TexCoord3] = "TEXCOORD";
    semanticString[nVertexComponent_TexCoord4] = "TEXCOORD";
    semanticString[nVertexComponent_TexCoord5] = "TEXCOORD";
    semanticString[nVertexComponent_TexCoord6] = "TEXCOORD";
    semanticString[nVertexComponent_TexCoord7] = "TEXCOORD";
	semanticString[nVertexComponent_Color0] = "COLOR";
	semanticString[nVertexComponent_Color1] = "COLOR";
    semanticString[nVertexComponent_Normal] = "NORMAL";
    semanticString[nVertexComponent_Tangent] = "TANGENT";
    semanticString[nVertexComponent_BiNormal] = "BINORMAL";

	if( m_PublicImpl->HasElement( nVertexComponent_Position ) )
	{
		const CGeometryVertexElement& element = m_PublicImpl->GetElementAtSemantic( nVertexComponent_Position );

		inputElements[Id].SemanticName		= semanticString[nVertexComponent_Position].GetBuffer();
		inputElements[Id].SemanticIndex		= 0;
		inputElements[Id].Format			= TranslateElementType( element.Type );
		inputElements[Id].InputSlot		    = element.StreamIndex;
        inputElements[Id].AlignedByteOffset = element.ByteOffset;
        inputElements[Id].InputSlotClass    = element.IsPerInstanceData?D3D10_INPUT_PER_INSTANCE_DATA:D3D10_INPUT_PER_VERTEX_DATA;
        inputElements[Id].InstanceDataStepRate	= element.IsPerInstanceData?1:0;

		Id++;
	}	
	if( m_PublicImpl->HasElement( nVertexComponent_Normal ) )
	{
		const CGeometryVertexElement& element = m_PublicImpl->GetElementAtSemantic( nVertexComponent_Normal );

        inputElements[Id].SemanticName		= semanticString[nVertexComponent_Normal].GetBuffer();
        inputElements[Id].SemanticIndex		= 0;
        inputElements[Id].Format			= TranslateElementType( element.Type );
        inputElements[Id].InputSlot		    = element.StreamIndex;
        inputElements[Id].AlignedByteOffset = element.ByteOffset;
        inputElements[Id].InputSlotClass    = element.IsPerInstanceData?D3D10_INPUT_PER_INSTANCE_DATA:D3D10_INPUT_PER_VERTEX_DATA;
        inputElements[Id].InstanceDataStepRate	= element.IsPerInstanceData?1:0;

		Id++;
	}
	if( m_PublicImpl->HasElement( nVertexComponent_BiNormal ) )
	{
		const CGeometryVertexElement& element = m_PublicImpl->GetElementAtSemantic( nVertexComponent_BiNormal );

        inputElements[Id].SemanticName		= semanticString[nVertexComponent_BiNormal].GetBuffer();
        inputElements[Id].SemanticIndex		= 0;
        inputElements[Id].Format			= TranslateElementType( element.Type );
        inputElements[Id].InputSlot		    = element.StreamIndex;
        inputElements[Id].AlignedByteOffset = element.ByteOffset;
        inputElements[Id].InputSlotClass    = element.IsPerInstanceData?D3D10_INPUT_PER_INSTANCE_DATA:D3D10_INPUT_PER_VERTEX_DATA;
        inputElements[Id].InstanceDataStepRate	= element.IsPerInstanceData?1:0;

		Id++;
	}
	if( m_PublicImpl->HasElement( nVertexComponent_Tangent ) )
	{
		const CGeometryVertexElement& element = m_PublicImpl->GetElementAtSemantic( nVertexComponent_Tangent );

        inputElements[Id].SemanticName		= semanticString[nVertexComponent_Tangent].GetBuffer();
        inputElements[Id].SemanticIndex		= 0;
        inputElements[Id].Format			= TranslateElementType( element.Type );
        inputElements[Id].InputSlot		    = element.StreamIndex;
        inputElements[Id].AlignedByteOffset = element.ByteOffset;
        inputElements[Id].InputSlotClass    = element.IsPerInstanceData?D3D10_INPUT_PER_INSTANCE_DATA:D3D10_INPUT_PER_VERTEX_DATA;
        inputElements[Id].InstanceDataStepRate	= element.IsPerInstanceData?1:0;

		Id++;
	}

    for( UInt32 i=0;i<7;i++ )
    {
        EVertexComponent uvSemantic = (EVertexComponent)(nVertexComponent_TexCoord0 + i);
	    if( m_PublicImpl->HasElement( uvSemantic ) )
	    {
		    const CGeometryVertexElement& element = m_PublicImpl->GetElementAtSemantic( uvSemantic );

            inputElements[Id].SemanticName		= semanticString[uvSemantic].GetBuffer();
            inputElements[Id].SemanticIndex		= i;
            inputElements[Id].Format			= TranslateElementType( element.Type );
            inputElements[Id].InputSlot		    = element.StreamIndex;
            inputElements[Id].AlignedByteOffset = element.ByteOffset;
            inputElements[Id].InputSlotClass    = element.IsPerInstanceData?D3D10_INPUT_PER_INSTANCE_DATA:D3D10_INPUT_PER_VERTEX_DATA;
            inputElements[Id].InstanceDataStepRate	= element.IsPerInstanceData?1:0;

		    Id++;
	    }
    }

	if( m_PublicImpl->HasElement( nVertexComponent_Color0 ) )
	{
		const CGeometryVertexElement& element = m_PublicImpl->GetElementAtSemantic( nVertexComponent_Color0 );

        inputElements[Id].SemanticName		= semanticString[nVertexComponent_Color0].GetBuffer();
        inputElements[Id].SemanticIndex		= 0;
        inputElements[Id].Format			= TranslateElementType( element.Type );
        inputElements[Id].InputSlot		    = element.StreamIndex;
        inputElements[Id].AlignedByteOffset = element.ByteOffset;
        inputElements[Id].InputSlotClass    = element.IsPerInstanceData?D3D10_INPUT_PER_INSTANCE_DATA:D3D10_INPUT_PER_VERTEX_DATA;
        inputElements[Id].InstanceDataStepRate	= element.IsPerInstanceData?1:0;

		Id++;
	}

    CString effectSrc = BuildDummyEffect( *m_PublicImpl );

    ID3D10Device* device = CImplDirectXGraphicsManagerHelper::GetDevice();
    ID3D10Blob* effectBuffer;
    ID3D10Blob* errorBuffer;
    if( D3D10CompileEffectFromMemory( (void*)effectSrc.GetBuffer(), effectSrc.GetLength(), "DummyEffect", NULL, NULL, D3D10_SHADER_ENABLE_STRICTNESS, 0, &effectBuffer, &errorBuffer ) != S_OK )
    {
        CString errorString = (const  char*) errorBuffer->GetBufferPointer();
        DebugError("");
    }
    else
    {
        ID3D10Effect* effect;
        AssertDXCall( D3D10CreateEffectFromMemory( effectBuffer->GetBufferPointer(), effectBuffer->GetBufferSize(), 0, device, NULL, &effect ) );

        D3D10_PASS_DESC desc;
        effect->GetTechniqueByIndex( 0 )->GetPassByIndex(0)->GetDesc( &desc );
	    // VertexDeclCreation
	    AssertDXCall( device->CreateInputLayout( inputElements, Id, desc.pIAInputSignature, desc.IAInputSignatureSize, &m_InputLayout ) );
    }
}

String CImplDirectXVertexLayout::ConvertElementTypeToString( EVertexComponentType type )
{
	static String typeName[3] = {"float2", "float3", "float4" };

	return typeName[type];
}

CString CImplDirectXVertexLayout::BuildDummyEffect( CGeometryVertexLayout& descriptor )
{
    CString elementList;

    CString effect;
    if( descriptor.HasElement( nVertexComponent_Position ) )
    {
        const CGeometryVertexElement& element = descriptor.GetElementAtSemantic( nVertexComponent_Position );
		elementList.Append( ConvertElementTypeToString( element.Type ) );
        elementList.Append( " Position0 : POSITION0;" );
    }	
    if( descriptor.HasElement( nVertexComponent_Normal ) )
	{
		const CGeometryVertexElement& element = descriptor.GetElementAtSemantic( nVertexComponent_Normal );
		elementList.Append( ConvertElementTypeToString( element.Type ) );
        elementList.Append( " Normal0 : NORMAL0;" );
    }
    if( descriptor.HasElement( nVertexComponent_BiNormal ) )
	{
		const CGeometryVertexElement& element = descriptor.GetElementAtSemantic( nVertexComponent_BiNormal );
		elementList.Append( ConvertElementTypeToString( element.Type ) );
        elementList.Append( " BiNormal0 : BINORMAL0;" );
    }
    if( descriptor.HasElement( nVertexComponent_Tangent ) )
	{
		const CGeometryVertexElement& element = descriptor.GetElementAtSemantic( nVertexComponent_Tangent );
		elementList.Append( ConvertElementTypeToString( element.Type ) );
        elementList.Append( " Tangent0 : TANGENT0;" );
    }

    for( UInt32 i=0;i<7;i++ )
    {
        EVertexComponent uvSemantic = (EVertexComponent)(nVertexComponent_TexCoord0 + i);
        if( descriptor.HasElement( uvSemantic ) )
        {
			CString tmp;
            const CGeometryVertexElement& element = descriptor.GetElementAtSemantic( uvSemantic );

			elementList.Append( ConvertElementTypeToString( element.Type ) );
  
            tmp.WriteFormattedText( " TexCoord%d : TEXCOORD%d;", i, i );
         
            elementList.Append( tmp );
        }
    }

    if( descriptor.HasElement( nVertexComponent_Color0 ) )
	{
		const CGeometryVertexElement& element = descriptor.GetElementAtSemantic( nVertexComponent_Color0 );
		elementList.Append( ConvertElementTypeToString( element.Type ) );
        elementList.Append( " Color0 : COLOR0;" );
    }

	if( descriptor.HasElement( nVertexComponent_Color1 ) )
	{
		const CGeometryVertexElement& element = descriptor.GetElementAtSemantic( nVertexComponent_Color1 );
		elementList.Append( ConvertElementTypeToString( element.Type ) );
		elementList.Append( " Color0 : COLOR1;" );
	}

    effect.Append( "struct VSInput \
                   {" );
    effect.Append( elementList );
    effect.Append( "}; \
                    struct VSOutput \
                    { \
                        float4 Position : POSITION; \
                    }; \
                    VSOutput VSMain( VSInput input ) \
                    { \
                        VSOutput output; \
                        return output; \
                    } \
                    technique10  MainTechnique  \
                    { \
                        pass P0 \
                        { \
                            SetVertexShader( CompileShader( vs_4_0, VSMain() ) ); \
                            SetPixelShader( NULL );		 \
                            SetGeometryShader( NULL ); \
                        } \
                    }" );

    return effect;

}

DXGI_FORMAT	CImplDirectXVertexLayout::TranslateElementType( EVertexComponentType type )
{
	switch( type )
	{
	case nVertexComponentType_Float2:
		return DXGI_FORMAT_R32G32_FLOAT;

	case nVertexComponentType_Float3:
		return DXGI_FORMAT_R32G32B32_FLOAT;

	case nVertexComponentType_Float4:
		return DXGI_FORMAT_R32G32B32A32_FLOAT;
	}

	return DXGI_FORMAT_UNKNOWN;
}

Bool CImplDirectXVertexLayout::IsInitialized() const
{
	return m_InputLayout != NULL;
}

