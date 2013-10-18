#include <Sable/Core/Debug/ProfNode.h>

#include <Sable/Core/Debug/Prof.h>

using namespace Sable;

CProfileNode::CProfileNode( ) :
	m_Name( NULL ),
	m_TotalCalls( 0 ),
	m_TotalSamplingTime( 0 ),
	m_SamplingStart( 0 ),
	m_RecursionCounter( 0 ),
	m_Parent( NULL ),
	m_Child( NULL ),
	m_Sibling( NULL )
{
	Reset();
}


CProfileNode::~CProfileNode()
{
}

Float32 CProfileNode::GetTotalSamplingTime() const
{
	return (Float32) ( m_TotalSamplingTime ) / CoreManager.GetDebugProf().GetTicksFreq() ;
}

CProfileNode * CProfileNode::GetChild( UInt32 index )
{
    UInt32 i=0;
    CProfileNode * child = m_Child;
    while( child )
    {
        if( i == index )
            return child;
        i++;
        child = child->GetSibling();
    }

    return NULL;
}

CProfileNode* CProfileNode::AddChild( String name )
{ 
    CProfileNode * node = CoreManager.GetDebugProf().RequestNode( name, this );
    node->m_Sibling = m_Child;
    m_Child = node;
    return node;
}

CProfileNode* CProfileNode::GetChild( String name )
{
	CProfileNode * child = m_Child;
	while ( child ) 
	{
		if ( child->m_Name == name ) 
		{
			return child;
		}
		child = child->m_Sibling;
	}

    return NULL;
}


Void	CProfileNode::Reset()
{
	m_TotalCalls = 0;
	m_TotalSamplingTime = 0;
	m_RecursionCounter = 0;
	m_SamplingStart = 0;

    CProfileNode* tmp = m_Child;
	while( tmp ) 
	{
		tmp->Reset();
        tmp = tmp->GetSibling();
	}
    m_Child = NULL;
}

Void	CProfileNode::Call()
{
	m_TotalCalls++;
	if (m_RecursionCounter++ == 0) 
	{
		m_SamplingStart = CoreManager.GetDebugProf().GetTicks();
	}
}

Void CProfileNode::Initialize( String name, CProfileNode* parent  )
{
	m_Name = name;
	m_Parent = parent;
	m_TotalCalls = 0;
	m_TotalSamplingTime = 0;
	m_SamplingStart = 0;
	m_RecursionCounter = 0;
	m_Child = NULL;
	m_Sibling = NULL;
}

bool CProfileNode::Return()
{
	if ( --m_RecursionCounter == 0 && m_TotalCalls != 0 ) 
	{ 
		Int64 time;
		time = CoreManager.GetDebugProf().GetTicks();
		time-=m_SamplingStart;
		m_TotalSamplingTime += time;
	}

	return ( m_RecursionCounter == 0 );
}
