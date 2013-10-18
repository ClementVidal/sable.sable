#include <Sable/Application/Impl/Android/Application.h>

#include <Sable/Application/Impl/Android/Helper.h>

#include <locale.h>

using namespace Sable;

extern CImplAndroidApplicationHelper ImplAndroidApplicationHelper;


CImplAndroidApplication::CImplAndroidApplication() :
    CImplStubApplication()
{
}

CImplAndroidApplication::~CImplAndroidApplication()
{
	eglTerminate( ImplAndroidApplicationHelper.GetEGLDisplay() );
}


Void CImplAndroidApplication::Initialize( CApplication& app )
{
	// Set locale for the application 
	//( this only affect the decimal-point character in formatted input/output operations and string formatting functions )
	setlocale(LC_NUMERIC,"C");

    EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

    eglInitialize(display, 0, 0);

    ImplAndroidApplicationHelper.SetEGLDisplay( display );
}
