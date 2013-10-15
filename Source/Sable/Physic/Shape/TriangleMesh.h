#ifndef _SABLE_PHYSIC_SHAPE_TRIANGLEMESH_
#define _SABLE_PHYSIC_SHAPE_TRIANGLEMESH_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\Math\Vector3f.h>
#include <Sable\Core\Persistent\Archive.h>
#include <Sable\Physic\Shape\Shape.h>

#include <NxTriangleMeshShapeDesc.h> 

namespace Sable
{

/** 
\ingroup PhysicShape
Physic shape for triangle meshes
*/
class CPhysicShapeTriangleMesh : public CPhysicShape
{

	DEFINE_MANAGED_CLASS( CPhysicShapeTriangleMesh );

public:

    /** @name Constructor/Destructor*/
    //@{
    CPhysicShapeTriangleMesh();
    ~CPhysicShapeTriangleMesh();
    //@}

    /** @name Accessors*/
    //@{
	Void		SetFilePath( const CFilePath& path );
    NxShapeDesc& GetNxShapeDesc() ;
    //@}

    /** @name Manipulator*/
    //@{
	Bool Serialize( CPersistentArchive& ar );
	//@}

	// Attributes
    NxTriangleMeshShapeDesc      NXShapeDesc;
	
private:

	// Attributes
	CFilePath				m_FilePath;
	NxTriangleMesh*			m_NXTriangleMesh;

};


}

#endif


