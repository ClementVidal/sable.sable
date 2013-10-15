attribute vec4 Attr_Position;
attribute vec3 Attr_Normal;
attribute vec2 Attr_TexCoord0;

varying vec2 Var_UVCoord;
varying vec4 Var_Color0;

uniform mat4 SC_WorldViewProjectionMatrix;
uniform vec3 lightDir;
        
void main( void )
{
    vec3 lightDirTmp = lightDir;
    lightDirTmp = vec3( 1,-1,1);
    gl_Position   = Attr_Position * SC_WorldViewProjectionMatrix;       
    Var_Color0    = clamp( dot(  normalize( Attr_Normal ), normalize( lightDirTmp ) ), 0.0, 1.0) * vec4( 1.0, 1.0, 1.0, 1.0 ); 
    Var_UVCoord   = Attr_TexCoord0;
}