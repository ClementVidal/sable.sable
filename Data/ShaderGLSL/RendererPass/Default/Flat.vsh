//Flat.vsh
attribute vec3 Attr_Position;
attribute vec2 Attr_TexCoord0;
attribute vec4 Attr_Color0;

varying vec2 Var_TexCoord0;
varying vec4 Var_Color0;

uniform mat4 SC_WorldViewProjectionMatrix;
        
void main( void )
{
    gl_Position   = vec4( Attr_Position, 1.0) * SC_WorldViewProjectionMatrix;       
    Var_Color0    = Attr_Color0; 
    Var_TexCoord0   = Attr_TexCoord0;
}