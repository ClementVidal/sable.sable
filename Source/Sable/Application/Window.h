#ifndef _SABLE_APPLICATION_WINDOW_
#define _SABLE_APPLICATION_WINDOW_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/ManagedObject/ManagedObject.h>
#include <Sable/Graphics/SwapChain/SwapChain.h>

namespace Sable
{

class CRenderer;
class CSwapChainInfo;

/**  
\ingroup Application
*/
class CApplicationWindow : public CManagedObject
{

public:

    /** @name Constructor/destructor */
    //@{
    CApplicationWindow();
    ~CApplicationWindow();
    //@}

    /** @name Manipulator*/
    //@{
    Void		SetRenderer( CRenderer* view );
    CRenderer*		GetRenderer() const;

    CSwapChain&		GetSwapChain();

    virtual Bool	Initialize( const CSwapChainInfo& swapChainDesc );
    virtual Bool	Update();
    virtual Void	Resize( const CVector2i& newSize );
    //@}

    /** @name Accessors*/
    //@{
    virtual UInt32    GetHandle() const = 0;
    //@}

private:

    // Friend ship

    // Attribute

    // Methods
    CRef<CRenderer>         m_Renderer;
    CSwapChain		    m_SwapChain;
};

}

#endif
