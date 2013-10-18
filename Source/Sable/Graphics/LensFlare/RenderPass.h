#ifndef _SABLE_GRAPHICS_LENSFLARE_RENDERPASS_
#define _SABLE_GRAPHICS_LENSFLARE_RENDERPASS_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Graphics/Geometry/Header.h>
#include <Sable/Graphics/Shader/Header.h>
#include <Sable/Graphics/RenderPass/RenderPass.h>
#include <Sable/Graphics/States/HEader.h>

#define WorldLensFlareRenderer CLensFlareRenderPass::GetInstance()
#define WORLDLENSFLARERENDERER_MAX_FLARE 32

namespace Sable
{

class CSceneWorld;
class CLensFlare;
class CRenderer;
class CSceneWorld;

/**  
\ingroup SceneWorld
WorldLensFlareRenderer
*/
class CLensFlareRenderPass : public CRenderPass
{

    DEFINE_MANAGED_CLASS( CLensFlareRenderPass );

public:

    /** @name DataTypes*/
    //@{
    struct SVertex
    {
        CVector2f            Pos;
        CVector2f            TexCoord0;
    };
    //@}

    /** @name Constructor/Destructor*/
    //@{
    CLensFlareRenderPass();
    CLensFlareRenderPass(CRenderer& renderer);
    ~CLensFlareRenderPass();
    //@}

    /** @name Accessors*/
    //@{
    Void     AddLensFlare( CLensFlare& flare );
    //@}

    /** @name Manipulator*/
    //@{
    Void    Initialize(CRenderer &renderer);
    Bool    ProcessTraversedNode( CNode& node, CRenderer& renderer );
    Void    Render( CRenderer& renderer );
    //@}

private:

    // Method

    //Attribute
    CLensFlare*						m_FlareTable[WORLDLENSFLARERENDERER_MAX_FLARE];
    UInt32                          m_FlareCount;
    CGeometryVertexBuffer			m_VertexBuffer;
	CGeometryVertexLayout			m_VertexLayout;
    CRef<CShader>                   m_Shader;
    CStatesBlend                    m_BlendStates;
    CStatesDepthStencil             m_DepthStates;
};

}

#endif
