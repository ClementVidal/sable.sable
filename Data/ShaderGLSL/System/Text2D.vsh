attribute vec2 Attr_Position;
attribute vec2 Attr_TexCoord0;

varying vec2 Var_UVCoord;

uniform vec3 Position;
uniform vec2 Resolution;

void main( void )
{
    // Compute vertex position
    float px = Position.x + ( Attr_Position.x / Resolution.x );
    float py = Position.y + ( Attr_Position.y / Resolution.y );

    gl_Position.x = px * 2.0 - 1.0;
    gl_Position.y = py * 2.0 - 1.0;

    gl_Position.z = 0.0;
    gl_Position.w = 1.0;
    Var_UVCoord = Attr_TexCoord0;

}
