#ifndef _GRAPHICS_RENDERER_RENDERERPASSDEPTH_
#define _GRAPHICS_RENDERER_RENDERERPASSDEPTH_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/ManagedObject/Macro.h>
#include <Sable/Core/ManagedObject/Ref.h>

#include <Sable/Graphics/RenderTarget/Texture.h>
#include <Sable/Graphics/Shader/Header.h>
#include <Sable/Graphics/RenderPass/RenderPass.h>
#include <Sable/Graphics/Light/Light.h>
#include <Sable/Graphics/Node/Render.h>
#include <Sable/Graphics/States/Header.h>

namespace Sable
{

class CRenderer;

/** 
\ingroup GraphicsRenderer
Base class for renderer pass.
*/
class CRenderPassDepth : public CRenderPass
{

DEFINE_MANAGED_CLASS( CRenderPassDepth );

public:

    /** @name Operator*/
    //@{
    CRenderPassDepth( CRenderer& renderer );
    virtual ~CRenderPassDepth();
    //@}

    /** @name Accessors*/
    //@{
    Void        SetRenderDepthTexture( const Bool renderDepthTexture );
    Bool        GetRenderDepthTexture() const;
    const CRenderTargetTexture& GetDepthTexture() const;
    //@}

    /** @name Manipulator*/
    //@{
    Bool ProcessTraversedNode( CNode& node, CRenderer& renderer );
    Void Render( CRenderer& renderer );
    Void Initialize( CRenderer& renderer, const CRenderTargetInfo& info );
    Void UnInitialize( CRenderer& renderer );
    //@}
    
protected:

    //Method

private:	

    // Type
        
    // Method
    CMaterial&  GetDefaultMaterial();
	Void		LoadDefaultMaterial();

    // Attribute
    Bool                        m_RenderDepthTexture;
    CRenderTargetTexture		m_DepthTexture;
	CShader						m_StandardShader;
#ifdef SETUP_IMPLTYPE_DIRECTX
    CShader						m_InstancingShader;
#endif
    CStatesRasterizer           m_RasterizerStates;
    CStatesBlend                m_BlendStates;
    CStatesDepthStencil         m_DepthStates;
	CMaterial					m_DefaultMaterial;
};


}

#endif
