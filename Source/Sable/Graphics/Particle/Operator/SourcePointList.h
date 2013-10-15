#ifndef _SABLE_GRAPHICS_PARTICLE_OPERATOR_POINTLIST_
#define _SABLE_GRAPHICS_PARTICLE_OPERATOR_POINTLIST_

#include <Sable\Core\Common\Header.h>
#include <Sable\Graphics\Particle\Operator\Source.h>
#include <Sable\Graphics\Node\Header.h>

namespace Sable
{

class CNodeSpatial;

/** 
\ingroup GraphicsParticle
Point list particle emitter
*/
class CParticleOpSourcePointList : public CParticleOpSource
{

	DEFINE_MANAGED_CLASS( CParticleOpSourcePointList );

public:

	/** @name DataTypes*/
	//@{
	struct SPoint
	{
		CColor		Color;
		CVector3f	Pos;
		Float32		Size;
	};
	//@}

	/** @name Constructor/Destructor*/
	//@{
	CParticleOpSourcePointList();
	CParticleOpSourcePointList( UInt32 reservedParticleCount );
	virtual ~CParticleOpSourcePointList();
	//@}

	/** @name Operator*/
	//@{
	CArray<SPoint>& GetPointCloud();
	//@}

	/** @name Accessors*/
	//@{
	//@}

	/** @name Manipulator*/
	//@{
	Void	SetParticleCapacity( UInt32 i );
	Void	BeginNewStep( CParticleGroup& sim, Time deltaTime );
	Void	Apply( CParticleGroup& sim, CParticle& particle, Time deltaTime );

	Void	AddPoint( const SPoint& p );
	Void	ClearPointList();
	//@}

private:

	// Methods
	Void ConfigureNewParticle( CParticleGroup& sim, CParticle& particle );

	// Attributes
	CArray<SPoint>		m_PointCloud;
	UInt32				m_PointCount;
};

}

#endif


