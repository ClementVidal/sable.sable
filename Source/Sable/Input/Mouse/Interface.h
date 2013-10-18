#ifndef _SABLE_INPUT_MOUSE_INTERFACE_
#define _SABLE_INPUT_MOUSE_INTERFACE_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/ManagedObject/Header.h>
#include <Sable/Core/Event/Header.h>
#include <Sable/Core/Math/Vector2f.h>

#include <Sable/Input/Mouse/Event.h>
#include <Sable/Core/Collection/BitArray.h>

#define MOUSE_Sensitivity 400

namespace Sable
{

class CApplicationWindow;

/** 
\ingroup InputMouse
Represent the mouse device.
\nUse the "Mouse" macro to access this singleton
*/
class CMouseInterface : public CManagedObject
{

//TEMPORARY - there is no need for an explicit dependency between MouseInterface and ImplMswMouse
#if defined( SETUP_IMPLTYPE_MSW )
	friend class CImplMswMouse;
#endif

	DEFINE_MANAGED_CLASS( CMouseInterface );

public:

	/** @name DataTypes*/
	//@{
    typedef CEventSignal<EMouseEventType, EMouseEventData, const CVector2f& > Signal;

	struct SState
	{
		SState()
		{
			XPosition = 0.5f;
			YPosition = 0.5f;
			Sensitivity = MOUSE_Sensitivity;
		}
		Float32 XPosition;
		Float32 YPosition;
		Float32 Sensitivity;
		CBitArray32 Buttons;
	};

	struct SAxisData
	{
		EMouseEventData Axis;
		Int32 Value;
	};
	//@}

	/** @name Constructor/Destructor*/
	//@{
	CMouseInterface( CApplicationWindow& window );
	virtual ~CMouseInterface();
	//@}

	/** @name Accessors*/
	//@{
    CApplicationWindow& GetAttachedWindow() const;
	Void	ClampCoordinate( Bool onOff );
	Bool	ClampCoordinate( ) const;
	Bool	GetIsKeyDown( const EMouseEventData key ) const ;
	Float32	GetXPosition( ) const;
	Float32	GetYPosition( ) const;
	CVector2f GetPosition() const;
	Void	SetPosition( const CVector2f& pos );
    //@}

	/** @name Manipulator*/
	//@{
	virtual Void    Update() = 0;
	//@}

	/** @name System*/
	//@{
	Signal          SignalEvent;
	//@}

protected:

	// Attributes
    CApplicationWindow*         m_AttachedWindow;
	SState                      m_State;
	Bool						m_ClampCoordinate;

};

}

#endif


