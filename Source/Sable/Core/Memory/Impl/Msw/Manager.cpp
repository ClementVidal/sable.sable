#include <Sable/Core/Memory/Impl/Msw/Manager.h>

using namespace Sable;

CImplMswMemoryManager::CImplMswMemoryManager( CMemoryManager& publicImpl ) :
    CImplStubMemoryManager(publicImpl)
{
}

CImplMswMemoryManager::~CImplMswMemoryManager()
{
}

Void* CImplMswMemoryManager::AllocPages( SysSize size )
{
	size = MemoryGetAlignedSize( size, (UInt32)GetPageSize() );

	return ::VirtualAlloc( NULL, size,  MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE );
}

Bool CImplMswMemoryManager::FreePages( Void* pages )
{
	return ::VirtualFree( pages, 0, MEM_RELEASE );
}

SysSize	CImplMswMemoryManager::GetPageSize() const
{
	SYSTEM_INFO si;
	::GetSystemInfo( &si );

	return si.dwPageSize;
}