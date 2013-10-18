#ifndef _SABLE_CORE_MEMORY_HEAP_
#define _SABLE_CORE_MEMORY_HEAP_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/String/StaticString.h>

namespace Sable
{

/**  
\ingroup CoreMemory
Memory heap
*/
class CMemoryHeap 
{

public:

	/** @name DataTypes*/
	//@{
	enum EType
	{
		nType_SystemHeap = 0,
		nType_FreeListHeap,
		nType_BuddyHeap,
		nType_StackHeap,
		nType_MallocHeap,
		nType_Count,
		nType_None = -1
	};
	//@}

    /** @name Constructor/Destructor*/
    //@{
    CMemoryHeap( String name );
    virtual ~CMemoryHeap();
    //@}

    /** @name Operator*/
    //@{
    //@}
    
    /** @name Accessors*/
    //@{
	String				GetName() const;
	virtual EType		GetType() const = 0;
	SysSize				GetAllocationMinSize() const;
	SysSize				GetAllocationMaxSize() const;
    SysSize             GetAllocatedBytes() const;
	SysSize				GetReservedBytes() const;
    //@}
    
    /** @name Manipulator*/
    //@{
	Void			DumpAlloc();
	virtual Void	LogInfo() const;
    virtual Void*   Allocate( SysSize size ) = 0;
    virtual Void    Free( Void* address ) = 0;
    virtual Void*   DebugAllocate( SysSize size, const Char* file, UInt32 line ) ;
    virtual Void    DebugFree( Void* address ) ;
    //@}

protected:

    // Method
	UInt32		GetHeaderSize() const;
	Void		OnAllocate( SysSize s );
	Void		OnFree( SysSize s );

    // Attribute
    Void*				m_BaseAddress;
    SysSize				m_ReservedSize;
	CStringIdentifier	m_Name;
	UInt8				m_Align;

private:

	// DataTypes
	struct SAlloc
	{
		SysSize Size;
		UInt32	Line;
		Char	File[64];

		SAlloc* NextTrack;
		SAlloc* PreviousTrack;
	};


	// Function
	Void		AddTrack( Void* adress, SysSize size, const Char* file, UInt32 line );
	UInt32		RemoveTrack( Void* adress );

    // Attributes
	SAlloc*			m_AllocList;
	SysSize			m_AllocatedBytes;
	SysSize			m_AllocMaxSize;
	SysSize			m_AllocMinSize;

};  

}

#endif
