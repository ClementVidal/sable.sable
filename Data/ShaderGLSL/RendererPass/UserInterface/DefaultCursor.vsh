attribute vec4 Attr_Position;
attribute vec2 Attr_TexCoord0;

varying vec2 Var_UVCoord;

uniform vec4 SC_ViewportInfo;
uniform vec2 CursorPosition;
uniform vec2 CursorSize;
uniform vec2 CursorOffset;

void main( void )
{
	// Scale position to view space
    gl_Position.x = Attr_Position.x * CursorSize.x ;
    gl_Position.y = Attr_Position.y * CursorSize.y ;

	// Offset to recenter cursor
    gl_Position.x += CursorOffset.x ;
    gl_Position.y += CursorOffset.y ;

    gl_Position.x /= SC_ViewportInfo.x ;
    gl_Position.y /= SC_ViewportInfo.y ;

    // Transform from range  0 +1 to -1 +1
    gl_Position.x += (CursorPosition.x * 2.0) - 1.0;
    gl_Position.y +=  ( ( 1.0 - CursorPosition.y ) * 2.0 ) - 1.0 ;

    gl_Position.z = 0.0;
    gl_Position.w = 1.0;

    Var_UVCoord = Attr_TexCoord0; 

}
