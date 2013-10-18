#include <Sable/Core/Memory/Primitives.h>


using namespace Sable;

Void Sable::MemoryFill( Void* srcadress, Byte val, SysSize size )
{
    SysSize i;

    for( i=0; i<size; i++ ){
        ((Byte*)srcadress)[i] = val;
    }
}

Void* Sable::MemoryGetAlignedAddress( Void* a, UInt32 align )
{
    Address left = (SysSize)a % ( align  );
    Void* aligned = a;

    if( left )
        aligned = (Byte*)a + ( ( align ) - left ); 

    return aligned;
}

SysSize Sable::MemoryGetAlignedSize( SysSize a, UInt32 align )
{
	SysSize left = a % ( align );
	SysSize aligned = a;

	if( left )
		aligned = a + (  ( align ) - left );

	return aligned;
}

Bool Sable::MemoryIsAddressAligned( Void* a, UInt32 align )
{
	SysSize left = (SysSize) a % ( align );
	if( left )
		return FALSE;

	return TRUE;
}

Bool Sable::MemoryIsSizeAligned( SysSize a, UInt32 align )
{
	SysSize left = (SysSize) a % ( align );
	if( left )
		return FALSE;

	return TRUE;
}

Void Sable::MemoryCopy( const Void* srcAdress, Void* dstAdress, SysSize size )
{
    DebugAssertMsg( srcAdress && dstAdress, "Source or destination is NULL" );

#if defined( SETUP_IMPLTYPE_MSW )

	SysSize rest;
	SysSize toCopy;

	toCopy = size / 4;
	rest = size % 4;

	__asm{
		push ecx;
		push esi;
		push edi;		
		mov ecx, toCopy;
		mov esi, srcAdress;
		mov edi, dstAdress;
		rep movsd;

		mov ecx, rest;
		test ecx, ecx;
		jz _end

		rep movsb;

_end:
		pop edi;
		pop esi;
		pop ecx;
	}
#else

	SysSize i;
	for( i=0; i<size; i++ )
	{
		((Byte*)dstAdress)[i] = ((Byte*)srcAdress)[i];
	}

#endif 

}


/* Placement new.
Used by Pool collection in order to explicitly call the constructor of objects*/
Void * operator new( SysSize numBytes, Void* placementMemory, UInt32 dummyArgs )
{
    return (Void*) placementMemory;
}

Void operator delete( Void* data, Void* placementMemory, UInt32 dummyArgs )
{

}