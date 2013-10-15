#ifndef _SABLE_SCENE_WORLD_SKYBOXRENDERPASS_
#define _SABLE_SCENE_WORLD_SKYBOXRENDERPASS_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Graphics\Geometry\Header.h>
#include <Sable\Graphics\Shader\Header.h>
#include <Sable\Graphics\RenderPass\RenderPass.h>
#include <Sable\Graphics\States\Header.h>

namespace Sable
{

class CSceneWorld;
class CLensFlare;
class CRenderer;
class CSceneWorld;
class CSkybox;

/**  
\ingroup SceneWorld
Skybox render pass
*/
class CSkyboxRenderPass : public CRenderPass
{

    DEFINE_MANAGED_CLASS( CSkyboxRenderPass );

public:

    /** @name DataTypes*/
    //@{
    //@}

    /** @name Constructor/Destructor*/
    //@{
    CSkyboxRenderPass();
    CSkyboxRenderPass(CRenderer& renderer);
    ~CSkyboxRenderPass();
    //@}

    /** @name Accessors*/
    //@{
    Void      SetSkybox( CSkybox& skybox );
	CSkybox& GetSkybox() const;
    //@}

    /** @name Manipulator*/
    //@{
    Void    Initialize(CRenderer &renderer, CRenderTarget* outputRenderTarget = NULL );
    Bool	ProcessTraversedNode( CNode& node, CRenderer& renderer );
    Void	Render( CRenderer& renderer );
    //@}

private:

    // Method

    //Attribute
    CRef<CSkybox>      m_Skybox;
    CStatesDepthStencil     m_DepthStates;
};

}

#endif
