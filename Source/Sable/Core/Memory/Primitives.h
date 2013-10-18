#ifndef _CORE_MEMORY_PRIMITIVES_
#define _CORE_MEMORY_PRIMITIVES_

#include <Sable/Core/Common/DataTypes.h>

/** 
\file Sable\Core\Memory\Primitives.h
Basic string primitives
*/

#ifdef SETUP_MEMORY_TRACKER

    /** 
    \ingroup CoreMemory
    \def MemoryAllocate
    Allocate memory from a given heap ( Debug version )
    */
    #define MemoryAllocate( a, size ) (a).DebugAllocate( size, __FILE__, __LINE__ )
    
    /** 
    \ingroup CoreMemory
    \def MemoryFree
    Free memory from a given heap ( Debug version )
    */
    #define MemoryFree( a, address ) (a).DebugFree( address )

#else

    /** 
    \ingroup CoreMemory
    \def MemoryAllocate
    Allocate memory from a given heap ( Release version )
    */
    #define MemoryAllocate( a, size ) (a).Allocate( size )

    /** 
    \ingroup CoreMemory
    \def MemoryFree
    Free memory from a given heap ( Release version )
    */
    #define MemoryFree( a, address ) (a).Free( address )

#endif

namespace Sable
{

/**
\ingroup CoreMemory
Align an address according to specific alignment given in bytes
*/
Void* MemoryGetAlignedAddress( Void* a, UInt32 align );

/**
\ingroup CoreMemory
Test if an address is aligned on a specific alignment given in bytes
*/
Bool MemoryIsAddressAligned( Void* a, UInt32 align );

/**
\ingroup CoreMemory
Test if a size is aligned on a specific alignment given in bytes
*/
Bool MemoryIsSizeAligned( SysSize a, UInt32 align );

/**
\ingroup CoreMemory
Align a size according to specific alignment given in bytes
*/
SysSize MemoryGetAlignedSize( SysSize a, UInt32 align );

/**
\ingroup CoreMemory
Fill a memory area with a specific values
*/
Void MemoryFill( Void* srcadress, Byte val, SysSize size );

/**
\ingroup CoreMemory
Copy memory from one place to an other
*/
Void MemoryCopy( const Void* srcadress, Void* dstadress, SysSize size );

}

/**
\ingroup CoreMemory
Placement new 
Used by Pool collection in order to explicitly call the constructor of objects
*/
Void *operator new( SysSize numBytes, Void* placementMemory, UInt32 dummyArgs );
Void operator delete( Void* data, Void* placementMemory, UInt32 dummyArgs );

/** 
\ingroup CoreMemory
\def ConstructObject

Construct a object starting at adresse addr by calling it's default ctr.

*/
#define ConstructObject( addr, type ) ( ::new ( (Byte*) addr, 0) type )
#define DestructObject( addr, type ) ( (addr)->~type() )

#endif
