
struct PSInput
{
    float2 UV0      : TEXCOORD0;
};

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
	TextureCoordinateOffset[ 16 ];
uniform float3
	TexelToPixelPositionOffset;
	
float4 PSMain( PSInput input ) : COLOR0
{
	int
		sampleIndex;
	float4
		average;
	float
		luminance;
	
	average = float4( 0,0,0,0 );
	
	for( sampleIndex = 0; sampleIndex < 16; sampleIndex++ )
	{
		average += tex2D( InputTextureSampler, input.UV0 + float2( TextureCoordinateOffset[ sampleIndex ].x, TextureCoordinateOffset[ sampleIndex ].y ) );
	}
	
	average *= ( 1.0f / 16.0f );
	
    return average * average.a;
}

VSOutput VSMain( VSInput input )
{
	VSOutput 
		output;

	output.HPosition.xyz 	= 	input.Position - TexelToPixelPositionOffset;
	output.HPosition.w 	= 	1.0;

	output.UV0 = input.UV0;

	return output;
}

technique MainTechnique
{
	pass P0
	{
		VertexShader = compile vs_3_0 VSMain();
        PixelShader  = compile ps_3_0 PSMain();
	}
}
