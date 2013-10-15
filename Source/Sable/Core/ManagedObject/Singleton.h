#ifndef _CORE_MANAGEDOBJECT_SINGLETON_
#define _CORE_MANAGEDOBJECT_SINGLETON_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\Debug\Primitives.h>

namespace Sable
{

/** 
\ingroup CoreManagedObject
Method pointer wrapper class
*/
template <typename T> 
class CSingleton
{

public:

    CSingleton( )
    {
        DebugAssert( !m_Instance );
        Address offset = (Address)(T*)1 - (Address)(CSingleton <T>*)(T*)1;
        m_Instance = (T*)((Address)this + offset);
    }

	virtual ~CSingleton( )
    {  
        DebugAssert( m_Instance );
        m_Instance = NULL;  
    }

    static Bool IsCreated()
    {
        return m_Instance != NULL;
    }

    static T& GetInstance( void )
    {  
        DebugAssert( m_Instance );
        return ( *m_Instance );  
    }

private:

    static T*  m_Instance;
};

template <typename T> 
T* CSingleton<T>::m_Instance = NULL;


}

#endif
