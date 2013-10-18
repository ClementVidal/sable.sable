#include <Sable/Core/Debug/Prof.h>

#define NODE_POOL_SIZE 2048

using namespace Sable;

CDebugProf::CDebugProf()
{
	m_FrameCount = 0;
	m_NodeCount = 0;
	m_NodePool.SetItemCount( NODE_POOL_SIZE );
	m_Root = RequestNode( "Root", NULL );
	m_ResetTime = 0;
	m_CurrentNode = m_Root;
	m_Timer.Start();
	m_States.Clear();
}

CDebugProf::~CDebugProf()
{

}

UInt32 CDebugProf::GetSampledFrameCount() const
{
	return m_FrameCount;
}

CProfileNode* CDebugProf::RequestNode( String name, CProfileNode* parent )
{
	if( m_NodeCount < NODE_POOL_SIZE )
	{
		CProfileNode* n = &m_NodePool[m_NodeCount++];
		n->Initialize( name, parent );
		
		return n;
	}
	return NULL;
}

Int64 CDebugProf::GetTicks()
{
	return m_Timer.GetElapsedTicks();
}

Int64 CDebugProf::GetTicksFreq()
{
	return m_Timer.GetTicksFreq();
}

Void CDebugProf::StartProfile( String name )
{
	Int64 pause;
	if( m_States.GetBit( nState_DoSampling ) )
	{
		CProfileNode* p = m_CurrentNode;
        DebugAssert( p );

		pause = m_Timer.GetElapsedTicks();

		if (name != m_CurrentNode->GetName()) 
		{
            CProfileNode* tmp = m_CurrentNode->GetChild( name );
            if( !tmp )
                tmp = m_CurrentNode->AddChild( name );
			m_CurrentNode = tmp;
		}

        // Evite de prendre en compte le temps de la recherche du noeud
		pause = m_Timer.GetElapsedTicks() - pause;
		p->m_TotalSamplingTime -= pause;

		m_CurrentNode->Call();
	}
}

Void	CDebugProf::StopProfile()
{
	if( m_States.GetBit( nState_DoSampling ) )
	{
		// Return will indicate whether we should back up to our parent (we may
		// be profiling a recursive function)
		if (m_CurrentNode->Return()) 
		{
			m_CurrentNode = m_CurrentNode->GetParent();
		}
	}
}

Void CDebugProf::StartFrame()
{
	if( m_States.GetBit( nState_AskEnableSampling ) )
	{
		m_States.SetBit( nState_AskEnableSampling, FALSE );
		m_States.SetBit( nState_AskDisableSampling, FALSE );
		m_States.SetBit( nState_DoSampling, TRUE );
	}
	else if( m_States.GetBit( nState_AskDisableSampling ) )
	{
		m_States.SetBit( nState_AskDisableSampling, FALSE );
		m_States.SetBit( nState_AskEnableSampling, FALSE );
		m_States.SetBit( nState_DoSampling, FALSE );
	}


	if( m_States.GetBit( nState_AskReset ) )
	{
		m_FrameCount = 0;
		m_Root->Reset(); 
		m_CurrentNode = m_Root;
		m_ResetTime = CoreManager.GetDebugProf().GetTicks();
		m_States.SetBit( nState_AskReset, FALSE );
	}

    if( m_States.GetBit( nState_DoSampling ) )
    {
        m_Root->Call();
    }
}

Void CDebugProf::EndFrame()
{
	if( m_States.GetBit( nState_DoSampling ) )
	{
        m_Root->Return();
		m_FrameCount++;
	}
}

CProfileNode* CDebugProf::GetRootNode() const
{
    return m_Root;
}

Void	CDebugProf::Reset()
{ 
	m_FrameCount = 0;
	m_States.SetBit( nState_AskReset, TRUE );
}

Float32 CDebugProf::GetTimeSinceReset()
{
	Int64 time;
	time = CoreManager.GetDebugProf().GetTicks();
	time -= m_ResetTime;
	return (Float32)time / CoreManager.GetDebugProf().GetTicksFreq();
}

CProfileSample::CProfileSample( String name )
{ 
	CoreManager.GetDebugProf().StartProfile( name ); 
}

CProfileSample::~CProfileSample()			
{ 
	CoreManager.GetDebugProf().StopProfile(); 
}

Void CDebugProf::EnableSampling( Bool onOff )
{
	if( onOff )
	{
		m_States.SetBit( nState_AskEnableSampling, TRUE );
		m_States.SetBit( nState_AskDisableSampling, FALSE );
	}
	else 
	{
		m_States.SetBit( nState_AskEnableSampling, FALSE );
		m_States.SetBit( nState_AskDisableSampling, TRUE );
	}
}