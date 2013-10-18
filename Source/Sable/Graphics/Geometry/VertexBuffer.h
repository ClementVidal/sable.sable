#ifndef _SABLE_GRAPHICS_GEOMETRY_GEOMETRYVERTEXBUFFER_
#define _SABLE_GRAPHICS_GEOMETRY_GEOMETRYVERTEXBUFFER_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/Collection/Array.h>
#include <Sable/Core/ManagedObject/ManagedObject.h>
#include <Sable/Core/Persistent/Header.h>
#include <Sable/Graphics/Geometry/VertexElement.h>
#include <Sable/Core/Common/BufferVisitor.h>
#include <Sable/Graphics/Geometry/Impl/Header.h>

namespace Sable
{

class CRenderer;
class CGeometryVertexLayout;

/** 
\ingroup GraphicsGeometry
CGeometryVertexBuffer.
\n Represent a simple stream of data within a vertex buffer.
\n A vertex stream contain several elements that are all part of the final vertex format of the vertex buffer.
\n A stream is identified within the vertex buffer by a unique StreamIndex.
*/
class CGeometryVertexBuffer : public CManagedObject
{
	
	DEFINE_MANAGED_CLASS( CGeometryVertexBuffer )

public:

	/** @name Types*/
	//@{
	enum EFlag
	{
		//Lowest 16 bit are for initialization time flags
		nFlag_Dynamic = 0,
		nFlag_DoNotDiscard = 1,

		//Higher 16 bit are for runtime flags
        nFlag_Locked = 18
	};
	//@}

	/** @name Constructor/Destructor*/
	//@{
	CGeometryVertexBuffer();
	~CGeometryVertexBuffer();

	/** @name Operator*/
	//@{
	//@}

	/** @name Accessors*/
	//@{
    CImplVertexStream&              GetImpl();
    Bool                            IsLocked() const;
	Bool							GetAttribute( EFlag flag ) const;
	Void							SetAttribute( EFlag flag );
	
	UInt32							GetVertexByteCount() const;
	UInt32							GetVertexCount() const;
	
    const Byte*                     GetRawData() const;
    UInt32                          GetRawDataByteCount() const;
	Void							SetRawData( UInt32 vertexCount, UInt32 vertexByteSize, const Byte* data = NULL );
	//@}

	/** @name Manipulator*/
	//@{
	Byte*			Lock( UInt32 start = 0, UInt32 size = 0);
	Void			UnLock();
	Void			Load( );
	Void			UnLoad( );
	Void			Activate( CRenderer& renderer, UInt8 streamIndex );
	Bool			Serialize( CPersistentArchive& ar );
	//@}

private:

	// Types

	//Attributes
	CArray<Byte>						m_RawData;

	UInt32								m_VertexCount;
	UInt32								m_VertexByteCount;
	CBitArray32							m_Flags;

	CImplVertexStream					m_Impl;
};

}

#endif
