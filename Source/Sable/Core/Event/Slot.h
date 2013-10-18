#ifndef _SABLE_CORE_EVENT_SLOT_
#define _SABLE_CORE_EVENT_SLOT_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/Collection/List.h>
#include <Sable/Core/Event/Base.h>

namespace Sable
{

/**
\ingroup CoreEvent
Slot class
*/
template <class TInstance, class TArgs1=Void*, class TArgs2=Void*, class TArgs3=Void*>
class CEventSlot : public CEventBase<TArgs1, TArgs2, TArgs3>
{

public:

	// DataTypes
	typedef CMethodPointer<TInstance, TArgs1, TArgs2, TArgs3> MethodPointer;

    CEventSlot( )
    {
    }

	Void AssignFunction(TInstance *inst, typename MethodPointer::Method0 func )
    {
        m_MethodPointer = MethodPointer(inst, func);
    }

	Void AssignFunction(TInstance *inst, typename MethodPointer::Method1 func )
	{
		m_MethodPointer = MethodPointer(inst, func);
	}

	Void AssignFunction(TInstance *inst, typename MethodPointer::Method2 func )
	{
		m_MethodPointer = MethodPointer(inst, func);
	}

	Void AssignFunction(TInstance *inst, typename MethodPointer::Method3 func )
	{
		m_MethodPointer = MethodPointer(inst, func);
	}

    Void operator() ()
    {
        m_MethodPointer();
    }

    Void operator() (TArgs1 arg1)
    {
        m_MethodPointer(arg1);
    }

    Void operator() (TArgs1 arg1, TArgs2 arg2)
    {
        m_MethodPointer(arg1, arg2);
    }

    Void operator() (TArgs1 arg1, TArgs2 arg2, TArgs3 arg3)
    {
        m_MethodPointer(arg1, arg2, arg3);
    }

protected:

	// Methods

	// Attributes
	MethodPointer m_MethodPointer;

};

}

#endif

