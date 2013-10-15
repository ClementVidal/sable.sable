struct SInput
{
    float4 Position     : POSITION;
    float2 UVCoord      : TEXCOORD0;
    float4 Color        : COLOR0;
};

struct SOutput
{
    float4 Position    : SV_POSITION;
    float2 UVCoord      : TEXCOORD0;
    float4 Color        : COLOR0;
};

uniform float4x4 SC_ViewProjectionMatrix;

SOutput main( SInput input )
{
    SOutput output;

    output.Position   = mul(  input.Position , SC_ViewProjectionMatrix );       
    output.UVCoord      = input.UVCoord;
    output.Color   = input.Color;
    return output;
}
