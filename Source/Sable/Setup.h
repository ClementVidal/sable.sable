#ifndef _SABLE_SETUP_
#define _SABLE_SETUP_

// "Forward declare" sable namespace
namespace Sable
{

}

/**
*/

/**
Platform setup PC
*/
#if defined( SETUP_IMPLTYPE_MSW )

    #ifndef SETUP_TARGET_DUNE
        #define SETUP_OPENAL
    #else
        #define SETUP_USE_EXCEPTION
    #endif
	#define SETUP_USE_PROF

#endif

/**
Flags
*/
#define SETUP_MEMORY_TRACKER // Memory track
#define SETUP_POLYMORPHIC_CAST_VALIDATION //RTTI features

/**
Constant from compiler specific macro
*/
#ifdef UNICODE
    #define SETUP_UNICODE
#endif

#ifdef _WCHAR_T_DEFINED
	#define SETUP_WCHAR_DEFINED
#endif	

/**
Global constant
*/
#define CONSTANT_MAX_RENDERENTRY_COUNT 2048

/**
Internal setup validation
*/
#ifndef SETUP_CONFIG_DEBUG
	#undef SETUP_MEMORY_TRACKER
#endif

#if defined( SETUP_IMPLTYPE_MSW )
    #define Inline  __inline  
#else
	#define Inline  inline
#endif


#endif

