#include <Sable\Graphics\Particle\Group.h>

#include <Sable\Graphics\Particle\Operator\Operator.h>
#include <Sable\Graphics\Renderer\Header.h>
#include <Sable\Graphics\Particle\System.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1_ALLOC( Sable, CParticleGroup, CManagedObject );

/**
This will create an empty particle group.
SetParticleCapacity must be called afterward to define the number of available particle in this group
*/
CParticleGroup::CParticleGroup()
{	
	Pause();
}

/**
This will create particle group of a given capacity.
*/
CParticleGroup::CParticleGroup( UInt32 particleCapacity )
{	
	Pause();
	m_ParticlePool.SetItemCount( particleCapacity );
}

CParticleGroup::~CParticleGroup()
{
}

Void CParticleGroup::SetParticleCapacity( UInt32 particleCapacity )
{
	m_ParticlePool.SetItemCount( particleCapacity );
}

Void CParticleGroup::Start()
{
	m_Timer.Start();
	m_LastUpdateTime = m_Timer.GetElapsedSeconds();

	OperatorTable::Iterator it;
	ForEachItem( it, m_OperatorTable )
	{
		(*it)->OnStart( *this );
	}
}

Void CParticleGroup::Stop()
{
	m_LastUpdateTime = 0.0;
	m_Timer.Stop();
	m_ParticlePool.SetItemCount(0);

	OperatorTable::Iterator it;
	ForEachItem( it, m_OperatorTable )
	{
		(*it)->OnStop( *this );
	}
}

Void CParticleGroup::Pause()
{
	m_LastUpdateTime = 0.0;
	m_Timer.Suspend();

	OperatorTable::Iterator it;
	ForEachItem( it, m_OperatorTable )
	{
		(*it)->OnSuspend( *this );
	}
}

Bool CParticleGroup::IsSuspended() const
{
	return m_Timer.IsSuspended();
}

Bool CParticleGroup::IsStarted() const
{
	return m_Timer.IsStarted();
}

Void CParticleGroup::Resume()
{
	m_Timer.Resume();
	m_LastUpdateTime = m_Timer.GetElapsedSeconds();

	OperatorTable::Iterator it;
	ForEachItem( it, m_OperatorTable )
	{
		(*it)->OnResume( *this );
	}
}

Void CParticleGroup::Update( const CParticleSystem& sys, const CRenderer& renderer )
{
	UInt32 i;
	if( !m_Timer.IsStarted() || m_Timer.IsSuspended() )
		return;

	UpdateDependentStates( sys );

	OperatorTable::Iterator it;
	CParticle* buffer = GetBuffer();

	Time currentTime = m_Timer.GetElapsedSeconds();
	Time deltaTime = currentTime - m_LastUpdateTime;
	m_LastUpdateTime = currentTime;

	DebugAssert( deltaTime >= 0.0f );

	ForEachItem( it, m_OperatorTable )
	{
		(*it)->BeginNewStep( *this, deltaTime );
	}

	ForEachItem( it, m_OperatorTable )
	{
		for( i=0;i<GetParticleCapacity();i++)
		{
			(*it)->Apply( *this, buffer[i], deltaTime );
		}
	}

	for( i=0;i<GetParticleCapacity();i++)
	{
		if( buffer[i].Age >= 0.0f )
		{
			buffer[i].Age += (Float32) deltaTime;
			buffer[i].Position += buffer[i].Velocity * (Float32) deltaTime;
		}
	}

}

Void CParticleGroup::UpdateDependentStates( const CParticleSystem& sys )
{
	m_Origin = sys.GetWorldPosition();
	m_Direction = sys.GetWorldMatrix().GetYComponent();
}

const CVector3f&	CParticleGroup::GetOrigin()const
{
	return m_Origin;
}

const CVector3f&	CParticleGroup::GetDirection()const
{
	return m_Direction;
}

const CParticleGroup::OperatorTable& CParticleGroup::GetOperators() const
{
	return m_OperatorTable;
}

Void CParticleGroup::AddOperator( CParticleOperator& ope )
{
	m_OperatorTable.AddItemAtEnd( &ope );
	if( IsStarted() )
	{
		ope.OnStart( *this );
		if( IsSuspended() )
		{
			ope.OnSuspend( *this );
		}
	}
}

Void CParticleGroup::RemoveOperator(  CParticleOperator& ope )
{
	m_OperatorTable.RemoveItem( &ope );
}

Void CParticleGroup::RemoveAllOperators()
{
	m_OperatorTable.ClearAllItems();
}

Void CParticleGroup::GetParticleMatrix( const CCamera& cam, const CParticle& particle , CMatrix4x4f& rotationMatrix)
{
	CMatrix4x4f transfo = cam.GetInverseViewMatrix();
	CMatrix4x4f particleScale;
	CMatrix4x4f rot;
	
	CMatrix4x4f wvp = cam.GetViewProjectionMatrix();

	CVector3f t = particle.Position;
	t.TransformPosition( wvp );

	// Spécial Tau ceti 
	rot.SetFromAxisAndAngle( CVector3f::ZAxis, MathDegreeToRadian( 90.0f * t.GetX() * 1.4f ) );

	particleScale.SetFromScale(CVector3f( particle.Size, particle.Size, particle.Size) );
	rotationMatrix = transfo;
	transfo.SetTranslationComponent( CVector3f::Zero );
	rotationMatrix =  particleScale * rot * transfo ;

}

Bool CParticleGroup::Serialize( CPersistentArchive& ar )
{
	Int16 version = 0;
	UInt32 poolSize = m_ParticlePool.GetItemCount();
	UInt32 operatorCount = m_OperatorTable.GetItemCount();
	UInt32 i;

	if( ar.BeginScope( WT("ParticleGroup"), version ) == 0 )
	{
		ar.Serialize( m_Origin, WT("Origin") );
		ar.Serialize( m_Direction, WT("Direction") );
		ar.Serialize( poolSize, WT("PoolSize") );
		ar.Serialize( operatorCount, WT("OperatorCount") );

		if( ar.BeginScope( WT("Operators"), version ) == 0 )
		{
			if( ar.IsLoading() )
			{
				m_ParticlePool.SetItemCount( poolSize );
				CRef<CParticleOperator> op;
				m_OperatorTable.ClearAllItems();
				for( i=0;i<operatorCount;i++ )
				{
					if( ar.BeginScope( WT("Operator"), version ) == 0 )
					{
						ar.Serialize( op, WT("Operator") );
						m_OperatorTable.AddItemAtEnd( op );
						ar.EndScope();
					}
				}
			}
			else
			{
				OperatorTable::Iterator it;
				ForEachItem( it, m_OperatorTable )
				{
					if( ar.BeginScope( WT("Operator"), version ) == 0 )
					{
						ar.Serialize( (*it), WT("Operator") );
						ar.EndScope();
					}
				}
			}
			ar.EndScope();
		}
		else
		{
			return FALSE;
		}
		ar.EndScope();
	}
	else
	{
		return FALSE;
	}

	return TRUE;
}