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
uniform float2 CursorSize;
uniform float2 CursorPosition;
uniform float2 CursorOffset;

SOutput main( SInput input )
{
    SOutput output;

	// Scale position to view space
    output.HPosition.x = input.Position.x * CursorSize.x ;
    output.HPosition.y = input.Position.y * CursorSize.y ;

	// Offset to recenter cursor
    output.HPosition.x += CursorOffset.x ;
    output.HPosition.y += CursorOffset.y ;

    output.HPosition.x /= SC_ViewportInfo.x ;
    output.HPosition.y /= SC_ViewportInfo.y ;

    // Transform from range  0 +1 to -1 +1
    output.HPosition.x += (CursorPosition.x * 2) - 1;
    output.HPosition.y +=  ( ( 1.0f - CursorPosition.y ) * 2 ) - 1 ;

    output.HPosition.z = 0;
    output.HPosition.w = 1;

    output.UV0 = input.UV0; 

    return output;
}
