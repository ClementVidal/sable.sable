#include <Sable/Graphics/Particle/Operator/Source.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1( Sable, CParticleOpSource, CParticleOperator );

CParticleOpSource::CParticleOpSource() :
	CParticleOperator()
{
	m_EmitRate = 1.0f;

	m_ParticleScale.SetValues(1.0f,1.0f);
	m_ParticleSpeed.SetValues(1.0f,1.0f);
	m_ParticleColor.Set( 1.0f, 1.0f, 1.0f, 1.0f );

	m_EmitRateFractionalPart = 0.0f;

	m_NbParticleToAdd = 0;
}

CParticleOpSource::~CParticleOpSource()
{
}

Void CParticleOpSource::BeginNewStep( CParticleGroup& sim, Time deltaTime )
{
	m_NbParticleToAdd = 0;

	Float32 count = (Float32) ( deltaTime * m_EmitRate );
	Float32	fractionalPart, temp;

	fractionalPart = count - ( UInt32) count;
	m_NbParticleToAdd = (UInt32)count;

	// Compute effective emit rate, and store the fractional part 
	// in order to be used at next update
	if( fractionalPart + m_EmitRateFractionalPart >= 1.0f) 
	{
		temp = fractionalPart + m_EmitRateFractionalPart;
		m_EmitRateFractionalPart = temp - ( UInt32) temp;
		m_NbParticleToAdd += ( UInt32 )temp;
	} 
	else 
	{
		m_EmitRateFractionalPart += fractionalPart;
	}
}

Void CParticleOpSource::Apply( CParticleGroup& sim, CParticle& particle, Time deltaTime )
{
	Float32 duration = GetDuration().GetRandomValueInRange();
	if( m_NbParticleToAdd && particle.Age < 0.0f && m_EmitTimer.GetElapsedSeconds() <= duration )
	{
		ConfigureNewParticle( sim, particle );
		m_NbParticleToAdd--;
	}
}

const CColor& CParticleOpSource::GetParticleColor() const
{
	return m_ParticleColor;
}

Void CParticleOpSource::SetParticleColor( const CColor& color )
{
	m_ParticleColor = color;
}

/**
Set a speed coefficient for particles.\n
This value is multiplied by the direction of the particle to get the final velocity
*/
Void CParticleOpSource::SetParticleSpeed(const CFloat32Range& range)
{
    m_ParticleSpeed = range;
}

const CFloat32Range& CParticleOpSource::GetParticleSpeed() const
{
	return m_ParticleSpeed;
}

/**
Set the emit rate of the particle system in particle per second.\n
*/
Void CParticleOpSource::SetEmitRate( Float32 emitRateBySecond )
{
    m_EmitRate = emitRateBySecond;
}

Float32 CParticleOpSource::GetEmitRate( ) const
{
    return m_EmitRate;
}

/**
Set the scale value of each particles
\param scale A range of scale used to randomly pick a scale value for the particles
*/
Void CParticleOpSource::SetParticleScale(const CFloat32Range& scale)
{
    m_ParticleScale = scale;
}

const CFloat32Range& CParticleOpSource::GetParticleScale( ) const
{
	return m_ParticleScale;
}

Void CParticleOpSource::ConfigureNewParticle( CParticleGroup& sim, CParticle& particle )
{
	particle.Size = m_ParticleScale.GetRandomValueInRange();
	particle.Color = m_ParticleColor;
	particle.Age = 0.0f;
	particle.Velocity = CVector3f( 0,1,0 ) * m_ParticleSpeed.GetRandomValueInRange();
}

Bool CParticleOpSource::Serialize( CPersistentArchive& ar )
{
	Int16 version = 0;

	if( ar.BeginScope( WT("OpSource"), version ) == 0 )
	{
		ar.Serialize( m_ParticleSpeed, WT("Speed") );
		ar.Serialize( m_ParticleScale, WT("Scale") );
		ar.Serialize( m_ParticleColor, WT("Color") );
		ar.Serialize( m_EmitRate, WT("Rate") );

		ar.EndScope();
	}
	else
	{
		return FALSE;
	}

	return CParticleOperator::Serialize( ar );
}

Void CParticleOpSource::SetDuration( const CFloat32Range& l )
{
	CParticleOperator::SetDuration( l );
	if( m_EmitTimer.IsStarted() )
		m_EmitTimer.Start();
}

Void CParticleOpSource::OnStart( CParticleGroup& group )
{
	m_EmitTimer.Start();
}

Void CParticleOpSource::OnStop( CParticleGroup& group )
{
	m_EmitTimer.Stop();
}

Void CParticleOpSource::OnSuspend( CParticleGroup& group )
{
	m_EmitTimer.Suspend();
}

Void CParticleOpSource::OnResume( CParticleGroup& group )
{
	m_EmitTimer.Resume();
}