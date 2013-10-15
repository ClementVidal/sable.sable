struct PSInput
{
    float2 UV0      : TEXCOORD0;
};

struct VSInput
{
    float4 Position : POSITION;
    float2 UV0       : TEXCOORD0;
};

struct VSOutput
{
    float4 HPosition    : POSITION;
    float2 UV0      : TEXCOORD0;
};

uniform float3
	TexelToPixelPositionOffset;
uniform float4 	
	TextureCoordinate_Offset[ 9 ];

texture Texture_Input0; 
sampler2D Texture_Input0Sampler = sampler_state 
{ 
    Texture = <Texture_Input0>;
};

VSOutput VSMain( VSInput input )
{
	VSOutput
		output;

	output.HPosition.xyz 	= 	input.Position - TexelToPixelPositionOffset;
	output.HPosition.w 		= 	1.0;

	output.UV0 = input.UV0;

	return output;
}

float4 PSMain( VSInput input ) : COLOR0
{
        float4 
			color = 0.0f;
        float 
			maximum = -1e20;
        float 
			average = 0.0f;
        int
			sampleIndex;
		
        for( sampleIndex = 0; sampleIndex < 9; sampleIndex++ )
        {
	        color = tex2D( Texture_Input0Sampler,  input.UV0 + float2( TextureCoordinate_Offset[ sampleIndex ].x, TextureCoordinate_Offset[ sampleIndex ].y ) );
            average += color.r;
            maximum = max( maximum, color.g );
        }
        
        average /= 9.0f;
        
        return float4( average, maximum, 0.0f, 1.0f );
}

technique MainTechnique
{
	pass P0
	{
		VertexShader = compile vs_3_0 VSMain();
        PixelShader  = compile ps_3_0 PSMain();
	}
}