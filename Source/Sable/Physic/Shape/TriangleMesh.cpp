#include <Sable/Physic/Shape/TriangleMesh.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1_ALLOC( Sable, CPhysicShapeTriangleMesh, CPhysicShape );

CPhysicShapeTriangleMesh::CPhysicShapeTriangleMesh() :
	CPhysicShape()
{
	m_NXTriangleMesh = NULL;
}

CPhysicShapeTriangleMesh::~CPhysicShapeTriangleMesh()
{
}

Void CPhysicShapeTriangleMesh::SetFilePath( const CFilePath& path )
{
	m_FilePath = path;
}

NxShapeDesc& CPhysicShapeTriangleMesh::GetNxShapeDesc()
{
    return NXShapeDesc;
}

Bool CPhysicShapeTriangleMesh::Serialize( CPersistentArchive& ar )
{
    DebugError("Not yet reimplemented since CPersistentArchive refactoring");

	ar.Serialize( m_FilePath, WT("FilePath") );
	if( ar.IsLoading() )
	{
        /*
		// Handle relative path
		Char arDir[128];
		Char finalPath[128];
		String filePath = m_FilePath.GetPath( );
		ar.GetFilePath().GetDirectory( arDir, 128 );

		if( filePath[0] == '.' && filePath[1] == '/' )
		{
			StringAppend( arDir, filePath+2, finalPath, 128 );
			m_FilePath = CFilePath( finalPath );
		}

		if( m_FilePath.Exist() )
		{
			m_NXTriangleMesh = PhysicManager.NXSdk->createTriangleMesh( CPhysicFileStream( m_FilePath.GetPath(), true) );
			NXShapeDesc.meshData = m_NXTriangleMesh;
		}*/
	}

	return TRUE;
}
