#include <Sable\Core\Memory\StackHeap.h>

using namespace Sable;

CMemoryStackHeap::CMemoryStackHeap( String name ) :
    CMemoryHeap( name )
{
	m_StackIndex = 0;
	m_Align = 0;
	m_ParentHeap = NULL;
	Reset();
}

CMemoryStackHeap::~CMemoryStackHeap()
{
	DumpAlloc();
	Reset( );
	FreeReservedMemory();
}

CMemoryHeap::EType CMemoryStackHeap::GetType() const
{
	return nType_StackHeap;
}

Void* CMemoryStackHeap::PushMarkerAndAllocate( SysSize size )
{
	PushMarker();
	return Allocate( size );
}

Void CMemoryStackHeap::PopMarkerAndFree( Void* object )
{
	Free( object );
	PopMarker();
}

Void CMemoryStackHeap::PushMarker()
{
	m_StackIndex++;
	DebugAssert( m_StackIndex < MEMORYSTACKHEAP_STACKSIZE );

	m_StackAlloc[m_StackIndex].Ptr = m_StackAlloc[m_StackIndex-1].Ptr + m_StackAlloc[m_StackIndex-1].Size;
	m_StackAlloc[m_StackIndex].Size = 0;
}

Void CMemoryStackHeap::PopMarker()
{
	DebugAssert( m_StackIndex > 0 );
	if(  m_StackAlloc[m_StackIndex].Size )
	{
		DumpAlloc();
		DebugAssert( m_StackAlloc[m_StackIndex].Size == 0 );
	}
	m_StackIndex --;
}

Void CMemoryStackHeap::FreeReservedMemory()
{
	DebugAssert( GetAllocatedBytes() == 0 );

	if( m_BaseAddress )
	{
		if( m_ParentHeap )
			MemoryFree( *m_ParentHeap, m_BaseAddress );
		else
			CoreManager.GetMemoryManager().FreePages( m_BaseAddress );

		m_BaseAddress = NULL;
	}
}

/**
Initialize all related variable and allocate the effective heap size
*/
Void CMemoryStackHeap::Initialize( CMemoryHeap* parent, SysSize maxSize, UInt8 align )
{
	FreeReservedMemory();
	Reset( );

	m_ParentHeap = parent;

    // Compute an aligned slot size
    m_ReservedSize = MemoryGetAlignedSize( maxSize, align );
    DebugAssert( m_ReservedSize >= maxSize );

	if( m_ParentHeap)
		m_BaseAddress = MemoryAllocate( *m_ParentHeap, m_ReservedSize + align ); 
	else
		m_BaseAddress = CoreManager.GetMemoryManager().AllocPages( m_ReservedSize + align );

    m_AlignedBaseAdress = (Byte*) MemoryGetAlignedAddress( m_BaseAddress, align );
    m_Align = align;

	m_StackIndex = 0;
	m_StackAlloc[m_StackIndex].Ptr = m_AlignedBaseAdress;
	m_StackAlloc[m_StackIndex].Size = 0;

#ifdef SETUP_CONFIG_DEBUG
	MemoryFill( m_BaseAddress, 0xcd, m_ReservedSize );
#endif

}

Void* CMemoryStackHeap::Allocate( SysSize size )
{
	DebugAssert( m_StackIndex > 0 );
	SysSize headerSize = MemoryGetAlignedSize( sizeof(SHeader), m_Align );

	SysSize alignedSize = MemoryGetAlignedSize( size, m_Align ) + headerSize;

    if( GetAllocatedBytes()+alignedSize < GetReservedBytes() )
    {
		SHeader* ptr = (SHeader*) (m_StackAlloc[m_StackIndex].Ptr + m_StackAlloc[m_StackIndex].Size );
        ptr->Size = (Int32)alignedSize;
		m_StackAlloc[m_StackIndex].Size += (Int32)alignedSize;
		CMemoryHeap::OnAllocate( (UInt32) ptr->Size );
		return ((Byte*) ptr) + headerSize;
    }

    DebugError( "Not enough memory in stack heap" );
    return NULL;
}

Void CMemoryStackHeap::Free( Void* object )
{
	Byte* ptr = (Byte*)object;
	ptr -= MemoryGetAlignedSize( sizeof( SHeader ), m_Align );
	SHeader* h = ((SHeader*)ptr);
	m_StackAlloc[m_StackIndex].Size -= h->Size;
	CMemoryHeap::OnFree( h->Size );
}

Void CMemoryStackHeap::Reset( )
{
#ifdef SETUP_CONFIG_DEBUG
	if( m_BaseAddress )
		MemoryFill( m_BaseAddress, 0xcd, m_ReservedSize );
#endif

	m_StackIndex = 0;
}
