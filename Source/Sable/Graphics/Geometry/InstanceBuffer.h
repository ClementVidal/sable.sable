#ifndef _SABLE_GRAPHICS_GEOMETRY_INSTANCEBUFFER_
#define _SABLE_GRAPHICS_GEOMETRY_INSTANCEBUFFER_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/ManagedObject/ManagedObject.h>
#include <Sable/Graphics/Geometry/VertexBuffer.h>
#include <SAble/Core/Math/Matrix4x4f.h>

namespace Sable
{

/** 
\ingroup GraphicsGeometry
*/
class CGeometryInstanceBuffer : public CManagedObject
{

    DEFINE_MANAGED_CLASS( CGeometryInstanceBuffer );

public:

    /** @name DataTypes*/
    //@{
	struct SInstanceData
	{
		CMatrix4x4f	Matrix;
		CColor		Color;
	};
    //@}

    /** @name Constructor/Destructor*/
    //@{
    CGeometryInstanceBuffer();
    ~CGeometryInstanceBuffer();
    //@}

    /** @name Accessors*/
    //@{
	Void			SetCapacity( UInt32 c );
	UInt32			GetCapacity() const;
	Void			AddInstanceData( const SInstanceData& m );
	Void			RemoveAllInstance();
    UInt32			GetInstanceCount() const;
	//@}
    
    /** @name Manipulator*/
    //@{
	Void			Initialize();
	Bool			Serialize( CPersistentArchive& ar );
    //@}
    
    /** @name System*/
    //@{
    //@}
    
private:	

	// Friendship
	friend class CRenderer;

    // Attribute
    CGeometryVertexBuffer       m_VertexBuffer;
    UInt32						m_InstanceCount;
    Bool                        m_IsDirty;
    CArray<SInstanceData>       m_InstanceData;

	// Method
    Bool IsDirty() const;
	Void Activate( CRenderer& renderer, UInt32 index );
    Void Flush();

};

}

#endif
