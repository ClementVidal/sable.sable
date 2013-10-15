#ifndef _GRAPHICS_PARTICLE_OPERATOR_SOURCERECTANGLE_
#define _GRAPHICS_PARTICLE_OPERATOR_SOURCERECTANGLE_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\Math\Random.h>
#include <Sable\Graphics\Particle\Operator\Source.h>

namespace Sable
{

class CNodeSpatial;

/** 
\ingroup GraphicsParticle
Rectangular particle deflector
*/
class CParticleOpSourceRectangle : public CParticleOpSource
{

	DEFINE_MANAGED_CLASS( CParticleOpSourceRectangle );

public:

	/** @name Constructor/Destructor*/
	//@{
	CParticleOpSourceRectangle();
	virtual ~CParticleOpSourceRectangle();
	//@}

	/** @name Operator*/
	//@{
	//@}

	/** @name Accessors*/
	//@{
	Void	SetXSize( Float32 f );
	Float32 GetXSize() const;
	Void	SetYSize( Float32 f );
	Float32 GetYSize() const;
	Void	SetZSize( Float32 f );
	Float32 GetZSize() const;
	Void				SetOrigin( const CVector3f& dir );
	const CVector3f&		GetOrigin( );
	//@}

	/** @name Manipulator*/
	//@{
	Bool Serialize( CPersistentArchive& ar );
	virtual Void ConfigureNewParticle( CParticleGroup& sim, CParticle& particle ) ;
	//@}

private:

	// Attributes
	Float32			m_XSize;
	Float32			m_YSize;
	Float32			m_ZSize;
	CVector3f		m_Origin;
	CRandom			m_Random;

};

}

#endif


