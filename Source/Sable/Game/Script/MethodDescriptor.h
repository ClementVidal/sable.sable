#ifndef _SABLE_GAME_SCRIPT_METHODDESCRIPTOR_
#define _SABLE_GAME_SCRIPT_METHODDESCRIPTOR_

#include <Sable\Game\Script\ArgumentDescriptor.h>

namespace Sable
{

// Test if an argument is void or not
template< class Type >
struct IsValidArg 
{ enum { Value = 1 }; };

template<>
struct IsValidArg< Void >
{ enum { Value = 0 }; };

// Count the number of valid argument
template< class TArg1, class TArg2, class TArg3 >
struct GetValidArgCount
{ enum { Value = IsValidArg<TArg1>::Value + IsValidArg<TArg2>::Value + IsValidArg<TArg3>::Value }; };

// Switch to take into account the number of valid args
// And test in each case if method is const or not
template< class TInstance, class TReturn, class TArg1, class TArg2, class TArg3, Bool isConst, int ArgCount >
struct SelectMethodPointerType {};
// Case 0
template<class TInstance, class TReturn, class TArg1, class TArg2, class TArg3, Bool isConst >
struct SelectMethodPointerType<TInstance, TReturn, TArg1, TArg2, TArg3, isConst, 0>
{
	// If is const
	template< Bool isConst >
	struct IsConstSwitch 
	{ typedef TReturn (TInstance::*Value)() const; };
	// else
	template<>
	struct IsConstSwitch< FALSE > 
	{ typedef TReturn (TInstance::*Value)() ; };

	typedef typename IsConstSwitch< isConst >::Value Value;
};
// Case 1
template<class TInstance, class TReturn, class TArg1, class TArg2, class TArg3, Bool isConst >
struct SelectMethodPointerType<TInstance, TReturn, TArg1, TArg2, TArg3, isConst, 1>
{
	// If is const
	template< Bool isConst >
	struct IsConstSwitch 
	{ typedef TReturn (TInstance::*Value)( TArg1 ) const; };
	// else
	template<>
	struct IsConstSwitch< FALSE > 
	{ typedef TReturn (TInstance::*Value)( TArg1 ) ; };

	typedef typename IsConstSwitch< isConst >::Value Value;
};
// Case 2
template<class TInstance, class TReturn, class TArg1, class TArg2, class TArg3, Bool isConst >
struct SelectMethodPointerType<TInstance, TReturn, TArg1, TArg2, TArg3, isConst, 2>
{
	// If is const
	template< Bool isConst >
	struct IsConstSwitch 
	{ typedef TReturn (TInstance::*Value)( TArg1, TArg2 ) const; };
	// else
	template<>
	struct IsConstSwitch< FALSE > 
	{ typedef TReturn (TInstance::*Value)( TArg1, TArg2 ) ; };

	typedef typename IsConstSwitch< isConst >::Value Value;
};

// Case 3
template<class TInstance, class TReturn, class TArg1, class TArg2, class TArg3, Bool isConst >
struct SelectMethodPointerType<TInstance, TReturn, TArg1, TArg2, TArg3, isConst, 3>
{
	// If is const
	template< Bool isConst >
	struct IsConstSwitch 
	{ typedef TReturn (TInstance::*Value)( TArg1, TArg2, TArg3 ) const; };
	// else
	template<>
	struct IsConstSwitch< FALSE > 
	{ typedef TReturn (TInstance::*Value)( TArg1, TArg2, TArg3  ) ; };

	typedef typename IsConstSwitch< isConst >::Value Value;
};

// Select the right SelectMethodPointerType depending upon the number of valid args
template< class TInstance, class TReturn, class TArg1, class TArg2, class TArg3, Bool isConst >
struct MethodPointerType
{
	typedef typename SelectMethodPointerType< TInstance, TReturn, TArg1, TArg2, TArg3, isConst, GetValidArgCount< TArg1, TArg2, TArg3 >::Value >::Value Value;
};

// Implement the right code for the call function based upon the number of arguments and the return value
template< class TInstance, class TReturn, class TArg1, class TArg2, class TArg3, Bool isConst, int argCount  >
struct CallFunction{};

//
// 0 Args call
//

// 0 args with return value
template < class TInstance, class TReturn, class TArg1, class TArg2, class TArg3, Bool isConst >
struct CallFunction<TInstance, TReturn, TArg1, TArg2, TArg3, isConst, 0>
{
	typedef typename MethodPointerType< TInstance, TReturn, TArg1, TArg2, TArg3, isConst>::Value TMethodType;

