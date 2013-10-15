struct VSInput
{
    float2 Position : POSITION;
    float2 UV       : TEXCOORD0;
};

struct VSOutput
{
    float4 HPosition    : POSITION;
    float2 UV	    : TEXCOORD0;
};

struct PSInput
{
    float2 UV	    : TEXCOORD0;
};


texture2D Texture; 
sampler2D TextureSampler = sampler_state 
{ 
    Texture = <Texture>;
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};

texture2D DepthTexture; 
sampler2D DepthTextureSampler = sampler_state 
{ 
    Texture = <DepthTexture>;
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};

uniform float4
	System_DisplayInfo;
	
uniform float4x4 
	WorldViewProjectionMatrix;

uniform float4
	Color;
	
uniform float
	Size;
	
uniform float2
	SpotPos;
	
uniform float2
	FlarePos;
	
float4 PSMain( PSInput input ) : COLOR0
{
	float4 Pixel;
	float depth;

	Pixel = Color;
	Pixel.a = Pixel.a * tex2D( TextureSampler, input.UV ).a / 2;
	
	depth = 1 - tex2D( DepthTextureSampler, float2( FlarePos.x, -FlarePos.y / System_DisplayInfo.z ) / 2 + 0.5 ).x;
	
    return  Pixel * depth;
}

VSOutput VSMain( VSInput input )
{
    VSOutput
		output;

	output.HPosition = float4( 0,0,0,1);
	output.HPosition.xy   = input.Position * Size + SpotPos;
	output.HPosition.y /= System_DisplayInfo.z;
    output.UV      = input.UV ; 
    
	
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
