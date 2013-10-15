#ifndef _SABLE_INPUT_PAD_IMPL_STUB_PAD_
#define _SABLE_INPUT_PAD_IMPL_STUB_PAD_

#include <Sable\Core\Common\DataTypes.h>

namespace Sable
{

class CPad;

/** 
\ingroup InputPad
*/
class CImplStubPad 
{

public:

	/** @name Constructor/Destructor*/
	//@{
    CImplStubPad(CPad& pad) : m_PublicImpl( pad ) {};
	virtual ~CImplStubPad(){};
	//@}

	/** @name Accessors*/
	//@{
	virtual CVector2f	GetAnalogStick( UInt32 id ) const { return CVector2f( 0.0f, 0.0f ); }
	virtual Float32		GetAnalogButton( UInt32 id ) const { return 0.0f; }
	virtual Bool		GetButton( UInt32 id ) const { return FALSE; }
	virtual Bool		IsAvailable() const { return FALSE; }
	//@}

	/** @name Manipulator*/
	//@{
	virtual Void	Update() {};
	//@}

protected:

	// Methods
    CPad&           m_PublicImpl;

	// Attributes

};

}

#endif


