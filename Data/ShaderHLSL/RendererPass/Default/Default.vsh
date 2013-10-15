struct SInput
{
    float3 Position     : POSITION;
    float3 Normal       : NORMAL;
    float2 UVCoord      : TEXCOORD0;
};

struct SOutput
{
    float4 HPosition    : SV_POSITION;
    float2 UVCoord      : TEXCOORD0;
    float4 Color0       : COLOR0;
};

uniform float4x4 SC_WorldViewProjectionMatrix;
float3 lightDir = float3( 1,-1,1 );
        
SOutput main( SInput input )
{
    SOutput output;

    output.HPosition    = mul( float4( input.Position, 1.0f ) , SC_WorldViewProjectionMatrix );       
    output.Color0       = clamp( dot(  normalize( input.Normal ), normalize( lightDir ) ), 0, 1)*1; 
	output.UVCoord   = input.UVCoord;
    return output;
}