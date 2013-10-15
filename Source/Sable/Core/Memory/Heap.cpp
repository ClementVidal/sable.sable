#include <Sable\Core\Memory\Heap.h>

#include <Sable\Core\Memory\Primitives.h>

using namespace Sable;

CMemoryHeap::CMemoryHeap( String name )
{
	m_Align = 0;
	m_Name = name;
    m_BaseAddress = NULL;
    m_AllocList = NULL;
	m_AllocatedBytes = 0;
	m_AllocMaxSize = 0;
	m_AllocMinSize = 0;
	m_AllocList = NULL;
	m_ReservedSize = 0;
	CoreManager.GetMemoryManager().RegisterHeap( *this );
}

CMemoryHeap::~CMemoryHeap()
{
	m_Align = 0;
	m_Name = NULL;
	m_BaseAddress = NULL;
	m_AllocList = NULL;
	m_AllocatedBytes = 0;
	m_AllocMaxSize = 0;
	m_AllocMinSize = 0;
	m_AllocList = NULL;
	m_ReservedSize = 0;
	CoreManager.GetMemoryManager().UnRegisterHeap( *this );
}

SysSize CMemoryHeap::GetReservedBytes() const
{
	return m_ReservedSize;
}

SysSize CMemoryHeap::GetAllocatedBytes() const
{
    return m_AllocatedBytes;
}

SysSize	CMemoryHeap::GetAllocationMinSize() const
{
	return m_AllocMinSize;
}

SysSize	CMemoryHeap::GetAllocationMaxSize() const
{
	return m_AllocMaxSize;
}

Void* CMemoryHeap::DebugAllocate( SysSize size, const Char* file, UInt32 line )
{
	Byte* data;

#ifdef SETUP_MEMORY_TRACKER
	data = (Byte*) Allocate( size + GetHeaderSize() );
	if( data )
	{
		AddTrack( data, size, file, line );
		data = data + GetHeaderSize();
	}
#else
	data = (Byte*) Allocate( size );
#endif

	DebugAssert( MemoryIsAddressAligned( data, m_Align ) );

    return data;
}

Void CMemoryHeap::DebugFree( Void* address )
{
	Byte* data = (Byte*)address;

	if( address == NULL )
		return;

#ifdef SETUP_MEMORY_TRACKER
	data = (Byte*)address;
	data = data - GetHeaderSize();

    RemoveTrack( data );
#endif

    Free( data );
}


UInt32	CMemoryHeap::GetHeaderSize() const
{
	return sizeof( SAlloc );
}

Void CMemoryHeap::AddTrack( Void* adress, SysSize size, const Char* file, UInt32 line )
{
	SAlloc *track, *tmptrack;

	track = (SAlloc*) adress;
	track->Size = size;
	track->NextTrack = NULL;
	track->PreviousTrack = NULL;
	track->Line = line;
	MemoryCopy(file, track->File, 64);

	tmptrack = m_AllocList;
	m_AllocList = track;
	track->NextTrack = tmptrack;
	if( tmptrack )
	{
		tmptrack->PreviousTrack = track;
	}
}

UInt32 CMemoryHeap::RemoveTrack( Void* adress )
{
	UInt32 size;
	SAlloc *track, *nexttrack, *previoustrack;

	if( adress == NULL )
		return 0;

	track = (SAlloc*) adress;

	size = (UInt32)track->Size;
	nexttrack = track->NextTrack;
	previoustrack = track->PreviousTrack;
	if( previoustrack )
	{
		previoustrack->NextTrack = nexttrack;
	}
	else
	{
		m_AllocList = nexttrack;
	}
	if( nexttrack )
	{
		nexttrack->PreviousTrack = previoustrack;
	}

	return size;
}

String CMemoryHeap::GetName() const
{
	return m_Name;
}

Void CMemoryHeap::OnAllocate( SysSize s )
{
	if( s > m_AllocMaxSize )
		m_AllocMaxSize = s;

	if( s < m_AllocMinSize )
		m_AllocMinSize =s;

	m_AllocatedBytes += s;
}

Void CMemoryHeap::OnFree( SysSize s )
{
	m_AllocatedBytes -= s;
}


Void CMemoryHeap::DumpAlloc()
{
	SAlloc* track;

	track = m_AllocList;

#if defined( SETUP_IMPLTYPE_MSW )

	if( track )
	{
		printf("|===========================================================|\n");
		printf("Memory Leak Dump\n");
		printf("|===========================================================|\n");
		while( track != NULL )
		{
			printf("\n---------------------------\n\nFile: %s\nLine: %d\nSize: %d\n", 
				track->File, track->Line, ( UInt32 ) track->Size );
			track = track->NextTrack;
		}
		printf("|===========================================================|\n");
	}
#endif
}


Void CMemoryHeap::LogInfo() const
{

	DebugLogInfo( "=================================" );
	DebugLogInfo( "CMemoryBuddyHeap::LogInfo" );
	DebugLogInfo( "---------------------------------");
#ifdef SETUP_MEMORY_TRACKER
	DebugLogInfo( "Reserved mem: %f ko/ %f mo", GetReservedBytes() / 1024.0f, GetReservedBytes() / 1024.0f / 1024.0f );
	DebugLogInfo( "Allocated mem: %f ko/ %f mo", GetAllocatedBytes() / 1024.0f, GetAllocatedBytes() / 1024.0f / 1024.0f );
#else
	DebugLogInfo( "Memory tracking disabled" );
#endif
	DebugLogInfo( "=================================" );

	

}
