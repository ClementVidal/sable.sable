#include <Sample\Application\Application.h>

#include <Sable\Input\Keyboard\Header.h>

#include <Sample\View\ViewGame.h>

using namespace Sample;

CApplication::CApplication() : 
    CApplicationStandAlone() 
{
    CViewGame* view = NEWOBJ( CViewGame, ( *this ) );
    SetView( view );

    Initialize();
}

CApplication::~CApplication()
{
}

Void CApplication::Run()
{
    CApplicationStandAlone::Run();
}

Bool CApplication::Update()
{
    return CApplicationStandAlone::Update();
}

Void CApplication::Render()
{
    CApplicationStandAlone::Render();
}

Void CApplication::Initialize()
{
    CApplicationStandAlone::Initialize();

    GetView()->Initialize();
    
    m_SlotKeyboardEvent.AssignFunction( this, &CApplication::OnKeyboardEvent );
    InputManager.GetKeyboard()->AddObserver( m_SlotKeyboardEvent );

    m_CameraController.Initialize( *GetView() );
}



Void CApplication::OnKeyboardEvent( EKeyboardEventType type, EKeyboardEventData data )
{
    if( type == nKeyboardEventType_KeyDown ) 
    {

    } 
    else if (type == nKeyboardEventType_KeyUp) 
    {
        if( data == nKeyboardEventData_Space )
        {
            int a = 0;
        }
        if( data == nKeyboardEventData_D )
        {

        }
        if( data == nKeyboardEventData_Q )
        {

        }
        if( data == nKeyboardEventData_Z )
        {

        }
        if( data == nKeyboardEventData_S )
        {

        }
    }

}


