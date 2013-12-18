#ifndef _SABLE_GAME_SCRIPT_METHODDESCRIPTOR_
#define _SABLE_GAME_SCRIPT_METHODDESCRIPTOR_

#include <Sable/Game/Script/ArgumentDescriptor.h>

namespace Sable
{

// Test if an argument is void or not
template< class Type >
struct CIsNotVoid 
{ enum { Value = 1 }; };

template<>
struct CIsNotVoid< Void >
{ enum { Value = 0 }; };

// Count the number of valid argument
template< class TArg1, class TArg2, class TArg3 >
struct CGetValidArgCount
{ enum { Value = CIsNotVoid<TArg1>::Value + CIsNotVoid<TArg2>::Value + CIsNotVoid<TArg3>::Value }; };


// Switch to take into account the number of valid args
// And test in each case if method is const or not
template< class TInstance, class TReturn, class TArg1, class TArg2, class TArg3, Bool isConst, int ArgCount >
struct CSelectMethodPointerType {};

// Case with 0 args

// Switch used to provide the right fonction pointer signature 
// If is const
template< class TInstance, class TReturn, Bool isConst >
struct CIsConstSwitch0
{ typedef TReturn (TInstance::*Value)() const; };
// else    
template < class TInstance, class TReturn>
struct CIsConstSwitch0< TInstance, TReturn, false > 
{ typedef TReturn (TInstance::*Value)(); };

template<class TInstance, class TReturn, class TArg1, class TArg2, class TArg3, Bool isConst >
struct CSelectMethodPointerType<TInstance, TReturn, TArg1, TArg2, TArg3, isConst, 0>
{
    typedef typename CIsConstSwitch0< TInstance, TReturn, isConst >::Value Value;
};
// Case with 1 arg

// Switch used to provide the right fonction pointer signature 
// If is const
template< class TInstance, class TReturn, class TArg1, Bool isConst >
struct CIsConstSwitch1
{ typedef TReturn (TInstance::*Value)( TArg1 ) const; };
// else    
template < class TInstance, class TReturn, class TArg1>
struct CIsConstSwitch1< TInstance, TReturn, TArg1, false > 
{ typedef TReturn (TInstance::*Value)( TArg1 ); };

template<class TInstance, class TReturn, class TArg1, class TArg2, class TArg3, Bool isConst >
struct CSelectMethodPointerType<TInstance, TReturn, TArg1, TArg2, TArg3, isConst, 1>
{
    typedef typename CIsConstSwitch1< TInstance, TReturn, TArg1, isConst >::Value Value;
};

// Case with 2 arg

// Switch used to provide the right fonction pointer signature 
// If is const
template< class TInstance, class TReturn, class TArg1, class TArg2, Bool isConst >
struct CIsConstSwitch2
{ typedef TReturn (TInstance::*Value)( TArg1, TArg2 ) const; };
// else    
template < class TInstance, class TReturn, class TArg1, class TArg2>
struct CIsConstSwitch2< TInstance, TReturn, TArg1, TArg2, false > 
{ typedef TReturn (TInstance::*Value)( TArg1, TArg2 ); };

template<class TInstance, class TReturn, class TArg1, class TArg2, class TArg3, Bool isConst >
struct CSelectMethodPointerType<TInstance, TReturn, TArg1, TArg2, TArg3, isConst, 2>
{
    typedef typename CIsConstSwitch2< TInstance, TReturn, TArg1, TArg2, isConst >::Value Value;
};

// Case with 3 args

// Switch used to provide the right fonction pointer signature 
// If is const
template< class TInstance, class TReturn, class TArg1, class TArg2, class TArg3, Bool isConst >
struct CIsConstSwitch3
{ typedef TReturn (TInstance::*Value)( TArg1, TArg2, TArg3 ) const; };
// else    
template < class TInstance, class TReturn, class TArg1, class TArg2, class TArg3>
struct CIsConstSwitch3< TInstance, TReturn, TArg1, TArg2, TArg3, false > 
{ typedef TReturn (TInstance::*Value)( TArg1, TArg2, TArg3 ); };

template<class TInstance, class TReturn, class TArg1, class TArg2, class TArg3, Bool isConst >
struct CSelectMethodPointerType<TInstance, TReturn, TArg1, TArg2, TArg3, isConst, 3>
{
    typedef typename CIsConstSwitch3< TInstance, TReturn, TArg1, TArg2, TArg3, isConst >::Value Value;
};

// Select the right CSelectMethodPointerType depending upon the number of valid args
template< class TInstance, class TReturn, class TArg1, class TArg2, class TArg3, Bool isConst >
struct CMethodPointerType
{
    typedef typename CSelectMethodPointerType< TInstance, TReturn, TArg1, TArg2, TArg3, isConst, CGetValidArgCount< TArg1, TArg2, TArg3 >::Value >::Value Value;
};

// Implement the right code for the call function based upon the number of arguments and the return value
template< class TInstanceCD, class TReturnCD, class TArg1CD, class TArg2CD, class TArg3CD, Bool isConst, int argCount, int hasReturnValue  >
struct CCallFunction{
};

//
// 0 Args call
//

// 0 args with return value
template < class TInstanceCD, class TReturnCD, class TArg1CD, class TArg2CD, class TArg3CD, Bool isConst >
struct CCallFunction<TInstanceCD, TReturnCD, TArg1CD, TArg2CD, TArg3CD, isConst, 0, 1>
{
    typedef typename TInstanceCD::Type TInstance;
    typedef typename TReturnCD::Type   TReturn;
    typedef typename TArg1CD::Type     TArg1;
    typedef typename TArg2CD::Type     TArg2;
    typedef typename TArg3CD::Type     TArg3;
    typedef typename CArgDescriptor<TInstanceCD>::PopReturnType TPopReturnType;
    typedef typename CMethodPointerType< TInstance, TReturn, TArg1, TArg2, TArg3, isConst>::Value TMethodType;
    
