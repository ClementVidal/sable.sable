#ifndef _SABLE_GRAPHICS_PARTICLE_OPERATOR_TARGETCOLOR_
#define _SABLE_GRAPHICS_PARTICLE_OPERATOR_TARGETCOLOR_

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
class CParticleOpTargetColor : public CParticleOperator
{

	DEFINE_MANAGED_CLASS( CParticleOpTargetColor );

public:

	/** @name Constructor/Destructor*/
	//@{
	CParticleOpTargetColor();
	virtual ~CParticleOpTargetColor();
	//@}

	/** @name Accessors*/
	//@{
	Void SetIncrement( const CVector4Range& l );
	const CVector4Range& GetIncrement() const;
	//@}

	/** @name Manipulator*/
	//@{
	Bool Serialize( CPersistentArchive& ar );
	Void Apply( CParticleGroup& sim, CParticle& particle, Float32 deltaTime );
	//@}

private:

	// Attributes
	CVector4Range			m_Increment;

};

}

#endif


