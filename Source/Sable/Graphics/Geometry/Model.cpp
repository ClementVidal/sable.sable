#include <Sable/Graphics/Geometry/Model.h>

#include <Sable/Graphics/Material/Material.h>
#include <Sable/Graphics/Common/DataTypes.h>
#include <Sable/Graphics/Geometry/IndexBuffer.h>
#include <Sable/Core/ManagedObject/Ref.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1_ALLOC( Sable, CGeometryModel, CManagedObject ) ;

CGeometryModel::CGeometryModel( )
{
}

CGeometryModel::~CGeometryModel()
{
}

CGeometryModel::SSubset& CGeometryModel::GetSubset( const Index index ) const
{
    return m_SubsetTable[ index ];
}

Void CGeometryModel::SetSubsetCount( const UInt8 count )
{
    m_SubsetTable.SetItemCount( count );
}

UInt32 CGeometryModel::GetSubsetCount() const
{
    return m_SubsetTable.GetItemCount();
}

Void CGeometryModel::GetBoundingBox( CAABox& box ) const
{
	box.SetEmpty();

	UInt32 i;
	for( i=0;i<m_SubsetTable.GetItemCount();i++)
	{
		box.AddBox( m_SubsetTable[i].Mesh->GetBoundingBox() );
	}
}

Bool CGeometryModel::Serialize( CPersistentArchive& ar )
{
	Int16 version = 0;
	UInt32 subsetCount = m_SubsetTable.GetItemCount();
	
	ar.Serialize( subsetCount, WT("SubsetCount") );

	if( ar.IsLoading() )
		m_SubsetTable.SetItemCount( subsetCount );

	UInt32 i;
	for( i=0;i<subsetCount;i++)
	{
		SSubset s;
		if( ar.IsStoring() )
			s = m_SubsetTable[i];

		if( ar.BeginScope( WT("Subset"), version ) == version )
		{
			ar.Serialize( s.Material,  WT("Material") );
			ar.Serialize( s.Mesh,  WT("Mesh") );
			ar.EndScope();
		}

		if( ar.IsLoading() )
			m_SubsetTable[i] = s;
	}
	
	return CManagedObject::Serialize( ar );
}

Void CGeometryModel::Load()
{
	UInt32 i;
	for(i=0;i<m_SubsetTable.GetItemCount();i++)
	{
		if( m_SubsetTable[i].Mesh )
			m_SubsetTable[i].Mesh->Load();

		if( m_SubsetTable[i].Material )
			m_SubsetTable[i].Material->Load();
	}
}