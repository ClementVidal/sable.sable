#ifndef _SABLE_GRAPHICS_RENDERER_RENDERER_
#define _SABLE_GRAPHICS_RENDERER_RENDERER_

#include <Sable/Core/ManagedObject/Ref.h>
#include <Sable/Core/Geometry/Rect2Df.h>
#include <Sable/Graphics/Common/DataTypes.h>
#include <Sable/Graphics/RenderQueue/RenderQueue.h>
#include <Sable/Graphics/Node/Header.h>
#include <Sable/Graphics/Scene/View.h>
#include <Sable/Graphics/Scene/World.h>

#include <Sable/Graphics/Node/ShaderConnector/Header.h>
#include <Sable/Graphics/Camera/ShaderConnector/Camera.h>

namespace Sable
{

class CRenderTarget;
class CMaterial;
class CManagedObject;
class CCamera;
class CNode;
class CDebugRenderPass;
class CRenderPassLighting;
class CRenderPassDepth;
class CShaderConnector;
class CGuiRenderPass;
class CSceneView;
class CViewport;
class CRenderTargetDepthStencil;
class CSceneView;

/** 
\ingroup GraphicsRenderer
Base class for Renderer.
At each frame, 3 mains steps are executed:
    - Update:
    Update the scene graph ( move node and so on )
    - TraverseNodeTree:
    Traverse the scene graph and fill the RenderQueue of the renderer.
    - Render:
    Execute the RenderQueue of this renderer.
*/
class CRenderer : public CManagedObject
{

    DEFINE_MANAGED_CLASS( CRenderer );

public:

    /** @name Type*/
    //@{
    typedef CStack< CRef< CRenderPass > > RendererPassTable;
    //@}

    /** @name Operator*/
    //@{
    CRenderer( );
    ~CRenderer();
    //@}

    /** @name Accessors*/
    //@{
    UInt32                      GetRendererPassCount() const;
    UInt32                      PushRenderPass( CRenderPass& pass );
    CRenderPass&                GetRendererPassAtIndex( UInt32 i ) const;
    CRenderPass&                GetRendererPassByType( const CTypeInfo& type ) const;

	CGuiRenderPass*				GetGuiRenderPass() const;
    CDebugRenderPass*           GetDebugRenderPass() const;
    CRenderPassDepth*           GetDepthRenderPass() const;
	CRenderPassLighting*        GetLightingRenderPass() const;

	CStatesBlend&				GetDefaultBlendStates();
	CStatesRasterizer&			GetDefaultRasterizerStates();
	CStatesDepthStencil&		GetDefaultDepthStencilStates();

	CViewport*					GetCurrentViewport() const;

	Void						SetView( CSceneView* view );
	CSceneView*					GetView( ) const;
    //@}

    /** @name Manipulator*/
    //@{
    virtual     Void    Initialize( );
    virtual     Void    UnInitialize();
	virtual     Void    Render( CRenderTarget& rt, CRenderTargetDepthStencil& ds, CViewport& viewport );
	virtual     Void    Resize( const CVector2i& newSize );

	Void				Activate( CViewport& vpt );
	Void				Activate( CRenderTarget& rt );
	Void				Activate( CRenderTargetDepthStencil& ds );
	Void				Activate( CShader& shader );
	Void				Activate( CGeometryIndexBuffer& ib );
	Void				Activate( CGeometryVertexBuffer& vb, UInt32 index );
	Void				Activate( CGeometryVertexLayout& vl );
	Void				Activate( CGeometryInstanceBuffer& ib, UInt32 index );
    Void				Activate( CStatesRasterizer& sr );
    Void				Activate( CStatesDepthStencil& ds );
    Void				Activate( CStatesBlend& bl );
    Void				Activate( CShaderProgram& program );

	Void				DrawIndexedInstanced( EPrimitiveType primitive, UInt32 indexCount, UInt32 startIndexLocation, UInt32 baseVertexLocation, UInt32 instanceCount );
	Void				DrawInstanced( EPrimitiveType primitive, UInt32 vertexCount, UInt32 offset, UInt32 instanceCount );
	Void				Draw( EPrimitiveType primitive, UInt32 vertexCount, UInt32 offset );
	Void				DrawIndexed( EPrimitiveType primitive, UInt32 indexCount, UInt32 startIndexLocation, UInt32 baseVertexLocation );
	//@}

private:

    // Types

    // Attribute
    RendererPassTable                   m_RendererPassTable;
    CDebugRenderPass*                   m_DebugPass;
    CRenderPassDepth*                   m_DepthPass;
	CRenderPassLighting*				m_LightingPass;
	CGuiRenderPass*						m_GuiPass;

    CShaderProgram*                     m_ActiveShaderProgram[nShaderProgramType_Count];
    CGeometryVertexLayout*              m_ActiveVertexLayout;
    CStatesRasterizer*                  m_ActiveStateRasterizer;
    CStatesDepthStencil*                m_ActiveStateDepthStencil;
    CStatesBlend*                       m_ActiveStateBlend;
	CShader*							m_ActiveShader;
	CGeometryIndexBuffer*				m_ActiveIndexBuffer;
	CGeometryVertexBuffer*				m_ActiveVertexBuffer;
	CGeometryInstanceBuffer*			m_ActiveInstanceBuffer;
	CRenderTarget*                      m_ActiveRenderTarget;
	CRenderTargetDepthStencil*			m_ActiveDepthStencil;

	CViewport*							m_CurrentViewport;

	CStatesBlend						m_DefaultBlendStates;
	CStatesDepthStencil					m_DefaultDepthStencilStates;
	CStatesRasterizer					m_DefaultRasterizerStates;

	CRef<CSceneView>					m_View;

	// Method
	Void                TraverseNodeTree( const CNode& node, CRenderPass& pass  );
	Void				TraverseNodeTree( const CNode& rootNode );

};

}

#endif
