#ifndef _GRAPHICS_GEOMETRY_INDEXBUFFER_
#define _GRAPHICS_GEOMETRY_INDEXBUFFER_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/Persistent/Header.h>
#include <Sable/Core/Common/BufferVisitor.h>
#include <Sable/Core/Collection/Array.h>

#include <Sable/Graphics/Common/DataTypes.h>
#include <Sable/Graphics/Geometry/Impl/Header.h>

namespace Sable
{

class CRenderer;

/** 
\ingroup GraphicsGeometry
Static Index Buffer. 
*/
class CGeometryIndexBuffer : public CManagedObject
{

    DEFINE_MANAGED_CLASS( CGeometryIndexBuffer );

public:

    /** @name Constructor/Destructor*/
    //@{
    CGeometryIndexBuffer();
    virtual ~CGeometryIndexBuffer();
    //@}
    
    /** @name Accessors*/
    //@{
    Void	SetDrawIndexCount( UInt32 count );
    
    UInt32	GetIndexByteCount() const;
    UInt32      GetIndexCount() const;
    Void		SetRawData( UInt32 indexCount, UInt32 indexByteCount, const Byte* data = NULL );
    const Byte* GetRawData() const;
    UInt32      GetRawDataByteCount() const;
    
    CBufferVisitor  GetBufferVisitor( const Byte* rawData ) const;
    //@}
    
    /** @name Manipulator*/
    //@{
    Void		Load( );
    
    Bool		Serialize( CPersistentArchive& ar );
    //@}
    
private:
    
    // Friendship
    friend class CRenderer;
    
    //Methods 
    UInt32      GetPrimitiveCount( EPrimitiveType type, UInt32 indexCount  ) const;
    Void	    Activate( CRenderer& renderer );
    
    //Attributes
    UInt32					m_DrawIndexCount;
    UInt32					m_IndexCount;
    UInt32					m_IndexByteCount;
    CArray<Byte>			m_RawData;
    CImplIndexBuffer        m_Impl;
    
};

}

#endif