    static Void Call( lua_State* L, TMethodType method)
    {
        Bool success = FALSE;
        // Extract this pointer		
        TPopReturnType thisPointer = CArgDescriptor<TInstanceCD>::PopValue( L, success );
        
        // Call function
        TReturn returnValue = (thisPointer.*(method))( );
        
        // Push return value
        CArgDescriptor<TReturnCD>::PushValue( L, returnValue );
    }
};
    
// 0 args without return value
template < class TInstanceCD, class TReturnCD, class TArg1CD, class TArg2CD, class TArg3CD, Bool isConst >
struct CCallFunction<TInstanceCD, TReturnCD, TArg1CD, TArg2CD, TArg3CD, isConst, 0, 0>
{
    typedef typename TInstanceCD::Type TInstance;
    typedef typename TArg1CD::Type     TArg1;
    typedef typename TArg2CD::Type     TArg2;
    typedef typename TArg3CD::Type     TArg3;
    typedef typename CArgDescriptor<TInstanceCD>::PopReturnType TPopReturnType;
    typedef typename CMethodPointerType< TInstance, Void, TArg1, TArg2, TArg3, isConst>::Value TMethodType;
    
    static Void Call( lua_State* L, TMethodType method)
    {
        Bool success = FALSE;
        // Extract this pointer
        TPopReturnType thisPointer = CArgDescriptor<TInstanceCD>::PopValue( L, success );
        // Call function
        (thisPointer.*(method))( );
    }
};
     
//
// 1 Args call
//

// 1 arg with return value
template < class TInstanceCD, class TReturnCD, class TArg1CD, class TArg2CD, class TArg3CD, Bool isConst >
struct CCallFunction<TInstanceCD, TReturnCD, TArg1CD, TArg2CD, TArg3CD, isConst, 1, 1>
{
    typedef typename TInstanceCD::Type TInstance;
    typedef typename TReturnCD::Type   TReturn;
    typedef typename TArg1CD::Type     TArg1;
    typedef typename TArg2CD::Type     TArg2;
    typedef typename TArg3CD::Type     TArg3;
    typedef typename CArgDescriptor<TInstanceCD>::PopReturnType TPopReturnType;
    typedef typename CMethodPointerType< TInstance, TReturn, TArg1, TArg2, TArg3, isConst>::Value TMethodType;  
 
    static Void Call( lua_State* L, TMethodType method)
    {
        Bool success = FALSE;
        // Extract arg 1
        typename CArgDescriptor<TArg1CD>::PopReturnType arg1Value = CArgDescriptor<TArg1CD>::PopValue( L, success );
        
        // Extract this pointer
        TPopReturnType thisPointer = CArgDescriptor<TInstanceCD>::PopValue( L, success );
        
        // Call function
        TReturn returnValue = (thisPointer.*(method))( arg1Value );
        
        // Push return value
        CArgDescriptor<TReturnCD>::PushValue( L, returnValue );
    }
};
    
// 1 arg without return value
template < class TInstanceCD, class TReturnCD, class TArg1CD, class TArg2CD, class TArg3CD, Bool isConst >
struct CCallFunction<TInstanceCD, TReturnCD, TArg1CD, TArg2CD, TArg3CD, isConst, 1, 0>
{    
    typedef typename TInstanceCD::Type TInstance;
    typedef typename TArg1CD::Type     TArg1;
    typedef typename TArg2CD::Type     TArg2;
    typedef typename TArg3CD::Type     TArg3;
    typedef typename CArgDescriptor<TInstanceCD>::PopReturnType TPopReturnType;
    typedef typename CMethodPointerType< TInstance, Void, TArg1, TArg2, TArg3, isConst>::Value TMethodType;  

