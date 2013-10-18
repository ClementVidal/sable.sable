#ifndef _SABLE_GRAPHICS_NODE_RENDERPHYSIC_
#define _SABLE_GRAPHICS_NODE_RENDERPHYSIC_

#include <Sable/Core/Common/DataTypes.h>

#include <Sable/Graphics/Node/Render.h>

namespace Sable
{

class CPhysicActor;

/**
\ingroup GraphicsSceneGraph

Same as a CNodeRenderPhysic, but the node is automatically positioned in world space according 
to its attached CPhysicActor
*/
class CNodeRenderPhysic : public CNodeRender
{

    DEFINE_MANAGED_CLASS( CNodeRenderPhysic );

public:

    /** @name Constructor/Destructor*/
    //@{
    CNodeRenderPhysic( );
    CNodeRenderPhysic( CNode&  other );
    virtual ~CNodeRenderPhysic();
    //@}

    /** @name Accessors*/
    //@{
	Void				SetScale( const CVector3f& scale );
	const CVector3f&	GetScale( ) const;
	Void				SetAttribute( EAttribute attrib, Bool onOff );
	Void				SetActor( CPhysicActor* actor );
	CPhysicActor*		GetActor() const;
	Void				SetLocalMatrix(const CMatrix4x4f& matrix);
    //@}

    /** @name Manipulator*/
    //@{
    virtual Bool	Update( );
    //@}

private:

    // Method

    // Attribute
    CRef< CPhysicActor >    m_PhysicActor;
	CVector3f				m_Scale;

};

}
#endif
