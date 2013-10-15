#ifndef _GEOMETRY_INTERFACE_WRAPPERINDEXBUFFER_
#define _GEOMETRY_INTERFACE_WRAPPERINDEXBUFFER_

#include <Sable\Core\Common\DataTypes.h>

namespace Sable
{

/** 
Interface Wrapper for both static and dynamic index buffer	 
*/
class CImplStubIndexBuffer
{

public:

	/** @name Accessor*/
	//@{
	//@}

	/** @name Manipulator*/
	//@{
	virtual Bool			IsInitialized() const { return TRUE; }
	virtual Void			Initialize( UInt32 indexCount, Byte* data, UInt32 byteCount ) {}
	virtual Void 			UnInitialize() {}
	virtual Void			Activate( ) {}
	//@}

};

}

#endif
