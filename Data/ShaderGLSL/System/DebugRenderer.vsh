attribute vec4 Attr_Position;
attribute vec4 Attr_Color0;

varying vec4 Var_Color0;

uniform mat4 WorldViewProjectionMatrix;

void main( void )
{
    gl_Position = Attr_Position * WorldViewProjectionMatrix;
    Var_Color0 = Attr_Color0; 
}
