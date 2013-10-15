#include <Sable\Graphics\Particle\Operator\SourcePointList.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1( Sable, CParticleOpSourcePointList, CParticleOpSource );

CParticleOpSourcePointList::CParticleOpSourcePointList() :
	CParticleOpSource()
{
	m_PointCount = 0;
}

CParticleOpSourcePointList::CParticleOpSourcePointList( UInt32 reservedParticleCount ) :
	CParticleOpSource()
{
	m_PointCount = 0;
	SetParticleCapacity( reservedParticleCount );
}

CParticleOpSourcePointList::~CParticleOpSourcePointList()
{
}

Void CParticleOpSourcePointList::SetParticleCapacity( UInt32 i )
{
	m_PointCloud.SetItemCount( i );
}

Void CParticleOpSourcePointList::BeginNewStep( CParticleGroup& sim, Time deltaTime )
{
}	

CArray<CParticleOpSourcePointList::SPoint>& CParticleOpSourcePointList::GetPointCloud()
{
	return m_PointCloud;
}

Void CParticleOpSourcePointList::AddPoint( const CParticleOpSourcePointList::SPoint& p )
{
	if( m_PointCount+1 < m_PointCloud.GetItemCount() )
	{
		m_PointCloud[m_PointCount] = p;
		m_PointCount++;
	}
	else
	{
		m_PointCount = 0;
	}

	m_NbParticleToAdd = m_PointCount;
}

Void CParticleOpSourcePointList::Apply( CParticleGroup& sim, CParticle& particle, Time deltaTime )
{
	particle.Position = CVector3f::Zero;

	if( m_NbParticleToAdd )
	{
		ConfigureNewParticle( sim, particle );
		m_NbParticleToAdd--;
	}
	else
	{
		particle.Age = -1.0f;
	}
}

Void CParticleOpSourcePointList::ClearPointList()
{
	m_PointCount = 0;

}

Void CParticleOpSourcePointList::ConfigureNewParticle( CParticleGroup& sim, CParticle& particle )
{
	CParticleOpSource::ConfigureNewParticle( sim, particle );
	particle.Velocity = CVector3f( 0,0,0 );
	particle.Position = m_PointCloud[m_NbParticleToAdd-1].Pos;
	particle.Size = m_PointCloud[m_NbParticleToAdd-1].Size;
	particle.Color = m_PointCloud[m_NbParticleToAdd-1].Color;
}