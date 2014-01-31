#ifndef _GRAPHICS_PARTICLE_OPERATOR_SOURCE_
#define _GRAPHICS_PARTICLE_OPERATOR_SOURCE_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/Math/Range.h>
#include <Sable/Graphics/Particle/Operator/Operator.h>

namespace Sable
{

class CParticle;
class CParticleGroup;
class CParticleSystem;

/** 
\ingroup Particle
Base class for a particle source.<br>
Each particle system is binded to a particle emitter.<br>
The only role of the particle emitter is to spawn new particle according specific rules
implemented in each derived class of CParticleOpSource
*/
class CParticleOpSource : public CParticleOperator
{

	DEFINE_MANAGED_CLASS( CParticleOpSource );

public:

	/** @name Constructor/Destructor*/
	//@{
	CParticleOpSource();
	virtual ~CParticleOpSource();
	//@}

	/** @name Accessors*/
	//@{
	UInt32					GetParticleCount()const;

	Void					SetParticleScale(const CFloat32Range& scale);
	const CFloat32Range&	GetParticleScale() const;

	Void					SetEmitRate( Float32 emitRateBySecond );
	Float32					GetEmitRate( ) const;

	Void					SetParticleSpeed(const CFloat32Range& range);
	const CFloat32Range&	GetParticleSpeed( ) const;

	Void					SetParticleColor( const CColor& color );
	const CColor&			GetParticleColor() const;
	Void					SetDuration( const CFloat32Range& l );
	//@}

	/** @name Manipulator*/
	//@{
	Bool	Serialize( CPersistentArchive& ar );
	Void	BeginNewStep( CParticleGroup& sim, Float32 deltaTime );
	Void	Apply( CParticleGroup& sim, CParticle& particle, Float32 deltaTime );
	Void	OnStart( CParticleGroup& group );
	Void	OnStop( CParticleGroup& group );
	Void	OnSuspend( CParticleGroup& group );
	Void	OnResume( CParticleGroup& group );
	//@}

protected:

	// Methods
	virtual Void	ConfigureNewParticle( CParticleGroup& sim, CParticle& particle );

	// Attributes
	UInt32					m_NbParticleToAdd;

private:

	// Methods

	// Attributes
	CTimer					m_EmitTimer;
	CFloat32Range			m_ParticleSpeed;
	CFloat32Range			m_ParticleScale;
	CColor			        m_ParticleColor;
	Float32					m_EmitRate;

	Float32					m_EmitRateFractionalPart;

};

}

#endif


