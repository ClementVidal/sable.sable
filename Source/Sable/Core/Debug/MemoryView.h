#ifndef _SABLE_CORE_DEBUG_MEMORYVIEW_
#define _SABLE_CORE_DEBUG_MEMORYVIEW_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/Collection/Stack.h>
#include <Sable/Core/Collection/Array.h>
#include <Sable/Setup.h>

namespace Sable
{

/**
\ingroup CoreDebug
Display formated informations about current memory status
*/
class CDebugMemoryView 
{

public:

	/** @Name Constructor/Destructor*/
	//@{
	CDebugMemoryView();
	~CDebugMemoryView();
	//@}

	/** @Name Accessors*/
	//@{
	String	GetBuffer() const;
	//@}

	/** @Name Manipulator*/
	//@{
	Void	Update();
	Void	MoveUp();
	Void	MoveDown();
	Void	MoveForward();
	Void    MoveBackward();
	//@}

private:

	// DataType
	
	// Methods
	Void	Format( );
	Char*	FormatHeapList( Char* buffer, Int32 s );
	Char*	GetHeapTypeName( CMemoryHeap::EType t, Char* buffer, Int32 s );

	// Attributes
	CArray<Char>			m_Buffer;
	Int32					m_SelectionMark;
	Int32					m_EntryCount;
};


}

#endif
