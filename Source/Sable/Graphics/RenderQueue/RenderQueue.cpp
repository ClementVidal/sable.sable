#include <Sable/Graphics/RenderQueue/RenderQueue.h>

#include <Sable/Core/Collection/BitArray.h>
#include <Sable/Setup.h>
#include <Sable/Graphics/Geometry/Model.h>
#include <Sable/Graphics/Shader/Shader.h>
#include <Sable/Graphics/Node/Render.h>
#include <Sable/Graphics/Common/Manager.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1( Sable, CRenderQueue, CManagedObject );

CRenderQueue::SEntry::SEntry()
{
}

CRenderQueue::CRenderQueue()
{
	m_EntryTable.SetItemCount( CONSTANT_MAX_RENDERENTRY_COUNT );
	Reset();
}

CRenderQueue::~CRenderQueue()
{

}

CRenderQueueEntry& CRenderQueue::LockEntry()
{
	CRenderQueueEntry& entry = m_EntryTable[m_EntryCount].Entry;

	entry.Clear();

	return entry;
}

Void CRenderQueue::UnlockEntry()
{
	CRenderQueueEntry& entry = m_EntryTable[ m_EntryCount ].Entry;
   
	m_EntryCount++;
}

Void CRenderQueue::UnInitialize()
{
	m_EntryCount = 0;
	m_EntryTable.ClearAllItems();
}

Void CRenderQueue::Reset()
{
	m_EntryCount = 0;
    m_CurrentEntry = -1;
}

Int32 CRenderQueue::SortPartition( Int32 l, Int32 r, Int32 pivotIndex )
{    
	SEntry* arr = m_EntryTable.GetBuffer();

	Int32 storeIndex = l;

	// Store pivot at end of array
	m_EntryTable.SwapItems( pivotIndex, r );
	CRenderQueueEntry& pivotValue = arr[r].Entry;

	// Iterate all values execpt pivot at the right most side
	for( Int32 i=l;i<r;i++ )
	{
		if( arr[i].Entry < pivotValue )
		{
			m_EntryTable.SwapItems( i, storeIndex );
			storeIndex++;
		}
	}

	// Move pivot to it's final place
	m_EntryTable.SwapItems( storeIndex, r );

	return storeIndex;
}

/**
Sort entry by ascending order
*/
Void CRenderQueue::SortEntry( Int32 l, Int32 r)
{    
	if( l < r )
	{
		// l is chossen as the pivotIndex
		UInt32 pivotIndex = SortPartition( l, r, l );
		SortEntry( l, pivotIndex - 1 );
		SortEntry( pivotIndex + 1, r);
	}
}

Void CRenderQueue::Execute( CRenderer& renderer, CRenderPass& rendererPass ) 
{
	DebugProfile("CRenderQueue::Execute");

	SortEntry( 0,m_EntryCount-1 );

	// process all entry execpt the last one
	for(m_CurrentEntry = 0; m_CurrentEntry < m_EntryCount; m_CurrentEntry++)
	{
		DebugGraphicCommandGroup("CRenderQueue::Execute - Process Entry");
		CRenderQueueEntry& entry = m_EntryTable[m_CurrentEntry].Entry;

		if( entry.Activate( renderer ) )
		{
			entry.Render( renderer );
		}
	}	

 	Reset();
}
