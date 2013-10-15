struct SInput
{
    float4 Position : POSITION;
    float4 WvpX     : TEXCOORD4;
    float4 WvpY     : TEXCOORD5;
    float4 WvpT     : TEXCOORD6;  
};

struct SOutput
{
    float4 HPosition    : SV_POSITION;
    float Depth         : TEXCOORD0;
};

uniform float4x4 SC_ViewProjectionMatrix;


SOutput main( SInput input )
{
    SOutput output;
    float4x4 worldTransfo;

    worldTransfo[0] = input.WvpX; 
    worldTransfo[1] = input.WvpY; 
    worldTransfo[2].xyz = cross( input.WvpX.xyz, input.WvpY.xyz );
    worldTransfo[2].w = 0;
    worldTransfo[3] = input.WvpT; 

    float4x4 final =    mul( worldTransfo, SC_ViewProjectionMatrix  ) ;
        
    output.HPosition   =  mul( input.Position, final );	

    output.Depth     = output.HPosition.z;

    return output;
}