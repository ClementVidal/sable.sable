#ifndef _SABLE_GRAPHICS_GEOMETRY_VERTEXDESCRIPTOR_
#define _SABLE_GRAPHICS_GEOMETRY_VERTEXDESCRIPTOR_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Graphics\Geometry\VertexElement.h>
#include <Sable\Core\Common\BufferVisitor.h>
#include <Sable\Graphics\Geometry\Impl\Header.h>

namespace Sable
{

/** 
\ingroup GraphicsGeometry
Vertex Buffer. 
*/
class CGeometryVertexLayout : public CManagedObject
{

	DEFINE_MANAGED_CLASS( CGeometryVertexLayout )

public:

	/** @name Constructor/Destructor*/
	//@{
	CGeometryVertexLayout( );
	~CGeometryVertexLayout();
	//@}

	/** @name Operator*/
	//@{
	//@}

	/** @name Accessor*/
	//@{
    Bool                            HasPerInstanceData() const;
	UInt32							GetElementCount() const;
	Bool							HasElement( EVertexComponent semantic ) const;
	UInt32							GetElementStreamIndex( EVertexComponent semantic ) const;
	const CGeometryVertexElement&	GetElementAtIndex( const Index index ) const;
	const CGeometryVertexElement&	GetElementAtSemantic( EVertexComponent semantic ) const;
	UInt32							GetVertexByteCount() const;
	CBufferVisitor                  GetBufferVisitor( EVertexComponent semantic, UInt32 vertexCount, const Byte* rawData ) const;
	//@}

	/** @name Manipulator*/
	//@{
	Bool	Serialize( CPersistentArchive& ar );
	Void	Activate( CRenderer& renderer );
	Void	Initialize();
	Void	AddElement( EVertexComponent semantic, EVertexComponentType type, UInt32 streamIndex = 0, Bool perInstanceData = FALSE );
	//@}

private:

	//Attributes
	CImplVertexLayout					m_Impl;
	Bool								m_IsActivated;
	CGeometryVertexElement				m_ElementTable[8];
	UInt32								m_ElementCount;
	UInt32								m_VertexByteCount;

	// Methods
	Void	UnInitialize();
	UInt32	GetVertexComponentByteCount( EVertexComponentType type ) const;

};

}

#endif
