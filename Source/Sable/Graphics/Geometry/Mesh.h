#ifndef _SABLE_GRAPHICS_GEOMETRY_MESH_
#define _SABLE_GRAPHICS_GEOMETRY_MESH_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Graphics/Common/DataTypes.h>

#include <Sable/Core/ManagedObject/Ref.h>
#include <Sable/Core/Geometry/AABox.h>

namespace Sable
{

class CGeometryVertexBuffer;
class CGeometryIndexBuffer;
class CGeometryVertexLayout;
class CRenderer;

/** 
\ingroup GraphicsGeometry
Base class for mesh object.
\n Act as a container for Vertex and Index buffer.
\n Provide basic interface for rendering those objects
\sa CGeometryModel
*/
class CGeometryMesh : public CManagedObject
{

    DEFINE_MANAGED_CLASS( CGeometryMesh );
	
public:

    /** DataTypes*/
    //@{
    //@}
    
    /** @name Constructor/Destructor*/
    //@{
    CGeometryMesh();
    CGeometryMesh( const CFilePath& filePath, String blockName );
    virtual ~CGeometryMesh();
    //@}
    
    /** @name Accessors*/
    //@{
    CGeometryVertexBuffer*  GetVertexBuffer( ) const;
    CGeometryIndexBuffer*   GetIndexBuffer( ) const;
    CGeometryVertexLayout*  GetVertexLayout() const;
    Void                    SetVertexBuffer( CGeometryVertexBuffer* vb );
    Void                    SetIndexBuffer( CGeometryIndexBuffer* ib );
    Void		    SetVertexLayout( CGeometryVertexLayout* vl );

    UInt32                  GetPrimitiveCount() const ;
    UInt32                  GetVertexCount() const;
    UInt32                  GetIndexCount() const;
    Void                    SetPrimitiveType( const EPrimitiveType type );
    EPrimitiveType          GetPrimitiveType( ) const;
    Void                    SetUsedVertexCount( const UInt32  count );
    Void                    SetVertexOffset( const UInt32 offset );

    Void		    SetBoundingBox( const CAABox& box );
    const CAABox&           GetBoundingBox() const;
    //@}
    
    /** @name Manipulator*/
    //@{
    Void			Load();
    Void			Render();
    Void			Activate( CRenderer& renderer );

    Bool			Serialize( CPersistentArchive& ar );
    //@}
    
private:
    
    // Attributes
    CRef<CGeometryIndexBuffer>  m_IndexBuffer;
    CRef<CGeometryVertexBuffer> m_VertexBuffer;
    CRef<CGeometryVertexLayout>	m_VertexLayout;
    UInt32		                m_VertexOffset;
    UInt32		                m_UsedVertexCount;
    EPrimitiveType	            m_PrimitiveType;
    CAABox		                m_BoundingBox;    

};

Inline
const CAABox& CGeometryMesh::GetBoundingBox() const
{
    return m_BoundingBox;
}

Inline
Void CGeometryMesh::SetPrimitiveType( const EPrimitiveType type )
{
    m_PrimitiveType = type;
}

Inline
EPrimitiveType CGeometryMesh::GetPrimitiveType( ) const
{
    return m_PrimitiveType;
}

Inline
Void CGeometryMesh::SetUsedVertexCount( const UInt32  count )
{
    m_UsedVertexCount = count;
}

Inline
Void CGeometryMesh::SetVertexOffset( const UInt32 offset )
{
    m_VertexOffset = offset;
}

}

#endif