    static Void Call( lua_State* L, TMethodType method)
    {
        Bool success = FALSE;
        // Extract arg 1
        typename CArgDescriptor<TArg1CD>::PopReturnType arg1Value = CArgDescriptor<TArg1CD>::PopValue( L, success );
	
        // Extract this pointer
        TPopReturnType thisPointer = CArgDescriptor<TInstanceCD>::PopValue( L, success );
        
        // Call function
        (thisPointer.*(method)) ( arg1Value );
    }
};
    
//
// 2 Args call
//

// 2 arg with return value
template < class TInstanceCD, class TReturnCD, class TArg1CD, class TArg2CD, class TArg3CD, Bool isConst >
struct CCallFunction<TInstanceCD, TReturnCD, TArg1CD, TArg2CD, TArg3CD, isConst, 2, 1>
{
    typedef typename TInstanceCD::Type TInstance;
    typedef typename TReturnCD::Type   TReturn;
    typedef typename TArg1CD::Type     TArg1;
    typedef typename TArg2CD::Type     TArg2;
    typedef typename TArg3CD::Type     TArg3;
    typedef typename CArgDescriptor<TInstanceCD>::PopReturnType TPopReturnType;
    typedef typename CMethodPointerType< TInstance, TReturn, TArg1, TArg2, TArg3, isConst>::Value TMethodType;  

    static Void Call( lua_State* L, TMethodType method)
    {
        Bool success = FALSE;
        // Extract arg 2
        typename CArgDescriptor<TArg2CD>::PopReturnType arg2Value = CArgDescriptor<TArg2CD>::PopValue( L, success );
        // Extract arg 1
        typename CArgDescriptor<TArg1CD>::PopReturnType arg1Value = CArgDescriptor<TArg1CD>::PopValue( L, success );
        
        // Extract this pointer
        TPopReturnType thisPointer = CArgDescriptor<TInstanceCD>::PopValue( L, success );
        
        // Call function
        TReturn returnValue = (thisPointer.*(method))( arg1Value, arg2Value );
        
        // Push return value
        CArgDescriptor<TReturnCD>::PushValue( L, returnValue );
    }
};

// 2 arg without return value
template < class TInstanceCD, class TReturnCD, class TArg1CD, class TArg2CD, class TArg3CD, Bool isConst >
struct CCallFunction<TInstanceCD, TReturnCD, TArg1CD, TArg2CD, TArg3CD, isConst, 2, 0>
{
    typedef typename TInstanceCD::Type TInstance;
    typedef typename TArg1CD::Type     TArg1;
    typedef typename TArg2CD::Type     TArg2;
    typedef typename TArg3CD::Type     TArg3;
    typedef typename CArgDescriptor<TInstanceCD>::PopReturnType TPopReturnType;
    typedef typename CMethodPointerType< TInstance, Void, TArg1, TArg2, TArg3, isConst>::Value TMethodType;  

    static Void Call( lua_State* L, TMethodType method)
    {
        Bool success = FALSE;
        // Extract arg 2
        typename CArgDescriptor<TArg2CD>::PopReturnType arg2Value = CArgDescriptor<TArg2CD>::PopValue( L, success );
        // Extract arg 1
        typename CArgDescriptor<TArg1CD>::PopReturnType arg1Value = CArgDescriptor<TArg1CD>::PopValue( L, success );
        
        // Extract this pointer
        TPopReturnType thisPointer = CArgDescriptor<TInstanceCD>::PopValue( L, success );
        DebugAssert(thisPointer);
        
        // Call function
        (thisPointer.*(method)) ( arg1Value, arg2Value );
    }
};

//
// 3 Args call
//

// 3 arg with return value
template < class TInstanceCD, class TReturnCD, class TArg1CD, class TArg2CD, class TArg3CD, Bool isConst >
struct CCallFunction<TInstanceCD, TReturnCD, TArg1CD, TArg2CD, TArg3CD, isConst, 3, 1>
{
    typedef typename TInstanceCD::Type TInstance;
    typedef typename TReturnCD::Type   TReturn;
    typedef typename TArg1CD::Type     TArg1;
    typedef typename TArg2CD::Type     TArg2;
    typedef typename TArg3CD::Type     TArg3;
    typedef typename CArgDescriptor<TInstanceCD>::PopReturnType TPopReturnType;
    typedef typename CMethodPointerType< TInstance, TReturn, TArg1, TArg2, TArg3, isConst>::Value TMethodType;  
    
