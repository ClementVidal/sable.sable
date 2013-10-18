#ifndef _GRAPHICS_PARTICLE_OPERATOR_SOURCEPOINT_
#define _GRAPHICS_PARTICLE_OPERATOR_SOURCEPOINT_

#include <Sable/Core/Common/Header.h>
#include <Sable/Graphics/Particle/Operator/Source.h>
#include <Sable/Graphics/Node/Header.h>

namespace Sable
{

class CNodeSpatial;

/** 
\ingroup GraphicsParticle
Point particle emitter
*/
class CParticleOpSourcePoint : public CParticleOpSource
{

	DEFINE_MANAGED_CLASS( CParticleOpSourcePoint );

public:

	/** @name Constructor/Destructor*/
	//@{
	CParticleOpSourcePoint();
	virtual ~CParticleOpSourcePoint();
	//@}

	/** @name Operator*/
	//@{
	//@}

	/** @name Accessors*/
	//@{
	Void				SetSpreadAngle( Float32 angle );
	Float32				GetSpreadAngle() const;
	Void				SetOrigin( const CVector3f& origin );
	const CVector3f&		GetOrigin( );
	//@}

	/** @name Manipulator*/
	//@{
	Bool	Serialize( CPersistentArchive& ar );
	virtual Void ConfigureNewParticle( CParticleGroup& sim, CParticle& particle ) ;
	//@}

private:

	// Attributes
	CVector3f		m_Origin;
	Float32			m_SpreadAngle;
	CRandom			m_Random;
};

Inline
Void CParticleOpSourcePoint::SetOrigin( const CVector3f& origin )
{
	m_Origin = origin;
}

Inline
const CVector3f& CParticleOpSourcePoint::GetOrigin() 
{
	return m_Origin;
}

}

#endif


