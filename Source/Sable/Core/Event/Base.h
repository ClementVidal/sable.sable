#ifndef _SABLE_CORE_EVENT_BASE_
#define _SABLE_CORE_EVENT_BASE_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/Collection/List.h>
#include <Sable/Core/Common/MethodPointer.h>
#include <Sable/Core/Debug/Primitives.h>

namespace Sable
{

/**
Event Base class
*/
template <class TArgs1=Void*, class TArgs2=Void*, class TArgs3=Void*>
class CEventBase
{

public:

	// DataTypes
	typedef CEventBase<TArgs1, TArgs2, TArgs3>  EventBase;

    virtual Void operator() () = 0;
    virtual Void operator() (TArgs1 arg1) = 0;
    virtual Void operator() (TArgs1 arg1, TArgs2 arg2) = 0;
    virtual Void operator() (TArgs1 arg1, TArgs2 arg2, TArgs3 arg3) = 0;

	// Ctrs
	CEventBase() :
		m_OutputList( MemoryManager.GetEventHeap() ),
		m_InputList( MemoryManager.GetEventHeap() )
	{
	}

	~CEventBase()
	{
		DisconnectAll();
	}

    Void Connect( EventBase &other )
    {
        if (&other == this)
        { 
            DebugError("CEventBase::Connect - Cannot connect a slot to itself"); 
            return; 
        }

        other.AddInput( *this );
        AddOutput( other );
    }

    Void Disconnect(EventBase &other)
    {
        other.RemoveInput(*this);
        RemoveOutput(other);
    }

    Void DisconnectAll()
    {
        ListIterator it;
        ForEachItem( it, m_OutputList )
        {
            (*it)->RemoveInput(*this);
        }
        m_OutputList.ClearAllItems();

        ForEachItem( it, m_InputList )
        {
            (*it)->RemoveOutput(*this);
        }
        m_InputList.ClearAllItems();
    }

protected:

	// DataType
	typedef CList<EventBase*>						List;
	typedef typename CList<EventBase*>::Iterator    ListIterator;

    // Attributes
    List           m_OutputList;
    List           m_InputList;

    // Methods
    Void RemoveOutput(EventBase &other)
    {
        m_OutputList.RemoveItem( &other );
    }
    Void RemoveInput(EventBase &other)
    {
        m_InputList.RemoveItem( &other );
    }

    Void AddOutput( EventBase &other )
    {
        if ( !m_OutputList.HasItem( &other ) )
        {
            m_OutputList.AddItemAtEnd( &other );
        }
    }
    Void AddInput( EventBase &other )
    {
        if ( !m_InputList.HasItem( &other ) )
        {
            m_InputList.AddItemAtEnd( &other );
        }
    }
};

}

#endif

