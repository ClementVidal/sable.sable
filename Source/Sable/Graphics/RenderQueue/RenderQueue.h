#ifndef _SABLE_GRAPHICS_RENDER_RENDERQUEUE_
#define _SABLE_GRAPHICS_RENDER_RENDERQUEUE_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/String/String.h>
#include <Sable/Core/Collection/Array.h>
#include <Sable/Core/ManagedObject/ManagedObject.h>
#include <Sable/Graphics/RenderQueue/Entry.h>

namespace Sable
{

/** 
Render Queue.
*/
class CRenderQueue : public CManagedObject
{

	DEFINE_MANAGED_CLASS( CRenderQueue );

public:

	/** @name Constructor/Destructor*/
	//@{
	CRenderQueue();
	virtual ~CRenderQueue();
	//@}

	/** @name Operator*/
    //@{
    //@}

	/** @name Accessors*/
	//@{
	//@}
	
	/** @name Manipulator*/
    //@{
    Void                Execute( CRenderer& renderer, CRenderPass& rendererPass );
	Void                Reset();
	CRenderQueueEntry&  LockEntry();
	Void                UnlockEntry( );
	Void				UnInitialize();
    //@}

private:  

	// Types
	struct SEntry
	{
		SEntry();
		CRenderQueueEntry	Entry;

	};
	typedef CArray<SEntry> RenderQueueTable;

	// Method
	Void						SortEntry( Int32 l, Int32 r);
	Int32						SortPartition( Int32 l, Int32 r, Int32 pivotIndex );

	// Attributes
    RenderQueueTable			m_EntryTable;
    Int32                       m_EntryCount;
	Int32						m_CurrentEntry;

};

}

#endif
