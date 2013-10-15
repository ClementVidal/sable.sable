attribute vec2 Attr_Position;
attribute vec2 Attr_TexCoord0;
attribute vec4 Attr_Color0;

varying vec2 Var_UVCoord;
varying vec4 Var_Color0;

uniform vec2 Size;
uniform vec2 Position;

void main( void )
{
    gl_Position = vec4( Attr_Position, 0.0, 1.0 );
    Var_Color0 = Attr_Color0; 
    Var_UVCoord = Attr_TexCoord0; 
}
