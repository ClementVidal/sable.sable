//Skybox.vsh
attribute vec3 Attr_Position;

varying vec3 Var_UVCoord;

uniform mat4 WorldViewProjectionMatrix;

void main( void )
{
    gl_Position =  vec4( Attr_Position, 1.0) * WorldViewProjectionMatrix ;
    Var_UVCoord   = Attr_Position.xyz;
}
