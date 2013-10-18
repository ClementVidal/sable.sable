#include <Sable/Application/Impl/Msw/StandAloneWindow.h>

#include <windows.h>

using namespace Sable;


LRESULT CALLBACK MessageProcedure( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
    static Bool cursorWasOutside = TRUE;

    switch(uMsg)
    {
    case  WM_KEYDOWN :
        if(wParam == VK_ESCAPE) 
        {
            PostQuitMessage(0);
            return 0;
        }
        return 0; 

    case WM_MOUSEMOVE:
        if( cursorWasOutside )
        {
            cursorWasOutside = FALSE;
            ShowCursor( FALSE );
        }
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    } 
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


CImplMswStandAloneWindow::CImplMswStandAloneWindow() 
{
}

CImplMswStandAloneWindow::~CImplMswStandAloneWindow()
{
    HINSTANCE hInstance = (HINSTANCE)GetModuleHandle(NULL);
    UnregisterClass( WT("SableWindowClass"),hInstance);
}

UInt32 CImplMswStandAloneWindow::GetHandle() const
{
    return m_Handle;
}

Void CImplMswStandAloneWindow::Initialize( const CTextureInfo& info )
{
    HWND windowHandle;
    HINSTANCE hInstance = (HINSTANCE)GetModuleHandle(NULL);

    // Register the windows class
    WNDCLASS wndClass;
    wndClass.style			= CS_DBLCLKS;
    wndClass.lpfnWndProc	= MessageProcedure;
    wndClass.cbClsExtra		= 0;
    wndClass.cbWndExtra		= 0;
    wndClass.hInstance		= hInstance;
    wndClass.hIcon			= NULL;
    wndClass.hCursor		= NULL;
    wndClass.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
    wndClass.lpszMenuName	= NULL;
    wndClass.lpszClassName  = WT("SableWindowClass");

    Bool rc = (Bool) RegisterClass( &wndClass );
    
    //DebugAssert( rc );

    // Set the window's initial style.  It is invisible initially since it might
    // be resized later
    DWORD dwWindowStyle =	WS_CAPTION ;

    RECT rect;
    //Definie la zone client
    SetRect( &rect, 0, 0, info.Width, info.Height ); 
    //Calcule la taille de la fenetre avec cette zone client
    AdjustWindowRect( &rect, dwWindowStyle,false );

    // Create the render window
    windowHandle = CreateWindow( WT("SableWindowClass"), WT("Sable"), dwWindowStyle,
        100, 100, (rect.right-rect.left), (rect.bottom-rect.top), 0,
        0, hInstance, 0 );

    DebugAssert( windowHandle != NULL );

    UpdateWindow( windowHandle ) ;

    SetWindowPos( windowHandle, HWND_TOP, 0, 0, (rect.right-rect.left), (rect.bottom-rect.top), SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_SHOWWINDOW);

    MemoryCopy( &windowHandle, &m_Handle, sizeof( UInt32 ) );
}

Bool CImplMswStandAloneWindow::Update()
{
    MSG     msg = { 0 };
	Bool	bGotMsg;

    bGotMsg = ( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) != 0) ;
    if( bGotMsg )
    {
        TranslateMessage( &msg );
        DispatchMessage( &msg );
    }

    if( msg.message  == WM_QUIT )
        return FALSE;

    return TRUE;
}
