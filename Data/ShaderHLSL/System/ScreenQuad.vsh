struct SInput
{
    float2 Position : POSITION;
    float2 UV0      : TEXCOORD0;
    float4 Color    : COLOR0;
};

struct SOutput
{
    float4 Position     : SV_POSITION;
    float2 UV0          : TEXCOORD0;
    float4 Color        : COLOR0;
};

uniform float2 Size;
uniform float2 Position;

SOutput main( SInput input )
{
    SOutput output;

    output.Position = float4( input.Position, 0.0, 1.0 );

    output.UV0 = input.UV0;
    output.Color = input.Color;

    return output;
}
