struct VSInput
{
    float4 Position 	: POSITION;
    float2 UV0       	: TEXCOORD0;
};

struct VSOutput
{
    float4 HPosition    : POSITION;
    float2 UV0      	: TEXCOORD0;
};

struct PSInput
{
    float2 UV0      	: TEXCOORD0;
};

texture Texture_Input0; 
sampler2D Texture_Input0Sampler = sampler_state 
{ 
    Texture = <Texture_Input0>;
};

uniform float4 	
	TextureCoordinate_Offset[ 4 ];
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
	float 
		average,
		maximum;
	float4 
		color;
	int
		sampleIndex;
	
	color = 0.0f;
	average = 0.0f;
	maximum = 0.0f;
	
	for( sampleIndex = 0; sampleIndex < 4; sampleIndex++ )
	{
		color = tex2D( Texture_Input0Sampler, input.UV0 + float2( TextureCoordinate_Offset[ sampleIndex ].x, TextureCoordinate_Offset[ sampleIndex ].y ) );
		
		float GreyValue = dot( color.rgb, float3( 0.33f, 0.33f, 0.33f ) );
							   
		maximum = max( maximum, GreyValue );
		average += log( 1e-5 + GreyValue ); //1e-5 necessary to stop the singularity at GreyValue=0
	}
	
	average = exp( average / 4.0f ) ;
	
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
