#include <Sable/Core/Debug/MemoryView.h>

using namespace Sable;

CDebugMemoryView::CDebugMemoryView()
{
	m_Buffer.SetItemCount( 1024 * 10 );

	m_SelectionMark = 0;
	m_Buffer[0] = 0;
}

CDebugMemoryView::~CDebugMemoryView()
{

}

String CDebugMemoryView::GetBuffer() const
{
	return m_Buffer.GetBuffer();
}

Void CDebugMemoryView::MoveUp()
{
	if( m_EntryCount > 0 )
	{
		if( m_SelectionMark == 0 )
			m_SelectionMark = m_EntryCount-1;
		else
			m_SelectionMark = ( m_SelectionMark - 1 ) % m_EntryCount;
	}
	else
	{
		m_SelectionMark = 0;
	}
}

Void CDebugMemoryView::MoveDown()
{
	if( m_EntryCount > 0 )
		m_SelectionMark = ( m_SelectionMark + 1 ) % m_EntryCount;
	else
		m_SelectionMark = 0;
}

Void CDebugMemoryView::MoveForward()
{

}

Void CDebugMemoryView::MoveBackward()
{

}

Void CDebugMemoryView::Update()
{
	Format( );
}

Void CDebugMemoryView::Format( )
{
	DebugProfile( "CDebugMemoryView::Format" );

	Char* buffer = m_Buffer.GetBuffer();
	Int32 s = m_Buffer.GetItemCount();
	Int32 off;

	UInt32 pageSize = (UInt32) CoreManager.GetMemoryManager().GetPageSize();
	UInt32 allocatedPageCount = CoreManager.GetMemoryManager().GetAllocatedPageCount();

	off = StringSetFormattedText( buffer, s,
		"-----------------------------------------------------\n"
		"| Allocated pages : %d ( %.2f ko %.2f mo bytes )    \n" \
		"-----------------------------------------------------\n"
		"| Heap allocated memory : %.2f ko %.2f mo    \n" \
		"| Heap reserved memory: %.2f ko %.2f mo    \n" \
		"-----------------------------------------------------\n", 
		allocatedPageCount, allocatedPageCount * pageSize / 1024.0f, allocatedPageCount * pageSize / 1024.0f / 1024.0f,
		CoreManager.GetMemoryManager().GetAllocatedBytes() / 1024.0f, CoreManager.GetMemoryManager().GetAllocatedBytes() / 1024.0f / 1024.0f,
		CoreManager.GetMemoryManager().GetReservedBytes() / 1024.0f, CoreManager.GetMemoryManager().GetReservedBytes() / 1024.0f / 1024.0f );

	buffer += off;
	buffer = FormatHeapList( buffer, s );
	
}

Char* CDebugMemoryView::GetHeapTypeName( CMemoryHeap::EType t, Char* buffer, Int32 s )
{
	if( t == CMemoryHeap::nType_StackHeap )
	{
		StringCopy( "Stack Heap", buffer, s);
	}
	else 	if( t == CMemoryHeap::nType_FreeListHeap )
	{
		StringCopy( "FreeList Heap", buffer, s );
	}
	else 	if( t == CMemoryHeap::nType_SystemHeap )
	{
		StringCopy( "System Heap", buffer, s );
	}
	else 	if( t == CMemoryHeap::nType_BuddyHeap )
	{
		StringCopy( "Buddy Heap", buffer, s );
	}
	else 	if( t == CMemoryHeap::nType_MallocHeap )
	{
		StringCopy( "Malloc Heap", buffer, s );
	}
	else
	{
		StringCopy( "Unknown", buffer, s );
	}
	return buffer;
}

Char* CDebugMemoryView::FormatHeapList( Char* buffer, Int32 s )
{
	UInt32 i = 0;
	Char tmp[128];
	Int32 off;

	for(i=0;i<CoreManager.GetMemoryManager().GetHeapCount();i++)
	{
		CMemoryHeap& h = CoreManager.GetMemoryManager().GetHeapAtIndex( i );

		off = StringSetFormattedText( buffer, s,"| %s (%s) | Alloc: %.2f ko %.2f mo | Res: %.2f ko %.2f mo\n",
			GetHeapTypeName( h.GetType(), tmp, 128 ), h.GetName(),
			h.GetAllocatedBytes() / 1024.0f, h.GetAllocatedBytes() / 1024.0f / 1024.0f,
			h.GetReservedBytes() / 1024.0f, h.GetReservedBytes() / 1024.0f / 1024.0f
			);

		buffer += off;
	}

	return buffer;
}