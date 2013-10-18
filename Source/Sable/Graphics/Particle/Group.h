#ifndef _SABLE_GRAPHICS_PARTICLE_GROUP_
#define _SABLE_GRAPHICS_PARTICLE_GROUP_

#include <Sable/Core/Common/DataTypes.h>

#include <Sable/Core/Time/Timer.h>
#include <Sable/Core/Math/Range.h>
#include <Sable/Core/Math/Random.h>

#include <Sable/Graphics/Particle/Particle.h>
#include <Sable/Graphics/Geometry/Header.h>

namespace Sable
{

class CMaterial;
class CParticleOpSource;
class CParticleOperator;
class CParticleSystem;

/** 
\ingroup GraphicsParticle
A particle group contain a particle pool that can be managed individually from the other particle group of a given particle system.
Each group has it's own set of operators that are applied ONLY to this group.
*/
class CParticleGroup : public CManagedObject
{

    DEFINE_MANAGED_CLASS( CParticleGroup );

public:

	/** @name Types*/
	//@{
	typedef CList< CRef<CParticleOperator> > OperatorTable;
	//@}

    /** @name Constructor/Destructor*/
    //@{
    CParticleGroup();
    CParticleGroup( UInt32 particleCapacity );
    virtual ~CParticleGroup();
    //@}

    /** @name Operator*/
    //@{
    //@}

    /** @name Accessors*/
    //@{
	const CVector3f&			GetOrigin()const;
	const CVector3f&			GetDirection()const;

	Bool					IsStarted() const;
	Bool					IsSuspended() const;
    UInt32					GetParticleCapacity() const;
	Void					SetParticleCapacity( UInt32 particleCapacity );
	const OperatorTable&	GetOperators() const;
	//@}

    /** @name Manipulator*/
	//@{
	Void            AddOperator(  CParticleOperator& ope );
	Void            RemoveOperator(  CParticleOperator& ope );

    Void			Update( const CParticleSystem& sys, const CRenderer& renderer );
    Void            Start();
    Void            Stop();
	Void            Pause();
    Void            Resume();
    CParticle*      GetBuffer( )const;
    Void            RemoveAllOperators();
	Void			GetParticleMatrix( const CCamera& cam, const CParticle& particle , CMatrix4x4f& rotationMatrix);

	Bool			Serialize( CPersistentArchive& ar );
	//@}

protected:

	// Friendship
	friend class CParticleOpSource;

    // Data type

    // Methods
	Void UpdateDependentStates( const CParticleSystem& sys );
    
	// Attributes
    CArray<CParticle>		m_ParticlePool;
	OperatorTable			m_OperatorTable;
	Time					m_LastUpdateTime;
	CTimer					m_Timer;

	CVector3f				m_Origin;
	CVector3f				m_Direction;

};

Inline
UInt32 CParticleGroup::GetParticleCapacity() const
{
    return m_ParticlePool.GetItemCount();
}

Inline
CParticle* CParticleGroup::GetBuffer( ) const
{
    return m_ParticlePool.GetBuffer();
}



}

#endif


