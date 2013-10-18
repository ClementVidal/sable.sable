#ifndef _GRAPHICS_RENDERER_RENDERERPASS_
#define _GRAPHICS_RENDERER_RENDERERPASS_

#include <Sable/Core/Common/DataTypes.h>

#include <Sable/Core/ManagedObject/Ref.h>
#include <Sable/Graphics/Node/Node.h>
#include <Sable/Graphics/Node/Render.h>
#include <Sable/Graphics/RenderQueue/RenderQueue.h>
#include <Sable/Graphics/Material/Material.h>

namespace Sable
{

class CRenderTarget;
class CRenderer;
class CMaterial;

/** 
\ingroup GraphicsRenderer
A renderer pass contain a table a shader that can be used with it.
This table is filled by calling CRenderPass::LoadShader().
*/
class CRenderPass : public CManagedObject
{

    DEFINE_MANAGED_CLASS( CRenderPass );

public:

    /** @name Operator*/
    //@{
    //CRenderPass();
    CRenderPass(CRenderer& renderer);
    ~CRenderPass();
    //@}

    /** @name Accessors*/
    //@{
	Void						SetIsEnabled( Bool onOff );
	Bool						GetIsEnabled() const;
    CRenderQueue&               GetRenderQueue() { return m_RenderQueue;}
    CRenderTarget*				GetRenderTarget()const;
    CRenderer&                  GetRenderer() const;
    //@}

    /** @name Manipulator*/
    //@{
    virtual Void Initialize( CRenderer& renderer, CRenderTarget* outputRenderTarget = NULL );
    virtual Void UnInitialize( CRenderer& renderer );

    virtual Bool ProcessTraversedNode( CNode& node, CRenderer& renderer );
    virtual Void Render( CRenderer& renderer );
    //@}
    
protected:

    // Method
    Void                        SetRenderTarget( CRenderTarget* target );

    // Attributes

private:	

    // Type

    // Method

    // Attribute
    CRenderQueue                        m_RenderQueue;
    CRef< CRenderTarget >               m_Output;
    CRenderer*                          m_Renderer;
	Bool								m_IsEnabled;
};

Inline
CRenderer& CRenderPass::GetRenderer() const
{
    return *m_Renderer;
}

Inline
CRenderTarget* CRenderPass::GetRenderTarget()const
{
    return m_Output;
}

Inline
Void CRenderPass::SetRenderTarget( CRenderTarget* target)
{
    m_Output = target;
}

}

#endif
