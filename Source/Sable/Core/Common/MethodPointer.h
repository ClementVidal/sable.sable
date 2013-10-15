#ifndef _SABLE_CORE_COMMON_METHODPOINTER_
#define _SABLE_CORE_COMMON_METHODPOINTER_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\Debug\Primitives.h>

namespace Sable
{

/**
\ingroup CoreCommon
Internal base class for calling methods
*/
template <typename TInstance, typename TArg1=Void*, typename TArg2=Void*, typename TArg3=Void*, typename TArg4=Void*, typename TArg5=Void*>
class CMethodPointer
{
public:

	// DataTypes
	typedef Void (TInstance::*Method0)();
	typedef Void (TInstance::*Method1)(TArg1);
	typedef Void (TInstance::*Method2)(TArg1, TArg2);
	typedef Void (TInstance::*Method3)(TArg1, TArg2, TArg3);
	typedef Void (TInstance::*Method4)(TArg1, TArg2, TArg3, TArg4);
	typedef Void (TInstance::*Method5)(TArg1, TArg2, TArg3, TArg4, TArg5);

	CMethodPointer()
    {
        m_ParamCount = 0;
        m_MethodUnion.M0 = NULL;
        m_Instance = NULL;
    }

	// Constructor
	CMethodPointer (TInstance *instance, Method0 method)
	{
		m_MethodUnion.M0 = method;
		m_Instance = instance;
		m_ParamCount = 0;	
	}

	CMethodPointer (TInstance *instance, Method1 method)
	{
		m_MethodUnion.M1 = method;
		m_Instance = instance;
		m_ParamCount = 1;	
	}

	CMethodPointer (TInstance *instance, Method2 method)
	{
		m_MethodUnion.M2 = method;
		m_Instance = instance;
		m_ParamCount = 2;	
	}

	CMethodPointer (TInstance *instance, Method3 method)
	{
		m_MethodUnion.M3 = method;
		m_Instance = instance;
		m_ParamCount = 3;	
	}

    CMethodPointer (TInstance *instance, Method4 method)
    {
        m_MethodUnion.M4 = method;
        m_Instance = instance;
        m_ParamCount = 4;	
    }

    CMethodPointer (TInstance *instance, Method5 method)
    {
        m_MethodUnion.M5 = method;
        m_Instance = instance;
        m_ParamCount = 5;	
    }

	// Set external Callback or clear Callback
    CMethodPointer& operator=( const CMethodPointer& other )
    {
        m_Instance = other.m_Instance;
        m_MethodUnion = other.m_MethodUnion;
        m_ParamCount = other.m_ParamCount;
        return *this;
    }

    Bool IsValid()
    {
        return (m_MethodUnion.M0 && m_Instance);
    }

    Void operator() ()
    {
		if( IsValid() )
        {
		    DebugAssert( m_ParamCount == 0 );
		    (m_Instance->*m_MethodUnion.M0)();
        }
    }

    Void operator() (TArg1 Arg1)
    {
		if( IsValid() )
        {
	        DebugAssert( m_ParamCount == 1 );
	        (m_Instance->*m_MethodUnion.M1)(Arg1);
        }
    }

    Void operator() (TArg1 Arg1, TArg2 Arg2)
    {
		if( IsValid() )
        {
	        DebugAssert( m_ParamCount == 2 );
            (m_Instance->*m_MethodUnion.M2)(Arg1, Arg2);
        }
    }

    Void operator() (TArg1 Arg1, TArg2 Arg2, TArg3 Arg3)
    {
		if( IsValid() )
        {
		    DebugAssert( m_ParamCount == 3 );
            (m_Instance->*m_MethodUnion.M3)(Arg1, Arg2, Arg3);
        }
    }

    Void operator() (TArg1 Arg1, TArg2 Arg2, TArg3 Arg3, TArg4 Arg4)
    {
        if( IsValid() )
        {
            DebugAssert( m_ParamCount == 4 );
            (m_Instance->*m_MethodUnion.M4)(Arg1, Arg2, Arg3, Arg4);
        }
    }

    Void operator() (TArg1 Arg1, TArg2 Arg2, TArg3 Arg3, TArg4 Arg4, TArg5 Arg5)
    {
        if( IsValid() )
        {
            DebugAssert( m_ParamCount == 5 );
            (m_Instance->*m_MethodUnion.M5)(Arg1, Arg2, Arg3, Arg4, Arg5);
        }
    }

protected:

	// DataTypes
	union UMethodUnion
	{
		Method0 M0;
		Method1 M1;
		Method2 M2;
		Method3 M3;
		Method3 M4;
		Method3 M5;
	};

	// Attributes
	Int32			m_ParamCount;
	TInstance*		m_Instance;
	UMethodUnion	m_MethodUnion;	

};

}

#endif

