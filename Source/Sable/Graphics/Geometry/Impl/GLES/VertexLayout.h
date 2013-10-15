#ifndef _SABLE_GRAPHICS_GEOMETRY_IMPL_GLES_VERTEXLAYOUT_
#define _SABLE_GRAPHICS_GEOMETRY_IMPL_GLES_VERTEXLAYOUT_

#include <Sable\Graphics\Geometry\VertexElement.h>
#include <Sable\Graphics\Geometry\Impl\Stub\VertexLayout.h>
#include <Sable\Core\Common\DataTypes.h>

namespace Sable
{

class CGeometryVertexLayout;

/** 

*/
class CImplGLESVertexLayout : public CImplStubVertexLayout
{

public:

	/** @name Constructor / Destructor*/
	//@{
	CImplGLESVertexLayout( CGeometryVertexLayout& descriptor );
	~CImplGLESVertexLayout();
	//@}

	/** @name Accessor*/
	//@{
	//@}

	/** @name Manipulator*/
	//@{
	Bool	IsInitialized() const;
	Void	Initialize();
	Void	UnInitialize();
	Void	Activate( );
	//@}

private:

	//Method
	GLenum 	TranslateElementType( EVertexComponentType type );
	Int32 	TranslateElementSize( EVertexComponentType type );
	Int32 	TranslateElementByteCount( EVertexComponentType type );

	//Attribute

};

}

#endif

