#ifndef _SABLE_CORE_DEBUG_PRIMITIVES_
#define _SABLE_CORE_DEBUG_PRIMITIVES_

#include <Sable\Setup.h>
#include <Sable\Core\Common\DataTypes.h>

/** 
\file Sable\Core\Debug\Primitives.h
Debug primitives
*/

#define NOP_INST	(Void)(0)

namespace Sable
{

	class CFilePath;

    // Internal usage should not be used directly
    Void DebugLogCodeInformation( String file, UInt32 line, String func );
    Void DebugLogInfo( String format, ... );
    Void DebugLogWarning( String format, ... );
    Void DebugLogError( String format, ... );

    Void DebugBreakExecution();
    Void DebugRaiseException();

    /**
    \ingroup CoreDebug
    Create an application dump file used to create a snapshot of the application state.
	\param dumpData Pointer to platform specific informations used to buil the dump
    */
    Void DebugCreateDump( Void* dumpData = NULL ) ;

    /**
    \ingroup CoreDebug
    Return the directory where application dump are created
    */
    String DebugGetDumpDirectory();
}


#ifdef SETUP_CONFIG_DEBUG

    /** 
    \ingroup CoreDebug
    \def DebugAssertMsg
    Assert a given condition, if assertion is false the following things are done:
        - Display a message using the logger
        - Create a crash dump file
        - Break execution
    */
    #define DebugAssertMsg(Exp, Msg)	\
        if( !(Exp) ) \
        { \
            Sable::DebugLogCodeInformation( __FILE__,__LINE__, __FUNCTION__ );\
            Sable::DebugLogInfo( "Assert: %s\n", #Exp ); \
            Sable::DebugLogInfo( Msg ); \
            Sable::DebugCreateDump( ); \
            Sable::DebugBreakExecution(); \
        } \

    /** 
    \ingroup CoreDebug
    \def DebugAssert
    Assert a given condition.
    */
	#define DebugAssert( Exp )	\
		DebugAssertMsg( Exp, "Runtime assertion" ) \

    /** 
    \ingroup CoreDebug
    \def DebugError
    Stop program exuction to signal an abnormal situation:
        - Display a message using the logger
        - Create a crash dump file
        - Break execution
    */
    #define DebugError(Msg) \
	    { \
        	Sable::DebugLogCodeInformation( __FILE__,__LINE__, __FUNCTION__ );\
        	Sable::DebugLogInfo( "Error:\n" ); \
            Sable::DebugLogInfo( #Msg ); \
            Sable::DebugCreateDump( ); \
            Sable::DebugBreakExecution(); \
        } \

#else

    /** 
    \ingroup CoreDebug
    \def DebugAssertMsg
    Assert a given condition, if assertion is false the following things are done:
        - Create a crash dump file
        - Break execution
    */
    #define DebugAssertMsg(Exp, Msg)	\
        if( !(Exp) ) \
        { \
        	Sable::DebugCreateDump( ); \
        	Sable::DebugRaiseException(); \
        } \

    /** 
    \ingroup CoreDebug
    \def DebugAssert
    Assert a given condition.
    */
	#define DebugAssert( Exp )	\
		DebugAssertMsg( Exp, "Runtime assertion" ) \

    /** 
    \ingroup CoreDebug
    \def DebugError
    Stop program exuction to signal an abnormal situation:
        - Create a crash dump file
        - Break execution
    */
    #define DebugError(Msg) \
		Sable::DebugCreateDump( ); \
		Sable::DebugRaiseException(); \

#endif


#endif
