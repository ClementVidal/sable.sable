#include <Sable/Input/Common/CameraController.h>

#include <Sable/Input/Keyboard/Interface.h>
#include <Sable/Input/Mouse/Interface.h>
#include <Sable/Input/Common/Manager.h>

#include <Sable/Core/Geometry/Ray.h>
#include <Sable/Core/Math/Vector2f.h>
#include <Sable/Core/Math/Matrix3x3f.h>

#include <Sable/Graphics/Camera/Camera.h>
#include <Sable/Graphics/Scene/View.h>
#include <Sable/Graphics/Scene/World.h>
#include <Sable/Graphics/Camera/Perspective.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS( Sable, CCameraController )

CCameraController::CCameraController( )
{
    m_Camera = NULL;
    m_ActionType.Clear();
	m_ControlPlaneDist = 1.0f;
    m_LastMoveScreenPos = CVector2f::Zero;
    m_LeftCtrlDown = FALSE;
}

CCameraController::~CCameraController()
{
    m_CameraCenter.SetParent( NULL );
}

Void CCameraController::Initialize( CCamera& cam, CMouseInterface::Signal& mouseSignal, CKeyboardInterface::Signal& kbdSignal  )
{
    EVENT_CONNECT_SLOT( kbdSignal, m_SlotKeyboardEvent, &CCameraController::OnKeyboardEvent )
    EVENT_CONNECT_SLOT( mouseSignal, m_SlotMouseEvent, &CCameraController::OnMouseEvent )
	m_SlotKeyboardEvent.AssignFunction( this, &CCameraController::OnKeyboardEvent );
    kbdSignal.Connect( m_SlotKeyboardEvent );

    m_Camera = &cam ;

    m_CameraCenter.SetParent( m_Camera->GetParent() );
    m_Camera->SetParent( &m_CameraCenter );

    m_Camera->SetCameraPosition( CVector3f( 0.0f, 0.0f, -10.0f ) );
	m_ControlPlaneDist = 10.0f;
	m_StartDragAngle = CEulerAngle( 0.0f, 0.0f, 0.0f );
}

Void CCameraController::SetControlPlaneDist( Float32 f )
{
	m_ControlPlaneDist = f;
}

Void CCameraController::FitTo( const CSphere& sphere, const CVector3f& camDir )
{
	DebugAssert( m_Camera && m_Camera->GetTypeInfo().IsKindOf( CCameraPerspective::GetStaticTypeInfo() ) );


	if( camDir.GetLength() != 0.0f  )
	{
		m_StartDragAngle = CEulerAngle( 0.0f, 0.0f, 0.0f );
	}

	CMatrix4x4f camMtx;
	CMatrix4x4f camCenterMtx;

	// Move camera ate the center of the bounding sphere using m_StartDragAngle as the orientation
	camCenterMtx.SetFromEulerAngle( m_StartDragAngle );
	camCenterMtx.SetTranslationComponent( sphere.GetCenter() );
	m_CameraCenter.SetLocalMatrix( camCenterMtx );
	
	// compute the distance between the camera and the center of the sphere using the camera FieldOfView
	Float32 dist = sphere.GetRadius() / MathTan( ((CCameraPerspective*)m_Camera)->GetFieldOfView() / 2.0f );
	m_ControlPlaneDist = dist;

	// Translate the camera by this distance
	camMtx.SetFromIdentity();
	camMtx.TranslateOverAxis( -dist , nAxis_Z );
	m_Camera->SetLocalMatrix( camMtx );
}

Void CCameraController::SetCameraWorldMatrix( const CMatrix4x4f& m )
{
	CMatrix4x4f centerMtx = m;
	centerMtx.TranslateOverAxis( m_ControlPlaneDist, nAxis_Z );
	m_CameraCenter.SetLocalMatrix( centerMtx );

	CMatrix4x4f invertCenterMtx = centerMtx;
	invertCenterMtx.Invert();

	invertCenterMtx = invertCenterMtx * m;
	m_Camera->SetLocalMatrix( invertCenterMtx );

}

Void CCameraController::OnKeyboardEvent( EKeyboardEventType type, EKeyboardEventData data )
{
    if( type == nKeyboardEventType_KeyDown && data == nKeyboardEventData_LeftShift )
    {
        m_LeftCtrlDown = TRUE;
    }
    else if( type == nKeyboardEventType_KeyUp && data == nKeyboardEventData_LeftShift )
    {
        m_LeftCtrlDown = FALSE;
    }
}

