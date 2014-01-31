#include <Sable/Graphics/Particle/Operator/Gravity.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1_ALLOC( Sable, CParticleOpGravity, CParticleOperator );

CParticleOpGravity::CParticleOpGravity() :
	CParticleOperator()
{
	m_Gravity = CVector3f( 0.0f, -0.9f, 0.0f );
}

CParticleOpGravity::~CParticleOpGravity()
{
}

Void CParticleOpGravity::Apply( CParticleGroup& sim, CParticle& particle, Float32 deltaTime )
{
	if( particle.Age > 0.0f )
	{
		particle.Velocity += m_Gravity * (Float32) deltaTime;
	}
}

Void CParticleOpGravity::SetGravity( const CVector3f& g )
{
	m_Gravity = g;
}

const CVector3f& CParticleOpGravity::GetGravity() const
{
	return m_Gravity;
}

Bool CParticleOpGravity::Serialize( CPersistentArchive& ar )
{
	Int16 version = 0;

	if( ar.BeginScope( WT("OpSourceGravity"), version ) == 0 )
	{
		ar.Serialize( m_Gravity, WT("Gravity") );

		ar.EndScope();
	}
	else
	{
		return FALSE;
	}

	return CParticleOperator::Serialize( ar );
}
