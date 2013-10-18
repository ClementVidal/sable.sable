#include <Sable/Graphics/Common/Impl/GLES/GraphicsManager.h>
#include <Sable/Graphics/Common/Impl/GLES/GraphicsManagerHelper.h>

using namespace Sable;

extern CImplGLESGraphicsManagerHelper ImplGLESGraphicsManagerHelper;

CImplGLESGraphicsManager::CImplGLESGraphicsManager()
{
	m_EGLTmpSurface = NULL;
}

CImplGLESGraphicsManager::~CImplGLESGraphicsManager()
{
	eglTerminate( ImplGLESGraphicsManagerHelper.GetEGLDisplay() );
}

Bool	CImplGLESGraphicsManager::Initialize( CGraphicsManager& manager )
{
	HDC			hDisplay = EGL_DEFAULT_DISPLAY;
	EGLDisplay	sEGLDisplay = DebugAssertEGLCall(eglGetDisplay(hDisplay));
	EGLConfig	aEGLConfigs;
	EGLint		cEGLConfigs;
	EGLContext	sEGLContext;

	EGLint aEGLAttributes[] = 
	{
		EGL_RED_SIZE, 8,
		EGL_GREEN_SIZE, 8,
		EGL_BLUE_SIZE, 8,
		EGL_DEPTH_SIZE, 16,
		EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
		EGL_NONE
	};

	EGLint aEGLContextAttributes[] = 
	{
		EGL_CONTEXT_CLIENT_VERSION, 2,
		EGL_NONE
	};

	DebugAssertEGLCall(eglInitialize(sEGLDisplay, NULL, NULL));
	DebugAssertEGLCall(eglChooseConfig(sEGLDisplay, aEGLAttributes, &aEGLConfigs, 1, &cEGLConfigs));

	ImplGLESGraphicsManagerHelper.SetEGLDisplay( sEGLDisplay );
	ImplGLESGraphicsManagerHelper.SetEGLConfig( aEGLConfigs );

	sEGLContext = DebugAssertEGLCall(eglCreateContext(sEGLDisplay, aEGLConfigs, EGL_NO_CONTEXT, aEGLContextAttributes));
	DebugAssert( sEGLContext != EGL_NO_CONTEXT );

		//TESTGL
/*	m_EGLTmpSurface = CreateTmpSurface();

    DebugAssertEGLCall(eglMakeCurrent(sEGLDisplay, m_EGLTmpSurface, m_EGLTmpSurface, sEGLContext));
*/
	ImplGLESGraphicsManagerHelper.SetEGLContext( sEGLContext );

	return TRUE;
}


LRESULT CALLBACK MessageProcedure2( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

EGLSurface CImplGLESGraphicsManager::CreateTmpSurface()
{
	HWND windowHandle;
	HINSTANCE hInstance = (HINSTANCE)GetModuleHandle(NULL);

	// Register the windows class
	WNDCLASS wndClass;
	wndClass.style			= CS_DBLCLKS;
	wndClass.lpfnWndProc	= MessageProcedure2;
	wndClass.cbClsExtra		= 0;
	wndClass.cbWndExtra		= 0;
	wndClass.hInstance		= hInstance;
	wndClass.hIcon			= NULL;
	wndClass.hCursor		= NULL;
	wndClass.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.lpszMenuName	= NULL;
	wndClass.lpszClassName  = WT("SableWindowClass");

	Bool rc = (Bool) RegisterClass( &wndClass );


	// Set the window's initial style.  It is invisible initially since it might
	// be resized later
	DWORD dwWindowStyle =	WS_CAPTION ;

	RECT rect;
	//Definie la zone client
	SetRect( &rect, 0, 0, 640, 480 ); 
	//Calcule la taille de la fenetre avec cette zone client
	AdjustWindowRect( &rect, dwWindowStyle,false );

	// Create the render window
	windowHandle = CreateWindow( WT("SableWindowClass"), WT("Sable"), dwWindowStyle,
		100, 100, (rect.right-rect.left), (rect.bottom-rect.top), 0,
		0, hInstance, 0 );

	DebugAssert( windowHandle != NULL );

	UpdateWindow( windowHandle ) ;

	SetWindowPos( windowHandle, HWND_TOP, 0, 0, (rect.right-rect.left), (rect.bottom-rect.top), SWP_NOMOVE | SWP_NOOWNERZORDER );

	HWND m_Handle;
	MemoryCopy( &windowHandle, &m_Handle, sizeof( UInt32 ) );

	EGLSurface s = DebugAssertEGLCall(eglCreateWindowSurface(ImplGLESGraphicsManagerHelper.GetEGLDisplay(), ImplGLESGraphicsManagerHelper.GetEGLConfig(), (EGLNativeWindowType)m_Handle, NULL));

	return s;
}

Bool	CImplGLESGraphicsManager::UnInitialize()
{
    return TRUE;
}

Bool CImplGLESGraphicsManager::Draw( EPrimitiveType primitive, UInt32 vertexCount, UInt32 offset )
{
	DebugAssertGLCall( glDrawArrays( CImplGLESGraphicsManagerHelper::TranslatePrimitiveType( primitive ), offset, vertexCount ) );
    return TRUE;
}

Bool CImplGLESGraphicsManager::DrawIndexedInstanced( EPrimitiveType primitive, UInt32 indexCount, UInt32 startIndexLocation, UInt32 baseVertexLocation, UInt32 instanceCount )
{
	return TRUE;
}

Bool CImplGLESGraphicsManager::DrawInstanced( EPrimitiveType primitive, UInt32 vertexCount, UInt32 offset, UInt32 instanceCount )
{
	return TRUE;
}

Void CImplGLESGraphicsManager::SetPrimitiveType( EPrimitiveType primitive )
{
}

Bool CImplGLESGraphicsManager::DrawIndexed( EPrimitiveType primitive, UInt32 indexCount, UInt32 startIndexLocation, UInt32 baseVertexLocation )
{
	DebugAssertGLCall( glDrawElements( CImplGLESGraphicsManagerHelper::TranslatePrimitiveType( primitive ), indexCount, GL_UNSIGNED_SHORT, NULL ) );
    return TRUE;
}
