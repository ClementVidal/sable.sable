#ifndef _SABLE_GRAPHICS_COMMON_IMPL_GLES_MANAGER_
#define _SABLE_GRAPHICS_COMMON_IMPL_GLES_MANAGER_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\Collection\BitArray.h>
#include <Sable\Core\Common\Color.h>
#include <Sable\Core\Collection\List.h>

#include <Sable\Graphics\Common\DataTypes.h>
#include <Sable\Graphics\Common\DisplayInfo.h>

#include <Sable\Graphics\Common\Impl\Stub\GraphicsManager.h>

namespace Sable
{

class CGraphicsManager;

/** 
*/
class CImplGLESGraphicsManager : public CImplStubGraphicsManager
{

public:

	/** @name Constructor/Destructor*/
	//@{
	CImplGLESGraphicsManager();
	~CImplGLESGraphicsManager();
	//@}

	/** @name Accessors*/
	//@{
	//@}

	/** @name Manipulator*/
	//@{
	Bool Initialize( CGraphicsManager& manager );
    Bool UnInitialize();

	Bool DrawIndexedInstanced( EPrimitiveType primitive, UInt32 indexCount, UInt32 startIndexLocation, UInt32 baseVertexLocation, UInt32 instanceCount );
	Bool DrawInstanced( EPrimitiveType primitive, UInt32 vertexCount, UInt32 offset, UInt32 instanceCount );
	Bool DrawIndexed( EPrimitiveType primitive, UInt32 indexCount, UInt32 startIndexLocation, UInt32 baseVertexLocation );
	Bool Draw( EPrimitiveType primitive, UInt32 vertexCount, UInt32 offset );
	//@}

private:

	//Types

	//Methods
	Void SetPrimitiveType( EPrimitiveType primitive );
	EGLSurface CreateTmpSurface();

	//Attributes
    EPrimitiveType              m_LastPrimitiveType;
	EGLSurface					m_EGLTmpSurface;

};


}

#endif
