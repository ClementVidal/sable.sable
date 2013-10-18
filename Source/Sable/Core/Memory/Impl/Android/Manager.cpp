#include <Sable/Core/Memory/Impl/Android/Manager.h>

#include <stdlib.h>
#include <unistd.h>

using namespace Sable;

CImplAndroidMemoryManager::CImplAndroidMemoryManager( CMemoryManager& publicImpl ) :
    CImplStubMemoryManager(publicImpl)
{
}

CImplAndroidMemoryManager::~CImplAndroidMemoryManager()
{
}

Void* CImplAndroidMemoryManager::AllocPages( SysSize size )
{
	size = MemoryGetAlignedSize( size, (UInt32)GetPageSize() );

	return ::malloc( size );
}

Bool CImplAndroidMemoryManager::FreePages( Void* pages )
{
	::free( pages );
	return TRUE;
}

SysSize	CImplAndroidMemoryManager::GetPageSize() const
{
	return ::getpagesize();
}
