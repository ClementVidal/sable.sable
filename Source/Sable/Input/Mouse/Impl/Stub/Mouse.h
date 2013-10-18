#ifndef _SABLE_INPUT_MOUSE_IMPL_STUB_MOUSE_
#define _SABLE_INPUT_MOUSE_IMPL_STUB_MOUSE_

#include <Sable/Core/Common/DataTypes.h>

namespace Sable
{

class CMouse;

/** 
\ingroup Input
*/
class CImplStubMouse 
{

public:

	/** @name Constructor/Destructor*/
	//@{
	CImplStubMouse(){};
	CImplStubMouse(CMouse& mouse){};
	virtual ~CImplStubMouse(){};
	//@}

	/** @name Accessors*/
	//@{
	//@}

	/** @name Manipulator*/
	//@{
	virtual Void	Update() {};
	//@}

private:

	// Methods
	virtual Void	ProcessImmediateData(){};
	virtual Void	ProcessBufferedData(){};

	// Attributes

};

}

#endif


