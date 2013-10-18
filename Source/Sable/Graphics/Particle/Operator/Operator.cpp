#include <Sable/Graphics/Particle/Operator/Operator.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1( Sable, CParticleOperator, CManagedObject );

CParticleOperator::CParticleOperator()
{
	m_StartTime = CFloat32Range( 1.0f, 1.0f );
	m_Duration = CFloat32Range( 1.0f, 1.0f );
}

CParticleOperator::~CParticleOperator()
{
}

/**
This method is called once for each ParticleGroup on each new update, but not once for each particle.
It should be used to process any kind of initialization/processing before processing each particle individualy
*/
Void CParticleOperator::BeginNewStep( CParticleGroup& sim, Time deltaTime )
{

}

Bool CParticleOperator::Serialize( CPersistentArchive& ar )
{
	Int16 version = 0;

	if( ar.BeginScope( WT("Operator"), version ) == 0 )
	{
		ar.Serialize( m_StartTime, WT("StartTime") );
		ar.Serialize( m_Duration, WT("Duration") );

		ar.EndScope();
	}
	else
	{
		return FALSE;
	}

	return CManagedObject::Serialize( ar );
}

const CFloat32Range& CParticleOperator::GetStartTime() const
{
	return m_StartTime;
}

Void CParticleOperator::SetStartTime( const CFloat32Range& startTime )
{
	m_StartTime = startTime;
}

Void CParticleOperator::SetDuration( const CFloat32Range& duration )
{
	m_Duration = duration;
}

const CFloat32Range& CParticleOperator::GetDuration() const
{
	return m_Duration;
}

Void CParticleOperator::OnStart( CParticleGroup& group )
{

}

Void CParticleOperator::OnStop( CParticleGroup& group )
{

}

Void CParticleOperator::OnSuspend( CParticleGroup& group )
{

}

Void CParticleOperator::OnResume( CParticleGroup& group )
{

}