#ifndef _SABLE_GRAPHICS_TEXTURE_IMPL_GLES_TEXTURE3D_
#define _SABLE_GRAPHICS_TEXTURE_IMPL_GLES_TEXTURE3D_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Graphics/Texture/Impl/Stub/Texture3D.h>

namespace Sable
{

/** 
Interface Wrapper for both static and dynamic index buffer	 
*/
class CImplGLESTexture3D : public CImplStubTexture3D
{

public:

	/** @name Constructor/Destructor*/
	//@{
	CImplGLESTexture3D();
	~CImplGLESTexture3D();
	//@}

	/** @name Accessors*/
	//@{
    //@}

	/** @name Accessors*/
	//@{
	//@}

	/** @name Manipulator*/
	//@{
	Void	Initialize( const CTextureInfo& info, const Byte* data );
	//@}

private:

	// Attributes


};


}

#endif
