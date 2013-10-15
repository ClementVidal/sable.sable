#ifndef _SABLE_GRAPHICS_GEOMETRY_IMPL_MSW_VERTEXLAYOUT_
#define _SABLE_GRAPHICS_GEOMETRY_IMPL_MSW_VERTEXLAYOUT_

#include <Sable\Graphics\Geometry\VertexElement.h>
#include <Sable\Graphics\Geometry\Impl\Stub\VertexLayout.h>
#include <Sable\Core\Common\DataTypes.h>

struct ID3D10InputLayout;

namespace Sable
{

class CGeometryVertexLayout;

/** 

*/
class CImplDirectXVertexLayout : public CImplStubVertexLayout
{

public:

	/** @name Constructor / Destructor*/
	//@{
	CImplDirectXVertexLayout( CGeometryVertexLayout& publicImpl );
	~CImplDirectXVertexLayout();
	//@}

	/** @name Accessor*/
	//@{
	//@}

	/** @name Manipulator*/
	//@{
	Bool	IsInitialized() const;
	Void	Initialize( );
	Void	UnInitialize( );
	Void	Activate( );
	//@}

private:

	//Method
    CString         BuildDummyEffect( CGeometryVertexLayout& descriptor );
	DXGI_FORMAT		TranslateElementType( EVertexComponentType type );
	String			ConvertElementTypeToString( EVertexComponentType type );

	//Attribute
	ID3D10InputLayout*	m_InputLayout;

};

}

#endif

