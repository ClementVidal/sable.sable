#include <Sable/Graphics/Debug/GraphicCommandGroup.h>

#if defined( SETUP_IMPLTYPE_DIRECTX )
	#include <D3d9.h>
#endif

using namespace Sable;

CDebugGraphicCommandGroup::CDebugGraphicCommandGroup( String name )
{
	BeginRenderSequence( name );
}

CDebugGraphicCommandGroup::~CDebugGraphicCommandGroup()
{
	EndRenderSequence();
}

Void CDebugGraphicCommandGroup::BeginRenderSequence( String name )
{

    UInt32 l = StringGetLength(name);
#if defined( SETUP_IMPLTYPE_DIRECTX ) //|| ( defined( SETUP_IMPLTYPE_GLES ) && defined( SETUP_OPENGLES_USE_ANGLE ) )

	WCHAR wbuffer[64];
	MultiByteToWideChar(CP_ACP, 0, name,l ,wbuffer,sizeof(wbuffer) );
	wbuffer[ l ] = 0;

	D3DPERF_BeginEvent(
		D3DCOLOR_ARGB( 1,1,1,1),
		wbuffer);
#endif

}

Void CDebugGraphicCommandGroup::EndRenderSequence( )
{

#if defined( SETUP_IMPLTYPE_DIRECTX ) //|| ( defined( SETUP_IMPLTYPE_GLES ) && defined( SETUP_OPENGLES_USE_ANGLE ) )
	D3DPERF_EndEvent( );
#endif

}