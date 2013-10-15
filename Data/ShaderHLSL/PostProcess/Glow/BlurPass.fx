
struct VSInput
{
    float4 Position		: POSITION;
    float2 UV0			: TEXCOORD0;
};

struct VSOutput
{
    float4 HPosition    : POSITION;
    float2 UV0			: TEXCOORD0;
};

struct PSInput
{
    float2 UV0      : TEXCOORD0;
};


texture InputTexture; 
sampler2D InputTextureSampler = sampler_state 
{ 
    Texture = <InputTexture>;
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
	AddressU = CLAMP;
	AddressV = CLAMP;
};

uniform float4 	
	TextureCoordinateOffset[ 5 ];
uniform float
	GaussianWeight[ 5 ];
uniform float3
	TexelToPixelPositionOffset;
	
VSOutput VSMain( VSInput input )
{
	VSOutput 
		output;

	output.HPosition.xyz 	= 	input.Position - TexelToPixelPositionOffset;
	output.HPosition.w 	= 	1.0;

	output.UV0 = input.UV0;

	return output;
}

float4 PSMain( PSInput input ) : COLOR0
{
	float4 
		color = { 0.0f, 0.0f, 0.0f, 0.0f };
	int
		sampleIndex;
    float2
		offset;
		
    for( sampleIndex = 0; sampleIndex < 5; sampleIndex++ )
    {
		offset = TextureCoordinateOffset[ sampleIndex ];
		
        color += ( 	tex2D( InputTextureSampler, input.UV0 + offset ) * GaussianWeight[ sampleIndex ] );
    }
        
    return float4( color.rgb, 1.0f );
}


technique MainTechnique
{
	pass P0
	{
		VertexShader = compile vs_3_0 VSMain();
        PixelShader  = compile ps_3_0 PSMain();
	}
}