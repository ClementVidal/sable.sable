#ifndef _SABLE_GRAPHICS_GEOMETRY_IMPL_STUB_VERTEXLAYOUT_
#define _SABLE_GRAPHICS_GEOMETRY_IMPL_STUB_VERTEXLAYOUT_

#include <Sable/Core/Common/DataTypes.h>

namespace Sable
{

class CGeometryVertexLayout;

/** 
*/
class CImplStubVertexLayout
{

public:

	/** @name Accessor*/
	//@{
	CImplStubVertexLayout( CGeometryVertexLayout& publicImpl ) { m_PublicImpl = &publicImpl; }
	virtual ~CImplStubVertexLayout(){}
	//@}

	/** @name Manipulator*/
	//@{
	virtual Bool	IsInitialized() const { return TRUE; }
	virtual Void	Initialize( ) {};
	virtual Void	UnInitialize( ) {};
    virtual Void	Activate( ) {};
	//@}

protected:

	// Attributes
	CGeometryVertexLayout*	m_PublicImpl;

};

}

#endif
