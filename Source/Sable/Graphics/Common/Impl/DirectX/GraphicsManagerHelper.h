#ifndef _SABLE_GRAPHICS_COMMON_IMPL_DIRECTX_GRAPHICSMANAGERHELPER_
#define _SABLE_GRAPHICS_COMMON_IMPL_DIRECTX_GRAPHICSMANAGERHELPER_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Graphics\Common\DataTypes.h>

#include <DXGI.h>

#ifdef SETUP_CONFIG_DEBUG
#define AssertDXCall( call ) DebugAssertMsg( call == S_OK, "DirectX Call failed" )
#else
#define AssertDXCall( call )  call
#endif

#define ReleaseDXResource( rsc ) \
	if( rsc ) rsc->Release(); \
	rsc = NULL; \
		

struct ID3D10Device;

namespace Sable
{

/** 
Wrapper DX9 for Shader
*/
class CImplDirectXGraphicsManagerHelper 
{  

public:

	/* @name Constructor/Destructor*/
	//@{
	CImplDirectXGraphicsManagerHelper();
	~CImplDirectXGraphicsManagerHelper();
	//@}

	/* @name Manipulator*/
	//@{
    static DXGI_SAMPLE_DESC         TranslateMultiSampling( EMultiSamplingQuality mt );
    static DXGI_FORMAT				TranslatePixelFormat( const ETextureFormat format );
	static ID3D10Device*		    GetDevice();
	//@}

private:

	//Method

	//Attribute

	//Static method

};

}
#endif
