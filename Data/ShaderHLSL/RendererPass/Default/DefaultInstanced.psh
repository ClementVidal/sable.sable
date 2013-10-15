
// ----------------------------------------------------------- //
// Input/Output data

struct VSInput
{
    float4 Position 	: POSITION;
    float3 Normal   	: NORMAL ;
    float4 WorldMatrix1 : TEXCOORD1;
    float4 WorldMatrix2 : TEXCOORD2;
    float4 WorldMatrix3 : TEXCOORD3;
    float4 WorldMatrix4 : TEXCOORD4;        
    float4 Color        : COLOR0;      
};

struct VSOutput
{
    float4 HPosition    : SV_POSITION;
    float4 Color0	    : COLOR0;
};


uniform float4x4 SC_ViewProjectionMatrix;
    
uniform float4x4 SC_WorldViewProjectionMatrix;
    


    
float3 lightDir = float3( 1,-1,1);
        
VSOutput VSMain( VSInput input )
{
    VSOutput output;
	float4x4 worldTransfo;

	worldTransfo[0] = input.WorldMatrix1; 
	worldTransfo[1] = input.WorldMatrix2; 
	worldTransfo[2] = input.WorldMatrix3; 
	worldTransfo[3] = input.WorldMatrix4; 
    
    float4x4 final =    mul( worldTransfo, SC_ViewProjectionMatrix  ) ;
        
    output.HPosition   =  mul( input.Position , final );       
    output.Color0      = clamp( dot(  normalize( input.Normal ), normalize( lightDir ) ), 0, 1); 
    output.Color0		+= float4( 0.1, 0.1, 0.1, 0.0 );
    return output;
}

        
float4 PSMain( VSOutput input ) : SV_Target0
{
    float4  Pixel;

    Pixel = input.Color0;

    Pixel.a = 1.0; 

    return  Pixel;
}


technique10  MainTechnique
{
	pass P0
	{
		SetVertexShader( CompileShader( vs_4_0, VSMain() ) );
		SetPixelShader( CompileShader( ps_4_0, PSMain() ) );		
		SetGeometryShader( NULL );
	}
}
