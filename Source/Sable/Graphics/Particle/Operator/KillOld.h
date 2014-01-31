#ifndef _SABLE_GRAPHICS_PARTICLE_OPERATOR_AGELIMIT_
#define _SABLE_GRAPHICS_PARTICLE_OPERATOR_AGELIMIT_

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
class CParticleOpKillOld : public CParticleOperator
{

	DEFINE_MANAGED_CLASS( CParticleOpKillOld );

public:

	/** @name Constructor/Destructor*/
	//@{
	CParticleOpKillOld();
	virtual ~CParticleOpKillOld();
	//@}

	/** @name Accessors*/
	//@{
	Void SetAgeLimit( const CFloat32Range& l );
	const CFloat32Range& GetAgeLimit() const;
	//@}

	/** @name Manipulator*/
	//@{
	Bool Serialize( CPersistentArchive& ar );
	Void Apply( CParticleGroup& sim, CParticle& particle, Float32 deltaTime );
	//@}

private:

	// Attributes
	CFloat32Range			m_AgeLimit;


};

}

#endif


