struct SInput
{
    float3 Position : POSITION;
    float4 Color0   : COLOR0;    
};

struct SOutput
{
    float4 Position     : SV_POSITION;
    float4 Color0       : COLOR0;
};

uniform float4x4 WorldViewProjectionMatrix;

SOutput main( SInput input )
{
    SOutput output;

    output.Position   =  mul( float4( input.Position, 1.0f ), WorldViewProjectionMatrix );
    output.Color0      = input.Color0; 

    return output;
}
