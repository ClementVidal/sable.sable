
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
    MipFilter = POINT;
    MinFilter = POINT;
    MagFilter = POINT;
	AddressU = BORDER;
	AddressV = BORDER;
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

texture Texture_Blend0; 
sampler2D Sampler_Blend0 = sampler_state 
{ 
    Texture = <Texture_Blend0>;
    MipFilter = POINT;
    MinFilter = POINT;
    MagFilter = POINT;
	AddressU = BORDER;
	AddressV = BORDER;
};

uniform float4 TextureCoordinateOffset[ 5 ];
		
VSOutput VSMain( VSInput input )
{
	VSOutput
		output;

	output.HPosition.xyz 	= 	input.Position;
	output.HPosition.w 	= 	1.0;

	output.UV0 = input.UV0;

	return output;
}


float4 PSMain( PSInput input ) : COLOR0
{
    float4  
		finalColor,
		originalColor,
		glowColor0,
		glowColor1,
		glowColor2;
		
	originalColor = tex2D( Sampler_OriginalScene, input.UV0 + TextureCoordinateOffset[0].xy / 2.0f ) ;
	glowColor0 = tex2D( Sampler_Glow_0, input.UV0 + TextureCoordinateOffset[1].xy / 2.0f ) ;
	glowColor1 = tex2D( Sampler_Glow_1, input.UV0 + TextureCoordinateOffset[2].xy / 2.0f ) ;
	glowColor2 = tex2D( Sampler_Glow_2, input.UV0 + TextureCoordinateOffset[3].xy / 2.0f ) ;
	
	finalColor =  originalColor + ( glowColor0 + glowColor1 + glowColor2 ) ;

	finalColor.a = 1;
    return finalColor;
}

technique MainTechnique
{
	pass P0
	{
		VertexShader = compile vs_3_0 VSMain();
        PixelShader  = compile ps_3_0 PSMain();
	}
}
