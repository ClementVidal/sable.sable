#include <Sable\Core\Debug\ProfView.h>

using namespace Sable;

#define PROFVIEW_FRAMEDELAY 10

CDebugProfView::SHistoryStep::SHistoryStep()
{
	SelectionMark = 0;
}

CDebugProfView::CDebugProfView()
{
	m_Buffer.SetItemCount( 1024 * 10 );

    m_CurrentNode = CoreManager.GetDebugProf().GetRootNode();
	m_SelectionMark = 0;
	m_NavigationHistory.SetCapacity( 64 );
	m_Buffer[0] = 0;
}

CDebugProfView::~CDebugProfView()
{

}

String CDebugProfView::GetBuffer() const
{
	return m_Buffer.GetBuffer();
}

Void CDebugProfView::MoveUp()
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

Void CDebugProfView::MoveDown()
{
	if( m_EntryCount > 0 )
		m_SelectionMark = ( m_SelectionMark + 1 ) % m_EntryCount;
	else
		m_SelectionMark = 0;
}

Void CDebugProfView::MoveForward()
{
	if( m_NavigationHistory.GetItemCount() < m_NavigationHistory.GetCapacity() )
	{		
		SHistoryStep h;
		h.Node = m_CurrentNode;
		h.SelectionMark = m_SelectionMark;

		// Descend d'un niveau dans les enfants
        m_CurrentNode = m_CurrentNode->GetChild( m_SelectionMark );
		if( m_CurrentNode )
		{
			m_NavigationHistory.PushItem( h );
			Sample( );
			m_SelectionMark = 0;
		}
		else
		{
			m_CurrentNode = h.Node;
		}
	}
}

Void CDebugProfView::MoveBackward()
{
	if( m_NavigationHistory.GetItemCount() )
	{
		SHistoryStep& h = m_NavigationHistory.GetTopItem();
		m_CurrentNode = h.Node;
		m_SelectionMark = h.SelectionMark;

		m_NavigationHistory.PopItem( );
		Sample( );
	}
}

Void CDebugProfView::Sample( )
{
	CoreManager.GetDebugProf().Reset();
	CoreManager.GetDebugProf().EnableSampling( TRUE );
}

Void CDebugProfView::Update()
{
	if( CoreManager.GetDebugProf().GetSampledFrameCount() >= PROFVIEW_FRAMEDELAY )
	{
		CoreManager.GetDebugProf().EnableSampling( FALSE );
	}
	Format( );
}

Void CDebugProfView::Format( )
{
	DebugProfile( "CDebugProfView::Format" );
	
	String parentName;

#ifndef SETUP_USE_PROF
	m_Buffer[0] = 0;
	return ;
#endif

	Char* buffer = m_Buffer.GetBuffer();
	Int32 s = m_Buffer.GetItemCount();
	Int32 off;
	UInt32 frameCount = CoreManager.GetDebugProf().GetSampledFrameCount();

	parentName = m_CurrentNode->GetName();

	off = StringSetFormattedText( buffer, s,"| Profiling Data | Depth Level: %d    \n" \
											"| Parent: %s \n" \
											"-----------------------------------------------------\n", 
											m_NavigationHistory.GetItemCount(), parentName );
	buffer += off;

	Float32 selfTotalTime = 0.0f;
	Float32 parentTotalTime = 0.0f;

	if( frameCount >= PROFVIEW_FRAMEDELAY )
	{
        CProfileNode* childNode = NULL;

		parentTotalTime = m_CurrentNode->GetTotalSamplingTime() / (Float32) frameCount; 
	
		m_EntryCount = 0;

		Float32 time;
		Int32 percent;

        childNode = m_CurrentNode->GetChild();
		while( childNode )
		{
			time = childNode->GetTotalSamplingTime();
			time = time / (Float32) frameCount; 

			selfTotalTime += time;
			childNode = childNode->GetSibling();
		}

		childNode = m_CurrentNode->GetChild();
		while( childNode )
		{
			time = childNode->GetTotalSamplingTime()/ (Float32) frameCount;
			if( parentTotalTime > 0.0f )
				percent = ( Int32 ) ( time / parentTotalTime * 100.0f );
			else
				percent = 0;

			if( m_EntryCount != m_SelectionMark )
				off = StringSetFormattedText( buffer, s, "|  %s : %.5f ms %d %%\n", childNode->GetName(), time * 1000.0f, percent );
			else
				off = StringSetFormattedText( buffer, s, "|>> %s : %.5f ms %d %%\n", childNode->GetName(), time * 1000.0f, percent );

			buffer += off;

			m_EntryCount++;
			childNode = childNode->GetSibling();
		}
	}
	else
	{
		off = StringSetFormattedText( buffer, s, "Sampling...\n");
		buffer += off;
	}

	Float32 totalTime = parentTotalTime;
	Float32 profiledTime = selfTotalTime;
	Float32 unProfiledTime = parentTotalTime - selfTotalTime;
	if( unProfiledTime < 0 )
		unProfiledTime = 0;

	off = StringSetFormattedText( buffer, s, "-----------------------------------------------------\n");
	buffer += off;
	off = StringSetFormattedText( buffer, s, "| Total time: %.5f ms \n", totalTime * 1000.0f );
	buffer += off;
	off = StringSetFormattedText( buffer, s, "| Profiled time: %.5f ms \n", profiledTime * 1000.0f );
	buffer += off;
	off = StringSetFormattedText( buffer, s, "| UnProfiled time: %.5f ms \n", unProfiledTime * 1000.0f );
	buffer += off;

}