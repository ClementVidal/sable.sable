#ifndef _CORE_MANAGEDOBJECT_OBJECTMETHOD_
#define _CORE_MANAGEDOBJECT_OBJECTMETHOD_

#include <Sable\Core\Common\DataTypes.h>

namespace Sable
{

class CManagedObject;

/** 
\ingroup CoreManagedObject
Method pointer wrapper class
*/
class CObjectMethod 
{

public:

    /* @name DataTypes*/
    //@{
    typedef Int32 (CManagedObject::* MethodPtr)( Void** args, UInt16 argCount );
    //@}
    
    /* @name Constructor/Destructor*/
    //@{
    CObjectMethod();
    CObjectMethod( CManagedObject& object, MethodPtr method);
    //@}
    
    /** @name Operator*/
    //@{
    Bool operator==( const CObjectMethod& om ) const;
    CObjectMethod&   operator=( const CObjectMethod& other );
    //@}
    
    /* @name Manipulator*/
    //@{
    Int32 Call();
    Int32 Call(Void** args, UInt16 argCount);
    //@}
    
protected:
    
    // Methods
    
    // Attributes
    CManagedObject* m_Object;
    MethodPtr           m_Method;
};

}

#endif