    static Void Call( lua_State* L, TMethodType method)
    {
        Bool success = FALSE;
        // Extract arg 3
        typename CArgDescriptor<TArg3CD>::PopReturnType arg3Value = CArgDescriptor<TArg3CD>::PopValue( L, success );
        // Extract arg 2
        typename CArgDescriptor<TArg2CD>::PopReturnType arg2Value = CArgDescriptor<TArg2CD>::PopValue( L, success );
        // Extract arg 1
        typename CArgDescriptor<TArg1CD>::PopReturnType arg1Value = CArgDescriptor<TArg1CD>::PopValue( L, success );
        
        // Extract this pointer
        TPopReturnType thisPointer = CArgDescriptor<TInstanceCD>::PopValue( L, success );
        
        // Call function
        TReturn returnValue = (thisPointer.*(method))( arg1Value, arg2Value, arg3Value );
        
        // Push return value
        CArgDescriptor<TReturnCD>::PushValue( L, returnValue );
    }
};

// 3 arg without return value
template < class TInstanceCD, class TReturnCD, class TArg1CD, class TArg2CD, class TArg3CD, Bool isConst >
struct CCallFunction<TInstanceCD, TReturnCD, TArg1CD, TArg2CD, TArg3CD, isConst, 3, 0>
{
    typedef typename TInstanceCD::Type TInstance;
    typedef typename TArg1CD::Type     TArg1;
    typedef typename TArg2CD::Type     TArg2;
    typedef typename TArg3CD::Type     TArg3;
    typedef typename CArgDescriptor<TInstanceCD>::PopReturnType TPopReturnType;
    typedef typename CMethodPointerType< TInstance, Void, TArg1, TArg2, TArg3, isConst>::Value TMethodType;  
    
    static Void Call( lua_State* L, TMethodType method)
    {
        Bool success = FALSE;
        // Extract arg 3
        typename CArgDescriptor<TArg3CD>::PopReturnType arg3Value = CArgDescriptor<TArg3CD>::PopValue( L, success );
        // Extract arg 2
        typename CArgDescriptor<TArg2CD>::PopReturnType arg2Value = CArgDescriptor<TArg2CD>::PopValue( L, success );
        // Extract arg 1
        typename CArgDescriptor<TArg1CD>::PopReturnType arg1Value = CArgDescriptor<TArg1CD>::PopValue( L, success );
        
        // Extract this pointer
        TPopReturnType thisPointer = CArgDescriptor<TInstanceCD>::PopValue( L, success );
        
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
template < class TInstanceCD, class TReturnCD, class TArg1CD, class TArg2CD, class TArg3CD, Bool isConst >
class CMethodDescriptor : public CMethodDescriptorBase
{

public:
    
    typedef typename TInstanceCD::Type TInstance;
    typedef typename TReturnCD::Type   TReturn;
    typedef typename TArg1CD::Type     TArg1;
    typedef typename TArg2CD::Type     TArg2;
    typedef typename TArg3CD::Type     TArg3;

    typedef typename CMethodPointerType< TInstance, TReturn, TArg1, TArg2, TArg3, isConst>::Value TMethodType;
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
        CMethodDescriptor<TInstanceCD, TReturnCD, TArg1CD, TArg2CD, TArg3CD, isConst>* methodDesc = (CMethodDescriptor<TInstanceCD, TReturnCD, TArg1CD, TArg2CD, TArg3CD, isConst>*) lua_touserdata(L, lua_upvalueindex(1));
        DebugAssert( methodDesc );

        typedef  CGetValidArgCount< TArg1, TArg2, TArg3 > ValidArgCount;
        typedef  CIsNotVoid< TReturn > IsNotVoid;

        CCallFunction<TInstanceCD, TReturnCD, TArg1CD, TArg2CD, TArg3CD, isConst, ValidArgCount::Value, IsNotVoid::Value >::Call( L, methodDesc->Method );
        
        return 0;
    }
};
    
}

#endif
