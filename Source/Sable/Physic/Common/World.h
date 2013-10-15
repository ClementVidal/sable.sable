#ifndef _SABLE_PHYSIC_COMMON_WORLD_
#define _SABLE_PHYSIC_COMMON_WORLD_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\Collection\List.h>
#include <Sable\Physic\Common\DataTypes.h>
#include <Sable\Core\Memory\FreeListHeap.h>

#include <NxScene.h> 


namespace Sable
{

class CRay;
class CMemoryHeap;
class CPhysicActor;
class CPhysicActorDesc;
class CPhysicJoint;
class CPhysicJointDesc;
class CDebugRenderPass;

/** 
\ingroup Physic
Physic World
*/
class CPhysicWorld : public CManagedObject
{

DEFINE_MANAGED_CLASS( CPhysicWorld );

public:

	/** @name Constructor/Destructor*/
	//@{
	struct SInfo
	{
		SInfo();
		CDebugRenderPass*	DebugRenderer;
		UInt32				MaxActorCount;
		UInt32				MaxJointCount;
	};
	//@}

	/** @name Constructor/Destructor*/
	//@{
	CPhysicWorld( const SInfo& info );
	virtual ~CPhysicWorld();
	//@}

	/** @name Operator*/
	//@{
	//@}

	/** @name Accessors*/
	//@{
    Void                SetGravity( const CVector3f& v ) ;
    CVector3f            GetGravity() const;
    Void                UseDebugDraw( Bool onOff );
    Bool                UseDebugDraw( );
    //@}

	/** @name Manipulator*/
	//@{
	UInt32			OverlapSphere( const CSphere& s, EPhysicActorType type, UInt32 group, UInt32 bufferSize, CPhysicActor** buffer );
    Void            Update( Float64 delta );
    CPhysicActor*   AddActor( CPhysicActorDesc& desc );
    CPhysicJoint*   AddJoint( CPhysicJointDesc& desc );
    //@}

    // Attributes
    NxScene* NXScene;

private:

    // DataTypes

    // Methods
    Void DebugDraw();

	// Attributes
    CDebugRenderPass*       m_DebugRenderer;
    Bool                    m_UseDebugDraw;
	CMemoryFreeListHeap		m_ActorHeap;
	CMemoryFreeListHeap		m_JointHeap;
};


}

#endif


