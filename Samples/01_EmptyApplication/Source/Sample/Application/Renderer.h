#ifndef _SAMPLE_APPLICATION_RENDERER_
#define _SAMPLE_APPLICATION_RENDERER_

#include <Sable/Core/Common/DataTypes.h>

#include <Sable/Graphics/Renderer/Header.h>

#define RENDERERPASS_DEPTH 0
#define RENDERERPASS_STATIC_LIGHTING 1

namespace Sable
{
    class CRenderPassDepth;
    class CRenderPassLighting;
    class CGuiRenderPass;
    class CDebugRenderPass;
}

namespace Sample
{

/** 
\ingroup GraphicsRenderer
Represent the Main Renderer of the system.
\n It can be queried to create material using CMainRenderer::CreateMaterial
*/
class CGameRenderer : public CRenderer
{
	DEFINE_MANAGED_CLASS( CGameRenderer );

public:

	/** @name Operator*/
	//@{
	CGameRenderer( CView& view, const CRenderTarget& renderTaget );
	~CGameRenderer();
	//@}

	/** @name Accessors*/
	//@{
    CDebugRenderPass&                 GetDebugRenderer() const;
	//@}

	/** @name Manipulator*/
	//@{
	virtual		Void	Initialize( CView& view );
	virtual		Void	UnInitialize();
	virtual		Void	Render();
	//@}

private:	

	// Types
	
	// Method

	// Attribute
	CRef<CRenderPassDepth>           m_RendererPassDeth ;
	CRef<CRenderPassLighting>         m_RendererPassDefault ;
    CRef<CGuiRenderPass>              m_UIRendererPass;
    CRef<CDebugRenderPass>           m_DebugRenderer;
	CView*							 m_View;

	// Static Attributes

};

Inline
CDebugRenderPass& CGameRenderer::GetDebugRenderer() const
{
    return *m_DebugRenderer;
}

}

#endif
