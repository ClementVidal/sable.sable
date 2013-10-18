#ifndef _INPUT_COMMON_IMPL_MANAGERDX9_
#define _INPUT_COMMON_IMPL_MANAGERDX9_

#include <Sable/Input/Common/Impl/Stub/InputManager.h>

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/Collection/Array.h>

#define DIRECTINPUT_VERSION 0x0800

#include <Dinput.h>

namespace Sable
{

/** 
DirectX9 Wrapper for input 
*/
class CImplMswInputManager : public CImplStubInputManager
{

public:

	/* @name Constructor/Destructor*/
	//@{
	CImplMswInputManager();
	~CImplMswInputManager();
	//@}

	/* @name Accessors*/
	//@{
	LPDIRECTINPUT8 GetInputDevice() const;
	//@}

	/* @name Manipulator*/
	//@{
	//@}

private:

	// Method

	// Attribute
	LPDIRECTINPUT8			m_DirectInputObject;

};


Inline
LPDIRECTINPUT8 CImplMswInputManager::GetInputDevice() const
{
	return m_DirectInputObject;
}

}

#endif
