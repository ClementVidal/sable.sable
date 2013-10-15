attribute vec4 Attr_Position;
attribute vec2 Attr_TexCoord0;

varying vec2 Var_UVCoord;

uniform vec4 SC_ViewportInfo;
uniform vec2 Position;
uniform vec2 Size;

void main( void )
{
    // Compute vertex position
    gl_Position.x = Position.x + Attr_Position.x * Size.x;
    gl_Position.y = Position.y + Attr_Position.y * Size.y;

    gl_Position.x /= SC_ViewportInfo.x;
    gl_Position.y /= SC_ViewportInfo.y;

    gl_Position.x = gl_Position.x * 2.0 - 1.0;
    gl_Position.y = gl_Position.y * 2.0 - 1.0;
     
    gl_Position.y =  - gl_Position.y;
           
    gl_Position.z = 0.0;
    gl_Position.w = 1.0;

    Var_UVCoord = Attr_TexCoord0; 
}