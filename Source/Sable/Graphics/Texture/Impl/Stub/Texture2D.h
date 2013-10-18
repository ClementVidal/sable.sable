#ifndef _SABLE_GRAPHICS_TEXTURE_IMPL_STUB_TEXTURE2D_
#define _SABLE_GRAPHICS_TEXTURE_IMPL_STUB_TEXTURE2D_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Graphics/Common/DataTypes.h>


namespace Sable
{

/** 
Interface Wrapper for both static and dynamic index buffer	 
*/
class CImplStubTexture2D 
{

public:

	/** @name Accessors*/
	//@{
	CImplStubTexture2D() {};
	virtual ~CImplStubTexture2D() {};
	//@}

	/** @name Manipulator*/
	//@{
	virtual Void*	Lock( const UInt8 mipmaplevel, const EBufferAcces acces, UInt32& pitch ) { return NULL; }
	virtual Void	UnLock( ) {};
	virtual Void	Initialize( const CTextureInfo& info, Bool lockable, const Byte* data ){};
	//@}

};

}

#endif
