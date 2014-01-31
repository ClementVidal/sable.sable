#include <Sable/Core/Memory/Impl/Linux/Manager.h>

#include <unistd.h>
#include <stdlib.h>

using namespace Sable;

CImplLinuxMemoryManager::CImplLinuxMemoryManager( CMemoryManager& publicImpl ) :
    CImplStubMemoryManager(publicImpl)
{
}

CImplLinuxMemoryManager::~CImplLinuxMemoryManager()
{
}

Void* CImplLinuxMemoryManager::AllocPages( SysSize size )
{
    size = MemoryGetAlignedSize( size, (UInt32)GetPageSize() );

    return malloc( size );
}

Bool CImplLinuxMemoryManager::FreePages( Void* pages )
{
    free( pages );
    return TRUE;
}

SysSize	CImplLinuxMemoryManager::GetPageSize() const
{
    long sz = sysconf(_SC_PAGESIZE);
    return (SysSize) sz;
}
