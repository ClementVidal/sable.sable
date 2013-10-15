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
uniform float4x4 SC_WorldITMatrix;

float3 lightDir = float3( 1,-1,1 );

SOutput main( SInput input )
{
    SOutput output;

    output.HPosition    = mul( float4( input.Position, 1.0f ) , SC_WorldViewProjectionMatrix );     
	float4 worldNormal = mul( float4( input.Normal, 1.0f ) , SC_WorldITMatrix );     
    output.Color0       = clamp( dot( normalize( input.Normal.xyz ), normalize( lightDir ) ), 0, 1) ; 
	output.UVCoord   = input.UVCoord;
    return output;
}