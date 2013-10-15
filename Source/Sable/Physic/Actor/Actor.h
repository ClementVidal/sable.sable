#ifndef _SABLE_PHYSIC_ACTOR_ACTOR_
#define _SABLE_PHYSIC_ACTOR_ACTOR_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\Math\Vector3f.h>
#include <Sable\Core\ManagedObject\ManagedObject.h>

#include <NxActor.h>

namespace Sable
{

class CPhysicWorld;

/** 
\ingroup PhysicActor
Physic actor
*/
class CPhysicActor : public CManagedObject
{

    DEFINE_MANAGED_CLASS( CPhysicActor )

public:

    /** @name DataTypes*/
    //@{
    //@}

    /** @name Accessors*/
    //@{
	Void		SetSolverIterationCount( UInt32 count );

	Void		SetMass( Float32 m );
	Float32		GetMass()const;

	Void        SetLinearDamping( Float32 d );
    Float32     GetLinearDamping() const;
	Void        SetAngularDamping( Float32 d );
	Float32     GetAngularDamping() const;

	Void        SetLinearVelocity( const CVector3f& v );
    CVector3f    GetLinearVelocity() const;
    Void        SetAngularVelocity( const CVector3f& v );
    CVector3f    GetAngularVelocity() const;
    //@}

    /** @name Manipulator*/
    //@{
    Void        AddLinearForce( const CVector3f& f, Bool wakeUp = TRUE );
    Void        AddLinearImpulse( const CVector3f& f, Bool wakeUp = TRUE );
    Void        SetWorldPosition( const CVector3f& p );
	Void		SetWorldMatrix( const CMatrix4x4f& m );
	Void        GetWorldMatrix( CMatrix4x4f& m );
    CVector3f    GetWorldPosition() const;

	Void		PutToSleep();
	Void		WakeUp();
	//@}

	// Attributes
    NxActor*        NXActor;
	Void*			UserData;

private:

    // Friendship
    friend CPhysicWorld;

    /** @name Constructor/Destructor*/
    //@{
    CPhysicActor( CPhysicWorld& world );
    virtual ~CPhysicActor();
    //@}

    // Attributes
    CPhysicWorld* m_World;
};


}

#endif


