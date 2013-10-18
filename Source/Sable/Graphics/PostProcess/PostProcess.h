#ifndef _GRAPHICS_POSTPROCESS_POSTPROCESS_
#define _GRAPHICS_POSTPROCESS_POSTPROCESS_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/ManagedObject/Header.h>
#include <Sable/Core/Collection/List.h>
#include <Sable/Graphics/RenderPass/RenderPass.h>

namespace Sable
{

class CRenderer;
class CRenderTarget;

/** 
Render Pipeline.
*/
class CPostProcess : public CRenderPass
{

    DEFINE_MANAGED_CLASS( CPostProcess );

public:

    /** @name Type*/
    //@{
    //@}

    /** @name Constructor*/
    //@{
    CPostProcess( CRenderer& renderer );
    virtual ~CPostProcess();
    //@}

    /** @name Operator*/
    //@{
    //@}

    /** @name Accessors*/
    //@{
    CRenderer&                  GetRenderer() const;
    //@}

    /** @name Manipulator*/
    //@{
    virtual Void				Initialize( CRenderer& renderer, CRenderTarget* outputRenderTarget = NULL );
    virtual Void				UnInitialize();

    virtual Void                Render( CRenderer& renderer );
    //@}

protected:

    // Method

    // Attributes;

private:	

    // Type

    // Method

    // Attribute
    CRenderer*                              m_Renderer;

};

Inline
CRenderer& CPostProcess::GetRenderer() const
{
    return *m_Renderer;
}

}

#endif
