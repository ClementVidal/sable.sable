#include <Sable\Graphics\Particle\Operator\TargetSize.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1_ALLOC( Sable, CParticleOpTargetSize, CParticleOperator );

CParticleOpTargetSize::CParticleOpTargetSize() :
	CParticleOperator()
{
	m_Increment = CFloat32Range( 2.0f, 2.0f );
}

CParticleOpTargetSize::~CParticleOpTargetSize()
{
}

Void CParticleOpTargetSize::Apply( CParticleGroup& sim, CParticle& particle, Time deltaTime )
{
	Float32 duration =  GetDuration().GetRandomValueInRange();
	Float32 startTime = GetStartTime().GetRandomValueInRange();
	Float32 targetSize = m_Increment.GetRandomValueInRange();

	if( duration > 0.0f )
	{
		if( particle.Age >= startTime && particle.Age <= startTime+duration )
		{
			particle.Size += targetSize * (Float32) deltaTime;
			particle.Size = MathClamp( particle.Size, 0.0f, 9999999.0f );
		}
	}
}

Void CParticleOpTargetSize::SetIncrement( const CFloat32Range& size )
{
	m_Increment = size;
}

const CFloat32Range& CParticleOpTargetSize::GetIncrement() const
{
	return m_Increment;
}

Bool CParticleOpTargetSize::Serialize( CPersistentArchive& ar )
{
	Int16 version = 0;

	if( ar.BeginScope( WT("OpSourceTargetSize"), version ) == 0 )
	{
		ar.Serialize( m_Increment, WT("TargetSize") );

		ar.EndScope();
	}
	else
	{
		return FALSE;
	}

	return CParticleOperator::Serialize( ar );
}