	static Void Call( lua_State* L, TMethodType method)
	{
		Bool success = FALSE;
		// Extract this pointer		
		CArgDescriptor<TInstance>::PopReturnType thisPointer = CArgDescriptor<TInstance>::PopValue( L, success );

		// Call function
		TReturn returnValue = (thisPointer.*(method))( );

		// Push return value
		CArgDescriptor<TReturn>::PushValue( L, returnValue );
	}
};

// 0 args without return value
template < class TInstance, class TArg1, class TArg2, class TArg3, Bool isConst >
struct CallFunction<TInstance, Void, TArg1, TArg2, TArg3, isConst, 0>
{
	typedef typename MethodPointerType< TInstance, Void, TArg1, TArg2, TArg3, isConst>::Value TMethodType;

	static Void Call( lua_State* L, TMethodType method)
	{
		Bool success = FALSE;
		// Extract this pointer
		CArgDescriptor<TInstance>::PopReturnType thisPointer = CArgDescriptor<TInstance>::PopValue( L, success );

		// Call function
		(thisPointer.*(method))( );
	}
};

//
// 1 Args call
//

// 1 arg with return value
template < class TInstance, class TReturn, class TArg1, class TArg2, class TArg3, Bool isConst >
struct CallFunction<TInstance, TReturn, TArg1, TArg2, TArg3, isConst, 1>
{
	typedef typename MethodPointerType< TInstance, TReturn, TArg1, TArg2, TArg3, isConst>::Value TMethodType;

	static Void Call( lua_State* L, TMethodType method)
	{
		Bool success = FALSE;
		// Extract arg 1
		CArgDescriptor<TArg1>::PopReturnType arg1Value = CArgDescriptor<TArg1>::PopValue( L, success );

		// Extract this pointer
		CArgDescriptor<TInstance>::PopReturnType thisPointer = CArgDescriptor<TInstance>::PopValue( L, success );

		// Call function
		TReturn returnValue = (thisPointer.*(method))( arg1Value );

		// Push return value
		CArgDescriptor<TReturn>::PushValue( L, returnValue );
	}
};

// 1 arg without return value
template < class TInstance, class TArg1, class TArg2, class TArg3, Bool isConst >
struct CallFunction<TInstance, Void, TArg1, TArg2, TArg3, isConst, 1>
{
	typedef typename MethodPointerType< TInstance, Void, TArg1, TArg2, TArg3, isConst>::Value TMethodType;

	static Void Call( lua_State* L, TMethodType method)
	{
		Bool success = FALSE;
		// Extract arg 1
		CArgDescriptor<TArg1>::PopReturnType arg1Value = CArgDescriptor<TArg1>::PopValue( L, success );
		
		// Extract this pointer
		CArgDescriptor<TInstance>::PopReturnType thisPointer = CArgDescriptor<TInstance>::PopValue( L, success );

		// Call function
		(thisPointer.*(method)) ( arg1Value );
	}
};

//
// 2 Args call
//

// 2 arg with return value
template < class TInstance, class TReturn, class TArg1, class TArg2, class TArg3, Bool isConst >
struct CallFunction<TInstance, TReturn, TArg1, TArg2, TArg3, isConst, 2>
{
	typedef typename MethodPointerType< TInstance, TReturn, TArg1, TArg2, TArg3, isConst>::Value TMethodType;

	static Void Call( lua_State* L, TMethodType method)
	{
		Bool success = FALSE;
		// Extract arg 2
		CArgDescriptor<TArg2>::PopReturnType arg2Value = CArgDescriptor<TArg2>::PopValue( L, success );
		// Extract arg 1
		CArgDescriptor<TArg1>::PopReturnType arg1Value = CArgDescriptor<TArg1>::PopValue( L, success );

		// Extract this pointer
		CArgDescriptor<TInstance>::PopReturnType thisPointer = CArgDescriptor<TInstance>::PopValue( L, success );

		// Call function
		TReturn returnValue = (thisPointer.*(method))( arg1Value, arg2Value );

		// Push return value
		CArgDescriptor<TReturn>::PushValue( L, returnValue );
	}
};

// 2 arg without return value
template < class TInstance, class TArg1, class TArg2, class TArg3, Bool isConst >
struct CallFunction<TInstance, Void, TArg1, TArg2, TArg3, isConst, 2>
{
	typedef typename MethodPointerType< TInstance, Void, TArg1, TArg2, TArg3, isConst>::Value TMethodType;

