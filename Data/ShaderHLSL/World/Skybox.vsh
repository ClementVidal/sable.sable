struct SInput
{
    float3 Position : POSITION;
};

struct SOutput
{
    float4 HPosition    : SV_POSITION;
    float4 UV           : TEXCOORD0;
};

uniform float4x4 WorldViewProjectionMatrix;

SOutput main( SInput input )
{
    SOutput output;

    output.HPosition = mul( float4( input.Position, 1.0f ), WorldViewProjectionMatrix );
    output.UV = float4( input.Position, 1.0f ); 

    return output;
}
