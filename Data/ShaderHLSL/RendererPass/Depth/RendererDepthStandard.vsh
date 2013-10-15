struct SInput
{
    float4 Position : POSITION;
};

struct SOutput
{
    float4 HPosition    : SV_POSITION;
    float Depth         : TEXCOORD0;
};

uniform float4x4 SC_WorldViewProjectionMatrix;
uniform float4x4 Node_WorldViewMatrix;

SOutput main( SInput input )
{
    SOutput output;

    output.HPosition   =  mul( input.Position, SC_WorldViewProjectionMatrix );

    output.Depth     = output.HPosition.z / 100;

    return output;
}
