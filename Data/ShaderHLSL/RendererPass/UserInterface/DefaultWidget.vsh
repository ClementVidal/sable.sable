struct SInput
{
    float3 Position : POSITION;
    float2 UV0      : TEXCOORD0;
};

struct SOutput
{
    float4 HPosition    : SV_POSITION;
    float2 UV0          : TEXCOORD0;
};

uniform float4 SC_ViewportInfo;
uniform float2 Position;
uniform float2 Size;

SOutput main( SInput input )
{
    SOutput output;

    // Compute vertex position
    output.HPosition.x = Position.x + input.Position.x * Size.x;
    output.HPosition.y = SC_ViewportInfo.y -( Position.y + input.Position.y * Size.y );

    output.HPosition.x /= SC_ViewportInfo.x;
    output.HPosition.y /= SC_ViewportInfo.y;

    output.HPosition.x = output.HPosition.x * 2 - 1;
    output.HPosition.y = output.HPosition.y * 2 - 1;
            
    output.HPosition.z = 1.0;
    output.HPosition.w = 1;

    output.UV0      = input.UV0; 

    return output;
}