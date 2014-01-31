#include <Sable/Graphics/Particle/Operator/TargetColor.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1_ALLOC( Sable, CParticleOpTargetColor, CParticleOperator );

CParticleOpTargetColor::CParticleOpTargetColor() :
	CParticleOperator()
{
	m_Increment = CVector4Range( CVector4f( 0.0f, 0.0f, 0.0f, 0.0f ), CVector4f( 0.0f, 0.0f, 0.0f, 0.0f ) );
}

CParticleOpTargetColor::~CParticleOpTargetColor()
{
}

Void CParticleOpTargetColor::Apply( CParticleGroup& sim, CParticle& particle, Float32 deltaTime )
{
	Float32 duration =  GetDuration().GetRandomValueInRange();
	Float32 startTime = GetStartTime().GetRandomValueInRange();
	CVector4f targetColor = m_Increment.GetRandomValueInRange();

	if( duration > 0.0f )
	{
		if( particle.Age >= startTime && particle.Age <= startTime+duration )
		{
			particle.Color += targetColor * (Float32) deltaTime;
			particle.Color.Normalize();
		}
	}
}

Void CParticleOpTargetColor::SetIncrement( const CVector4Range& l )
{
	m_Increment = l;
}

const CVector4Range& CParticleOpTargetColor::GetIncrement() const
{
	return m_Increment;
}

Bool CParticleOpTargetColor::Serialize( CPersistentArchive& ar )
{
	Int16 version = 0;

	if( ar.BeginScope( WT("OpSourceTargetColor"), version ) == 0 )
	{
		ar.Serialize( m_Increment, WT("TargetColor") );
		ar.EndScope();
	}
	else
	{
		return FALSE;
	}

	return CParticleOperator::Serialize( ar );
}
