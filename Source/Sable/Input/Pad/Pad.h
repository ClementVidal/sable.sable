#ifndef _SABLE_INPUT_PAD_PAD_
#define _SABLE_INPUT_PAD_PAD_

#include <Sable/Core/Common/DataTypes.h>

#include <Sable/Input/Pad/Interface.h>
#include <Sable/Input/Pad/Impl/Header.h>

namespace Sable
{

/** 
\ingroup InputPad
Represent the pad device.
*/
class CPad : public CPadInterface
{

    DEFINE_MANAGED_CLASS( CPad );

    /** @name Constructor/Destructor*/
    //@{
    CPad();
    virtual ~CPad();
    //@}

    /** @name Accessors*/
    //@{
	CVector2f	GetAnalogStick( UInt32 id ) const;
	Float32		GetAnalogButton( UInt32 id ) const;
	Bool		GetButton( UInt32 id ) const;
	Bool		IsAvailable() const;
	//@}

    /** @name Manipulator*/
    //@{
    Void				Update();
    //@}

private:

    // Attributes
    CImplPad	m_Impl;

};

}

#endif