	static Void Call( lua_State* L, TMethodType method)
	{
		Bool success = FALSE;
		// Extract arg 2
		CArgDescriptor<TArg2>::PopReturnType arg2Value = CArgDescriptor<TArg2>::PopValue( L, success );
		// Extract arg 1
		CArgDescriptor<TArg1>::PopReturnType arg1Value = CArgDescriptor<TArg1>::PopValue( L, success );

		// Extract this pointer
		CArgDescriptor<TInstance>::PopReturnType thisPointer = CArgDescriptor<TInstance>::PopValue( L, success );
		DebugAssert(thisPointer);

		// Call function
		(thisPointer.*(method)) ( arg1Value, arg2Value );
	}
};

//
// 3 Args call
//

// 3 arg with return value
template < class TInstance, class TReturn, class TArg1, class TArg2, class TArg3, Bool isConst >
struct CallFunction<TInstance, TReturn, TArg1, TArg2, TArg3, isConst, 3>
{
	typedef typename MethodPointerType< TInstance, TReturn, TArg1, TArg2, TArg3, isConst>::Value TMethodType;

	static Void Call( lua_State* L, TMethodType method)
	{
		Bool success = FALSE;
		// Extract arg 3
		CArgDescriptor<TArg3>::PopReturnType arg3Value = CArgDescriptor<TArg3>::PopValue( L, success );
		// Extract arg 2
		CArgDescriptor<TArg2>::PopReturnType arg2Value = CArgDescriptor<TArg2>::PopValue( L, success );
		// Extract arg 1
		CArgDescriptor<TArg1>::PopReturnType arg1Value = CArgDescriptor<TArg1>::PopValue( L, success );

		// Extract this pointer
		CArgDescriptor<TInstance>::PopReturnType thisPointer = CArgDescriptor<TInstance>::PopValue( L, success );

		// Call function
		TReturn returnValue = (thisPointer.*(method))( arg1Value, arg2Value, arg3Value );

		// Push return value
		CArgDescriptor<TReturn>::PushValue( L, returnValue );
	}
};

// 3 arg without return value
template < class TInstance, class TArg1, class TArg2, class TArg3, Bool isConst >
struct CallFunction<TInstance, Void, TArg1, TArg2, TArg3, isConst, 3>
{
	typedef typename MethodPointerType< TInstance, Void, TArg1, TArg2, TArg3, isConst>::Value TMethodType;

	static Void Call( lua_State* L, TMethodType method)
	{
		Bool success = FALSE;
		// Extract arg 3
		CArgDescriptor<TArg3>::PopReturnType arg3Value = CArgDescriptor<TArg3>::PopValue( L, success );
		// Extract arg 2
		CArgDescriptor<TArg2>::PopReturnType arg2Value = CArgDescriptor<TArg2>::PopValue( L, success );
		// Extract arg 1
		CArgDescriptor<TArg1>::PopReturnType arg1Value = CArgDescriptor<TArg1>::PopValue( L, success );

		// Extract this pointer
		CArgDescriptor<TInstance>::PopReturnType thisPointer = CArgDescriptor<TInstance>::PopValue( L, success );

		// Call function
		(thisPointer.*(method)) ( arg1Value, arg2Value, arg3Value );
	}
};

class CMethodDescriptorBase
{
public:
	virtual Void Register( lua_State* L, int methodTableIndex  ) = 0;

	CMethodDescriptorBase* Next;
};

// End user class used to represent method descriptor
template < class TInstance, class TReturn, class TArg1, class TArg2, class TArg3, Bool isConst >
class CMethodDescriptor : public CMethodDescriptorBase
{

public:

	typedef typename MethodPointerType< TInstance, TReturn, TArg1, TArg2, TArg3, isConst>::Value TMethodType;
	TMethodType Method;
	String Name;

	CMethodDescriptor( CMethodDescriptorBase** methodList, String name, TMethodType method )
	{
		Next = NULL;
		Method = method;
		Name = name;

		if( *methodList == NULL )
		{
			*methodList = this;
		}
		else
		{
			Next = *methodList;
			*methodList = this;
		}
	}

	Void Register( lua_State* L, int methodTableIndex  )
	{
		// Register new method
		lua_pushstring(L, Name );
		lua_pushlightuserdata(L, (void*) this );
		lua_pushcclosure(L, Call, 1);
		// methodTableIndex[ name ] = Thunk
		lua_settable(L, methodTableIndex );
	}

	static int Call( lua_State* L )
	{
		// Get Method descriptor from upvalue
		CMethodDescriptor<TInstance, TReturn, TArg1, TArg2, TArg3, isConst>* methodDesc = (CMethodDescriptor<TInstance, TReturn, TArg1, TArg2, TArg3, isConst>*) lua_touserdata(L, lua_upvalueindex(1));
		DebugAssert( methodDesc );

		CallFunction<TInstance, TReturn, TArg1, TArg2, TArg3, isConst, GetValidArgCount< TArg1, TArg2, TArg3 >::Value>::Call( L, methodDesc->Method );

		return 0;
	}
};

}

#endif
