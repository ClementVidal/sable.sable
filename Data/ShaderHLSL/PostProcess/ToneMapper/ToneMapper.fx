
// Define outputs from vertex shader.
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

texture Texture_OriginalScene; 
sampler2D Sampler_OriginalScene = sampler_state 
{ 
    Texture = <Texture_OriginalScene>;
};

texture Texture_Luminance; 
sampler2D Sampler_Luminance = sampler_state 
{ 
    Texture = <Texture_Luminance>;
};

texture Texture_Glow_0; 
sampler2D Sampler_Glow_0 = sampler_state 
{ 
    Texture = <Texture_Glow_0>;
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
	AddressU = BORDER;
	AddressV = BORDER;
};

texture Texture_Glow_1; 
sampler2D Sampler_Glow_1 = sampler_state 
{ 
    Texture = <Texture_Glow_1>;
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
	AddressU = BORDER;
	AddressV = BORDER;
};

texture Texture_Glow_2; 
sampler2D Sampler_Glow_2 = sampler_state 
{ 
    Texture = <Texture_Glow_2>;
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
	AddressU = BORDER;
	AddressV = BORDER;
};

texture Texture_Glow_3; 
sampler2D Sampler_Glow_3 = sampler_state 
{ 
    Texture = <Texture_Glow_3>;
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
	AddressU = BORDER;
	AddressV = BORDER;
};

uniform float4 
	ToneMapper_Exposure ;
	
uniform bool
	ToneMapper_UseGlow;
	
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
		originalScene,
		luminance,
		finalColor,
		glowColor0,
		glowColor1,
		glowColor2,
		glowColor3;

	float 
		Lp,
		LmSqr,
		toneScalar;
				
	glowColor0 = 0.0f;
	glowColor1 = 0.0f;
	glowColor2 = 0.0f;
	glowColor3 = 0.0f;

	if( ToneMapper_UseGlow )
	{
		glowColor0 = tex2D( Sampler_Glow_0, input.UV0 ) ;
		glowColor1 = tex2D( Sampler_Glow_1, input.UV0 ) ;
		glowColor2 = tex2D( Sampler_Glow_2, input.UV0 ) ;
		glowColor3 = tex2D( Sampler_Glow_3, input.UV0 ) ;	
	}
		
    originalScene = tex2D( Sampler_OriginalScene, input.UV0 ) ;
    luminance = tex2D( Sampler_Luminance, float2( 0.5f, 0.5f ) ) ;

	finalColor = originalScene ; 
	
	Lp = ( ToneMapper_Exposure.x / luminance.r) * max( finalColor.r, max( finalColor.g,finalColor.b ) );
	
	Lp  = max( 0.0f, Lp );
	LmSqr = ( luminance.g + 0.0 * luminance.g ) * ( luminance.g + 1.0 * luminance.g );
	
	toneScalar = ( Lp * ( 1.0f + ( Lp / ( LmSqr ) ) ) ) / ( 1.0f + Lp );

	finalColor =   finalColor * toneScalar + 
			( 	//glowColor0 
				glowColor1 * 0.01 +
				glowColor2 * 0.01 +
				glowColor3 
				) ;
	
	finalColor.a = 1.0; 
		
    return  finalColor;
}

technique MainTechnique
{
	pass P0
	{
		VertexShader = compile vs_3_0 VSMain();
        PixelShader  = compile ps_3_0 PSMain();
	}
}
