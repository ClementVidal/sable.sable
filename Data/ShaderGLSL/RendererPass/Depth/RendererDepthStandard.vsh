attribute vec4 Attr_Position;

varying float Var_Depth;

uniform mat4 SC_WorldViewProjectionMatrix;

void main( void )
{
    gl_Position =  Attr_Position * SC_WorldViewProjectionMatrix;
    Var_Depth = gl_Position.z / 100.0;
}
