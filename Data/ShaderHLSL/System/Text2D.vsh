struct SInput
{
    float2 Position : POSITION;
    float2 UV0      : TEXCOORD0;
};

struct SOutput
{
    float4 Position     : SV_POSITION;
    float2 UV0          : TEXCOORD0;
};

uniform float3 Position;
uniform float2 Resolution;

SOutput main( SInput input )
{
    SOutput output;

    // Compute vertex position
    float px = Position.x + ( input.Position.x / Resolution.x );
    float py = Position.y + ( input.Position.y / Resolution.y );

    output.Position.x = px * 2.0f - 1.0f;
    output.Position.y = py * 2.0f - 1.0f;

    output.Position.z = 0;
    output.Position.w = 1;
    output.UV0 = input.UV0;

    return output;
}
