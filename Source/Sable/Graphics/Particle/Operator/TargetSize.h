#ifndef _SABLE_GRAPHICS_PARTICLE_OPERATOR_TARGETSIZE_
#define _SABLE_GRAPHICS_PARTICLE_OPERATOR_TARGETSIZE_

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
class CParticleOpTargetSize : public CParticleOperator
{

	DEFINE_MANAGED_CLASS( CParticleOpTargetSize );

public:

	/** @name Constructor/Destructor*/
	//@{
	CParticleOpTargetSize();
	virtual ~CParticleOpTargetSize();
	//@}

	/** @name Accessors*/
	//@{
	Void SetIncrement( const CFloat32Range& l );
	const CFloat32Range& GetIncrement() const;
	//@}

	/** @name Manipulator*/
	//@{
	Bool Serialize( CPersistentArchive& ar );
	Void Apply( CParticleGroup& sim, CParticle& particle, Time deltaTime );
	//@}

private:

	// Attributes
	CFloat32Range			m_Increment;

};

}

#endif


