#include <Sable/Graphics/Particle/Operator/SourcePoint.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1_ALLOC( Sable, CParticleOpSourcePoint, CParticleOpSource );

CParticleOpSourcePoint::CParticleOpSourcePoint()
{
	m_SpreadAngle = 45.0f;
}

CParticleOpSourcePoint::~CParticleOpSourcePoint()
{
}

Void CParticleOpSourcePoint::ConfigureNewParticle( CParticleGroup& sim, CParticle& particle )
{
	CParticleOpSource::ConfigureNewParticle( sim, particle );

	particle.Position = sim.GetOrigin() + m_Origin;
	particle.Velocity = sim.GetDirection() * GetParticleSpeed().GetRandomValueInRange();

	CMatrix4x4f rot;
	Float32 spread = MathDegreeToRadian( m_SpreadAngle );

	rot.SetFromEulerAngle( CEulerAngle( m_Random.GetRandomNumber(-spread, spread ), 0.0f, m_Random.GetRandomNumber(-spread, spread ) ) );

	particle.Velocity.Transform( rot );
}

Void CParticleOpSourcePoint::SetSpreadAngle( Float32 angle )
{
	m_SpreadAngle = angle;
}

Float32	CParticleOpSourcePoint::GetSpreadAngle() const
{
	return m_SpreadAngle;
}

Bool CParticleOpSourcePoint::Serialize( CPersistentArchive& ar )
{
	Int16 version = 0;

	if( ar.BeginScope( WT("OpSourcePoint"), version ) == 0 )
	{
		ar.Serialize( m_Origin, WT("Origin") );
		ar.Serialize( m_SpreadAngle, WT("SpreadAngle") );

		ar.EndScope();
	}
	else
	{
		return FALSE;
	}

	return CParticleOpSource::Serialize( ar );
}