#include <Sable\Core\Memory\MallocHeap.h>

using namespace Sable;

CMemoryMallocHeap::CMemoryMallocHeap( String name ) :
    CMemoryHeap( name )
{
	m_Align = 0;
}

CMemoryMallocHeap::~CMemoryMallocHeap()
{
}

CMemoryHeap::EType CMemoryMallocHeap::GetType() const
{
	return nType_MallocHeap;
}

Void* CMemoryMallocHeap::Allocate( SysSize size )
{
	return ::new Byte[size];
}

Void CMemoryMallocHeap::Free( Void* object )
{
	if( object == NULL )
		return;

	::delete [] (Byte*) object;
}