Void CCameraController::OnMouseEvent( EMouseEventType type, EMouseEventData data, const CVector2f& pos )
{    
	CVector2f lastPos;
    CVector2f newPos = InputManager.GetMouse()->GetPosition();

	lastPos = m_LastMoveScreenPos;
    m_LastMoveScreenPos = newPos;

    // Prepare for a new potential drag sequence
    if( type == nMouseEventType_KeyDown )
    {
        m_DragState = 1;
        m_DragBtn = data;
    }
    // End drag sequence
    else if( type == nMouseEventType_KeyUp )
    {
        if( m_DragState == 2 )
        {
            if( data == nMouseEventData_LeftBtn && m_LeftCtrlDown == FALSE )
            {
                m_ActionType.SetBit( nActionType_RotateView, FALSE );
            }
            else if( data == nMouseEventData_RightBtn && m_LeftCtrlDown == TRUE )
            {
                m_ActionType.SetBit( nActionType_ZoomView, FALSE );
            }
            else if( data == nMouseEventData_RightBtn )
            {
                m_ActionType.SetBit( nActionType_PanView, FALSE );
            }
            else if( data == nMouseEventData_MiddleBtn )
            {
                m_ActionType.SetBit( nActionType_ZoomView, FALSE );
            }
        }
        m_DragState = 0;

    }
    else if( type == nMouseEventType_Move )
    {
        // Start a drag Sequence
        if( m_DragState == 1 )
        {
            m_LastMoveScreenPos = InputManager.GetMouse()->GetPosition();
			//m_StartDragAngle = CEulerAngle( m_CameraCenter.GetWorldMatrix().GetRotationComponent() );

            if( m_DragBtn == nMouseEventData_LeftBtn && m_LeftCtrlDown == FALSE )
            {
                m_ActionType.SetBit( nActionType_RotateView, TRUE );
            }
            else if( m_DragBtn == nMouseEventData_RightBtn && m_LeftCtrlDown == TRUE )
            {
                m_ActionType.SetBit( nActionType_ZoomView, TRUE );
            }
            else if( m_DragBtn == nMouseEventData_RightBtn )
            {
                m_ActionType.SetBit( nActionType_PanView, TRUE );
            }
            else if( m_DragBtn == nMouseEventData_MiddleBtn )
            {
                m_ActionType.SetBit( nActionType_ZoomView, TRUE );
            }

            m_DragState = 2;
        }
        // Drag
        else if( m_DragState == 2 )
        {
            UpdateRotation( lastPos, newPos );
            UpdatePan( lastPos, newPos );
            UpdateZoom( lastPos, newPos  );
        }
        // Move without dragging
        else
        {

        }
    }
}

Bool CCameraController::GetIsDragging() const
{
    return m_DragState == 2;
}

Void CCameraController::UpdateZoom( const CVector2f& lastPos, const CVector2f& newPos )
{
    if( m_ActionType.GetBit( nActionType_ZoomView ) )
    {
		CVector3f a = m_Camera->Get3DPointFrom2DPos( lastPos, m_ControlPlaneDist );
		CVector3f b = m_Camera->Get3DPointFrom2DPos( newPos, m_ControlPlaneDist );

		CVector3f delta = b-a;
		delta.Transform( m_Camera->GetViewProjectionMatrix() );

        m_CameraCenter.GetLocalMatrix().TranslateOverAxis( delta.GetY(), nAxis_Z );
    }
}

Void CCameraController::UpdatePan( const CVector2f& lastPos, const CVector2f& newPos )
{
    if( m_ActionType.GetBit( nActionType_PanView ) )
    {
		CVector3f a = m_Camera->Get3DPointFrom2DPos( lastPos, m_ControlPlaneDist );
		CVector3f b = m_Camera->Get3DPointFrom2DPos( newPos, m_ControlPlaneDist );

		CVector3f delta = b-a;
		delta.Transform( m_Camera->GetViewProjectionMatrix() );

        m_CameraCenter.GetLocalMatrix().TranslateOverAxis( delta.GetY(), nAxis_Y );
        m_CameraCenter.GetLocalMatrix().TranslateOverAxis( -delta.GetX(), nAxis_X );
    }
}

Void CCameraController::UpdateRotation( const CVector2f& lastPos, const CVector2f& newPos )
{
    if( m_ActionType.GetBit( nActionType_RotateView ) )
    {
		CVector2f delta = newPos-lastPos;

		m_StartDragAngle = m_StartDragAngle + CEulerAngle( delta.GetY() * MathPi, delta.GetX() * MathPi, 0.0f );
		
		CMatrix4x4f m;
		CVector3f position = m_CameraCenter.GetLocalMatrix().GetTranslationComponent();
		m.SetFromEulerAngle( m_StartDragAngle );
		m.SetTranslationComponent( position );
        m_CameraCenter.SetLocalMatrix( m );
    }
}
