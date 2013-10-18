#ifndef _SABLE_GRAPHICS_GEOMETRY_MODEL_
#define _SABLE_GRAPHICS_GEOMETRY_MODEL_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/ManagedObject/ManagedObject.h>
#include <Sable/Core/Geometry/AABox.h>
#include <Sable/Core/Persistent/Header.h>
#include <Sable/Graphics/Node/Spatial.h>

namespace Sable
{

class CGeometryMesh;
class CMaterial;
class CRenderPass;

/** 
\ingroup GraphicsGeometry
Contain an array of Subset.
\n A subset is a pair Mesh<->Material
\n Fully represent a complex 3d object, including it's material.
\sa CGeometryMesh
*/
class CGeometryModel : public CManagedObject
{

    DEFINE_MANAGED_CLASS( CGeometryModel );

public:

    /** @name DataTypes*/
    //@{
    struct SSubset
    {
        CRef<CGeometryMesh>   Mesh;
        CRef<CMaterial>       Material;
    };
    //@}

    /** @name Constructor/Destructor*/
    //@{
    CGeometryModel();
    ~CGeometryModel();
    //@}

    /** @name Accessors*/
    //@{
	Void			GetBoundingBox( CAABox& bbox ) const;
    SSubset&        GetSubset( const Index index ) const;
    UInt32          GetSubsetCount() const;
    Void            SetSubsetCount( const UInt8 count );
    //@}
    
    /** @name Manipulator*/
    //@{
	Void			Load();
	Bool			Serialize( CPersistentArchive& ar );
    //@}
    
    /** @name System*/
    //@{
    //@}
    
private:	

    // Attribute
    CArray<SSubset>                 m_SubsetTable;

};

}

#endif
