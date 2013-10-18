#ifndef _SABLE_CORE_EVENT_SIGNAL_
#define _SABLE_CORE_EVENT_SIGNAL_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/Collection/List.h>
#include <Sable/Core/Event/Base.h>
#include <Sable/Core/Debug/Primitives.h>


#define EVENT_CONNECT_SLOT( signalSrc, slotDst, func ) \
        (slotDst).AssignFunction( this, (func) ); \
        (signalSrc).Connect( (slotDst) ); \


#define EVENT_CONNECT_SIGNAL( signalSrc, signalDst ) \
    (signalSrc).Connect( (signalDst) ); \

namespace Sable
{

/**
\ingroup CoreEvent
Signal class
*/
template <class TArgs1=Void*, class TArgs2=Void*, class TArgs3=Void*>
class CEventSignal : public CEventBase<TArgs1, TArgs2, TArgs3>
{

public:

    /**
    Constructor
    */
    CEventSignal( )
    {
    }

	Void operator() ()
    {
        typename CList< CEventBase<TArgs1, TArgs2, TArgs3 > * >::Iterator it;
        ForEachItem( it, this->m_OutputList )
        {
            (*it)->operator() ();
        }
    }

    Void operator() (TArgs1 arg1)
    {
		ListIterator it;
        ForEachItem( it, this->m_OutputList )
        {
            (*it)->operator() ( arg1 );
        }
    }

    Void operator() (TArgs1 arg1, TArgs2 arg2)
    {
		ListIterator it;
        ForEachItem( it, this->m_OutputList )
        {
            (*it)->operator() ( arg1, arg2 );
        }
    }

    Void operator() (TArgs1 arg1, TArgs2 arg2, TArgs3 arg3)
    {
		ListIterator it;
        ForEachItem( it, this->m_OutputList )
        {
            (*it)->operator() ( arg1, arg2, arg3 );
        }
    }

protected:

    // DataTypes
    typedef typename CList< CEventBase<TArgs1, TArgs2, TArgs3 > * >::Iterator ListIterator;

	// Attributes

    // Method

};


}

#endif

