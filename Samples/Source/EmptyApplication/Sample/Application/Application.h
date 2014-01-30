#ifndef _SAMPLE_APPLICATION_APPLICATION_
#define _SAMPLE_APPLICATION_APPLICATION_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/ManagedObject/Ref.h>
#include <Sable/Application/Application.h>
#include <Sable/Application/WindowStandAlone.h>

namespace Sample
{

class CApplicationWindowStandAlone;

class CApplication : public Sable::CApplication
{
    
public:
    
    /** @name Constructor/Destructor*/
    //@{
    CApplication();
    ~CApplication();
    //@}
    
    /** @name Accessors*/
    //@{
    //@}
    
    /** @name Manipulator*/
    //@{
    Void        Run();
    Bool        Update();
    Void        Initialize();
    //@}
    
private:
    
    //Methods
    
    //Attributes
    Sable::CApplicationWindowStandAlone       m_Window;
    
};
    
}

#endif
