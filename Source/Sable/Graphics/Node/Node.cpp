#include <Sable\Graphics\Node\Node.h>

#include <Sable\Core\Persistent\Archive.h>
#include <Sable\Graphics\Node\Spatial.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1( Sable, CNode, CManagedObject ) ;

CNode::CNode()
{
    m_Child = NULL;
    m_Sibling = NULL;
    m_Parent = NULL;
}

CNode::CNode( CNode& parent )
{
    m_Parent = NULL;
    m_Child = NULL;
    m_Sibling = NULL;
    SetParent( &parent );
}

CNode::~CNode()
{		
	if( m_Parent )
		SetParent( NULL );

    RemoveAllChilds();
}

/** 
Set the parent of this node.
Can be set to null to detach the node from the graph
*/
Void CNode::SetParent( CNode* pParent )
{
    if ( pParent != m_Parent )
    {
		// This temporary pointer is necessary to avoid the object to be destructed automaticaly if
		// This node is ONLY referenced by it's parent
		CRef<CNode> tmp = this;
        if( m_Parent )
        {
            CNode* parentTmp = m_Parent;
            m_Parent = NULL;
            parentTmp->RemoveChild( *this );
        }

        if( pParent )
        {
            m_Parent = pParent;
            pParent->AddChild( *this );
        }
    }
}

CNode* CNode::GetParent() const
{
    return m_Parent;
}

CNode* CNode::GetChild() const		
{
    return m_Child;
}

CNode* CNode::GetSibling() const
{
    return m_Sibling;
}

Void CNode::AddChild( CNode& childToAdd )
{
    childToAdd.m_Sibling = m_Child;
    m_Child = &childToAdd;
}

Void CNode::RemoveChild( CNode& childToRemove )
{
    CNode* child = m_Child;
    CNode* previous = NULL;
    while( child )
    {
        if( child == &childToRemove )
        {
			// Si le noeud à supprimer n'est pas en premiere position
            if( previous )
            {
                //une reference vers les sibling DOIT être maintenue de manière à ce qu'ils ne soient pas automatiquement détruit
                // quand le premier sibling est détruit
				CRef<CNode> tmpSibling = childToRemove.m_Sibling;
				childToRemove.m_Sibling = NULL;
                previous->m_Sibling = NULL; // Supprime le sibling
                previous->m_Sibling = tmpSibling; // Attache le nouveau sibling
			}
			// Si le noeud à supprimer est en premiere position
            else
            {
                //une reference vers les sibling DOIT être maintenue de manière à ce qu'ils ne soient pas automatiquement détruit
                // quand le premier sibling est détruit
                CRef<CNode> tmpSibling = childToRemove.m_Sibling;
				childToRemove.m_Sibling = NULL;
                m_Child = NULL; // Supprime le sibling
                m_Child = tmpSibling; // Attache le nouveau sibling
            }
            return;
        }
        else
        {
            previous = child;
            child = child->GetSibling();
        }
    }
}

Void CNode::RemoveAllChilds()
{
    if( m_Child )
    {
        CNode* node = m_Child;
        CNode* tmp = NULL;
        while( node )
        {
            tmp = node;
            node = node->GetSibling();
            tmp->SetParent( NULL );
        }

        DebugAssert( m_Child == NULL );
    }
}

Bool CNode::Update( )
{
	return TRUE;
}

Void CNode::PrepareForNextUpdate()
{
}

Bool CNode::RecursiveUpdate( )
{
    if( Update( ) )
	{
        CNode* child = GetChild();
        while( child )
		{
			child->RecursiveUpdate( );
            child = child->GetSibling();
		}
		PrepareForNextUpdate();
		return TRUE;
	}

    return FALSE;
}

Bool CNode::RecursiveUnInit()
{
    CNode* child = GetChild();
    while( child )
    {
		child->RecursiveUnInit();
        child = child->GetSibling();
    }
    SetParent( NULL );

    return TRUE;
}

UInt32 CNode::GetChildCount( ) const
{
    UInt32 i=0;
    CNode* child = GetChild();
    while( child )
    {
        i++;
        child = child->GetSibling();
    }

    return i;
}

Bool CNode::GetState( CNode::EState state ) const
{
    return m_States.GetBit( state );
}

Void CNode::SetState( CNode::EState state, Bool onOff )
{
    if( onOff )
        m_States.SetBit( state );
    else
        m_States.ClearBit( state );
}

Bool CNode::GetAttribute( CNode::EAttribute attrib ) const
{
    return m_Attributes.GetBit( attrib );
}

Void CNode::SetAttribute( CNode::EAttribute attrib, Bool onOff )
{
    if( onOff )
        m_Attributes.SetBit( attrib );
    else
        m_Attributes.ClearBit( attrib );
}

Bool CNode::Serialize( CPersistentArchive& ar )
{
    Int16 version = 0;

    UInt32 childCount = GetChildCount();

    if( ar.BeginScope( WT("Node"), version ) == version )
    {
        ar.Serialize( childCount, WT("ChildCount") );

        if( ar.IsLoading() )
        {
            UInt32 i=0;
            CRef< CNode > child;
            for( i=0;i<childCount;i++ )
            {
                ar.Serialize( child, WT("") );
                child->SetParent( this );
            }
        }
        else
        {
            CRef<CNode> child = GetChild();
            while( child )
            {
                ar.Serialize( child, WT("") );
                child = child->GetSibling();
            }
        }

        ar.EndScope();
    }
    else
    {
        return FALSE;
    }

    return TRUE;
}
