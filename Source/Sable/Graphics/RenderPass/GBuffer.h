#ifndef _SABLE_GRAPHICS_RENDERER_RENDERERPASSGBUFFER_
#define _SABLE_GRAPHICS_RENDERER_RENDERERPASSGBUFFER_

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
*/
class CRenderPassGBuffer : public CRenderPass
{

DEFINE_MANAGED_CLASS( CRenderPassGBuffer );

public:

    /** @name Operator*/
    //@{
    CRenderPassGBuffer( CRenderer& renderer );
    ~CRenderPassGBuffer();
    //@}

    /** @name Accessors*/
    //@{
    //@}

    /** @name Manipulator*/
    //@{
    Bool ProcessTraversedNode( CNode& node, CRenderer& renderer );
    Void Render( CRenderer& renderer );
    Void Initialize( CRenderer& renderer, const CTextureInfo& info  );
    Void UnInitialize( CRenderer& renderer );
    //@}
    
protected:

    //Method

private:	

    // Type
        
    // Method
//    CMaterial&  GetDefaultMaterial();
//	Void		LoadDefaultMaterial();

    // Attribute
    CRenderTargetTexture    m_RenderTarget[4];
};


}

#endif
