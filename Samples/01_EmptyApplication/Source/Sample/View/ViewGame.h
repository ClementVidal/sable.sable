#ifndef _SAMPLE_VIEW_VIEWGAME_
#define _SAMPLE_VIEW_VIEWGAME_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/ManagedObject/Ref.h>
#include <Sable/Graphics/Scene/View.h>

namespace Sample 
{

class CGameRenderer;
class CApplication;

class CViewGame : public CView
{

    DEFINE_MANAGED_CLASS( CViewGame );

public:

    /** @name Constructor/Destructor*/
    //@{
    CViewGame();
    CViewGame(CApplication& app);
    virtual ~CViewGame();
    //@}
    
    /** @name Operator*/
    //@{
    //@}
    
    /** @name Accessors*/
    //@{
    //@}
    
    /** @name Manipulator*/
    //@{
    Void            Initialize();
    Void			Update() ;
    Void			Render();
    //@}
    
private:

    // Methods

    //Attributes

};

}

#endif
