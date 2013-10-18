#ifndef _SABLE_GRAPHICS_RENDERPASS_DEFAULT_
#define _SABLE_GRAPHICS_RENDERPASS_DEFAULT_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/ManagedObject/Macro.h>
#include <Sable/Core/ManagedObject/Ref.h>

#include <Sable/Graphics/RenderPass/RenderPass.h>
#include <Sable/Graphics/Light/Light.h>
#include <Sable/Graphics/Node/Render.h>
#include <Sable/Graphics/Texture/TextureCube.h>
#include <Sable/Graphics/States/Header.h>

namespace Sable
{

/**
\ingroup GraphicsRenderer
Base class for renderer pass.
*/
class CRenderPassLighting : public CRenderPass
{

DEFINE_MANAGED_CLASS( CRenderPassLighting );

public:

    /** @name Operator*/
    //@{
    CRenderPassLighting( CRenderer& renderer );
    ~CRenderPassLighting();
    //@}

    /** @name Accessor*/
    //@{
    //@}

    /** @name Manipulator*/
    //@{
    virtual Bool ProcessTraversedNode( CNode& node, CRenderer& renderer );
    virtual	Void Render( CRenderer& renderer );
    virtual	Void Initialize( CRenderer& renderer, CRenderTarget* outputRenderTarget = NULL );
    virtual	Void UnInitialize( CRenderer& renderer );
    //@}
    
protected:

    //Method

private:	

    // Type
        
    // Method
	CMaterial&	GetDefaultMaterial();
	Void		LoadDefaultMaterial();

    // Attribute
    CStatesDepthStencil     m_DepthStates;
	CMaterial				m_DefaultMaterial;
	CShader					m_DefaultShader;

};

}

#endif
