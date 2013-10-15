#ifndef _SABLE_SCENE_VIEW_CAMERACONTROLLER_
#define _SABLE_SCENE_VIEW_CAMERACONTROLLER_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\ManagedObject\ManagedObject.h>
#include <Sable\Core\ManagedObject\Ref.h>
#include <Sable\Core\Collection\BitArray.h>
#include <Sable\Core\Math\PolarCoordinate.h>
#include <Sable\Core\Math\Matrix4x4f.h>
#include <Sable\Graphics\Node\Spatial.h>
#include <Sable\Core\Event\Header.h>
#include <Sable\Input\Keyboard\Header.h>
#include <Sable\Input\Mouse\Header.h>

namespace Sable
{

class CSceneView;

/** 
\ingroup SceneView

Class that automaticly handle classic camera control using mouse & keyboard.

*/
class CCameraController : public CManagedObject
{

    DEFINE_MANAGED_CLASS( CCameraController );

public:

	/** @name DataType*/
	//@{
	enum EActionType
	{
        nActionType_RotateView = 0,
        nActionType_PanView,
        nActionType_ZoomView,
    };
    //@}

    /** @name Constructor/Destructor*/
    //@{
    CCameraController( );
    virtual ~CCameraController();
    //@}

    /** @name Accessors*/
    //@{
	Void	SetControlPlaneDist( Float32 f );
    Bool    GetIsDragging() const;
    //@}

    /** @name Manipulator*/
    //@{
	Void				FitTo( const CSphere& sphere, const CVector3f& camDir = CVector3f::Zero );
    Void                Initialize( CCamera& cam, CMouseInterface::Signal& mouseSignal, CKeyboardInterface::Signal& kbdSignal  );
	Void				SetCameraWorldMatrix( const CMatrix4x4f& m );
    //@}

private:

    // Attributes
    CBitArray32           m_ActionType;

	CEulerAngle			m_StartDragAngle;

	CVector2f			m_LastMoveScreenPos;

    CCamera*            m_Camera;
    CNodeSpatial        m_CameraCenter;
    Bool                m_LeftCtrlDown;
    Bool                m_DragState;
	Float32				m_ControlPlaneDist;
    EMouseEventData     m_DragBtn;

    CEventSlot<CCameraController, EKeyboardEventType, EKeyboardEventData> m_SlotKeyboardEvent;
    CEventSlot<CCameraController, EMouseEventType, EMouseEventData, const CVector2f& > m_SlotMouseEvent;

    // Methods
    Void OnKeyboardEvent( EKeyboardEventType key, EKeyboardEventData data );
    Void OnMouseEvent( EMouseEventType axis, EMouseEventData data, const CVector2f& pos );
    Void UpdateRotation( const CVector2f& lastPos, const CVector2f& newPos );
    Void UpdatePan( const CVector2f& lastPos, const CVector2f& newPos );
    Void UpdateZoom( const CVector2f& lastPos, const CVector2f& newPos );

	
};

}

#endif


