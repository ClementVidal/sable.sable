#include <Sable\Graphics\Particle\Operator\KillOld.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1_ALLOC( Sable, CParticleOpKillOld, CParticleOperator );

CParticleOpKillOld::CParticleOpKillOld() :
	CParticleOperator()
{
	m_AgeLimit = CFloat32Range( 10.0f, 10.0f );
}

CParticleOpKillOld::~CParticleOpKillOld()
{
}

Void CParticleOpKillOld::Apply( CParticleGroup& sim, CParticle& particle, Time deltaTime )
{
	if( particle.Age > m_AgeLimit.GetRandomValueInRange() )
	{
		particle.Reset();
	}
}

Void CParticleOpKillOld::SetAgeLimit( const CFloat32Range& limit )
{
	m_AgeLimit = limit;
}

const CFloat32Range& CParticleOpKillOld::GetAgeLimit() const
{
	return m_AgeLimit;
}

Bool CParticleOpKillOld::Serialize( CPersistentArchive& ar )
{
	Int16 version = 0;

	if( ar.BeginScope( WT("OpSourceKillOld"), version ) == 0 )
	{
		ar.Serialize( m_AgeLimit, WT("AgeLimit") );
		
		ar.EndScope();
	}
	else
	{
		return FALSE;
	}

	return CParticleOperator::Serialize( ar );
}