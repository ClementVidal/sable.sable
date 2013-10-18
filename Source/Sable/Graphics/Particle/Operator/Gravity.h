#ifndef _GRAPHICS_PARTICLE_OPERATOR_GRAVITY_
#define _GRAPHICS_PARTICLE_OPERATOR_GRAVITY_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/Math/Range.h>
#include <Sable/Graphics/Particle/Operator/Operator.h>

namespace Sable
{

class CParticle;
class CParticleGroup;

/** 
\ingroup Particle
Gravity operator
*/
class CParticleOpGravity : public CParticleOperator
{

	DEFINE_MANAGED_CLASS( CParticleOpGravity );

public:

	/** @name Constructor/Destructor*/
	//@{
	CParticleOpGravity();
	virtual ~CParticleOpGravity();
	//@}

	/** @name Accessors*/
	//@{
	Void SetGravity( const CVector3f& g );
	const CVector3f& GetGravity() const;
	//@}

	/** @name Manipulator*/
	//@{
	Bool Serialize( CPersistentArchive& ar );
	Void Apply( CParticleGroup& sim, CParticle& particle, Time deltaTime );
	//@}

private:

	// Methods

	// Attributes
	CVector3f				m_Gravity;

};

}

#endif


