#ifndef _SABLE_GRAPHICS_PARTICLE_OPERATOR_OPERATOR_
#define _SABLE_GRAPHICS_PARTICLE_OPERATOR_OPERATOR_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\ManagedObject\ManagedObject.h>

namespace Sable
{

class CParticle;
class CParticleGroup;

/** 
\ingroup GraphicsParticle
Particle System
*/
class CParticleOperator : public CManagedObject
{

    DEFINE_MANAGED_CLASS( CParticleOperator  );
    
public:
    
    /** @name Constructor/Destructor*/
    //@{
    CParticleOperator();
    virtual ~CParticleOperator();
    //@}
    
    /** @name Accessors*/
    //@{
	virtual Void SetStartTime( const CFloat32Range& l );
	const CFloat32Range& GetStartTime() const;
	virtual Void SetDuration( const CFloat32Range& l );
	const CFloat32Range& GetDuration() const;
    //@}
    
    /** @name Manipulator*/
    //@{
	Bool Serialize( CPersistentArchive& ar );
	virtual Void BeginNewStep( CParticleGroup& sim, Time deltaTime );
	virtual Void Apply( CParticleGroup& sim, CParticle& particle, Time deltaTime ) = 0;
	virtual Void OnStart( CParticleGroup& group );
	virtual Void OnStop( CParticleGroup& group );
	virtual Void OnSuspend( CParticleGroup& group );
	virtual Void OnResume( CParticleGroup& group );
    //@}

protected:

    //Method

private:

	// Attributes
	CFloat32Range		m_StartTime;
	CFloat32Range		m_Duration;

};

}

#endif


