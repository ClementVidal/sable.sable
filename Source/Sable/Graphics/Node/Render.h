#ifndef _SABLE_GRAPHICS_NODE_RENDER_
#define _SABLE_GRAPHICS_NODE_RENDER_

#include <Sable\Core\Common\DataTypes.h>

#include <Sable\Graphics\Node\Spatial.h>
#include <Sable\Core\ManagedObject\Ref.h>
#include <Sable\Graphics\Geometry\Model.h>
#include <Sable\Graphics\Node\ShaderConnector\Node.h>

namespace Sable
{

class CShader;
class CRenderer;
class CRenderPass;
class CRenderQueueEntry;
class CStaticModelNode;
class CGeometryInstanceBuffer;

/**
\ingroup GraphicsSceneGraph
Base class for object that can be rendered using the RendererQueue.
\n Contain pointer to a Material, a GeometryObject and a LightingContext for shaded objects.
\sa CMaterial, CGeometryMesh
*/
class CNodeRender : public CNodeSpatial
{

    DEFINE_MANAGED_CLASS( CNodeRender );

public:

    /** @name Constructor/Destructor*/
    //@{
    CNodeRender( );
    CNodeRender( CNode&  parent );
    ~CNodeRender();
    //@}

    /** @name Operator*/
    //@{
    //@}

    /** @name Accessors*/
    //@{
	CShaderConnectorGraphNode&	GetShaderConnector();
    Void						GetLocalBoundingBox( CAABox& bbox ) const;
    CGeometryModel*				GetModel( ) const;
    Void						SetModel( const CGeometryModel* model );
	CGeometryInstanceBuffer*	GetInstanceBuffer( ) const;
	Void						SetInstanceBuffer( const CGeometryInstanceBuffer* buffer );
	const CColor&				GetInstanceColor()const;
	Void						SetInstanceColor( const CColor& col );
	Void						SetIsVisible( Bool onOff );
	Bool						GetIsVisible() const;

	Void						SetRenderPriority( UInt32 p );
	UInt32						GetRenderPriority( ) const;
    //@}

    /** @name Manipulator*/
    //@{
    Bool						Serialize( CPersistentArchive& ar );
    virtual Bool				Update( );
    //@}

protected:

	// Attributes
	CColor						m_InstanceColor;

private:

    // Method

    // Attribute
    CRef< CGeometryModel >			m_Model;
	CRef< CGeometryInstanceBuffer >	m_InstanceBuffer;
	CShaderConnectorGraphNode		m_ShaderConnector;
	UInt32							m_RenderPriority;
	Bool							m_IsVisible;

};

}
#endif
