#ifndef _SABLE_GRAPHICS_COMMON_IMPL_STUB_MANAGER_
#define _SABLE_GRAPHICS_COMMON_IMPL_STUB_MANAGER_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\Common\Color.h>
#include <Sable\Graphics\Common\DisplayInfo.h>

namespace Sable
{

class CGraphicsManager;
class CSwapChain;

/** 
Interface Wrapper for Display system
*/
class CImplStubGraphicsManager 
{

public:

	/** @name Constructor/Destructor*/
	//@{
	CImplStubGraphicsManager();
	virtual ~CImplStubGraphicsManager();
	//@}

	/** @name Accessors*/
	//@{
    //@}

	/** @name Manipulator*/
	//@{
	virtual Bool Initialize( CGraphicsManager& manager ) { return TRUE; }
	virtual Bool UnInitialize() { return TRUE; }
	virtual Bool DrawIndexedInstanced( EPrimitiveType primitive, UInt32 indexCount, UInt32 startIndexLocation, UInt32 baseVertexLocation, UInt32 instanceCount )  { return TRUE; }
	virtual Bool DrawInstanced( EPrimitiveType primitive, UInt32 vertexCount, UInt32 offset, UInt32 instanceCount )  { return TRUE; }
	virtual Bool Draw( EPrimitiveType primitive, UInt32 vertexCount, UInt32 offset ) { return TRUE; }
	virtual Bool DrawIndexed( EPrimitiveType primitive, UInt32 indexCount, UInt32 startIndexLocation, UInt32 baseVertexLocation ) { return TRUE; }
	//@}

protected:

	// Attributes
	Bool	m_CheckStatesRedondency;

};

}

#endif
