#include <Sable/Gui/Layout/Item.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1( Sable, CLayoutItem, CManagedObject );

CLayoutItem::CLayoutItem():
	CManagedObject()
{
    m_ChildCount = 0;
    m_Parent = NULL;
}

CLayoutItem::~CLayoutItem()
{
}

Void CLayoutItem::RemoveAllChild()
{
    CLayoutItem* child = GetChild();
    while( child )
    {
        child->SetParent( NULL );
        child = child->GetSibling();
    }
    m_Child = NULL;
    m_ChildCount = 0;
}

Void CLayoutItem::AddChild( CLayoutItem& child )
{
    if( m_Child )
    {
        child.m_Sibling = m_Child;
        m_Child = &child;
    }
    else
    {
        m_Child = &child;
    }

    m_ChildCount++;
}

CLayoutItem& CLayoutItem::SetParent( CLayoutItem* p )
{
    if( p == m_Parent )
        return *this;

    // Create thisRef in order to ensure that the widget will be destroyed 
    // AT THE END of this function.
    // This canappend if RemoveChild remove the last ref to this object
    CRef<CLayoutItem> thisRef = this;

    // Remove old parenting
    if( m_Parent )
    {
        m_Parent->RemoveChild( *this );
        m_Parent = NULL;
    }

    // Add new one
    if( p )
    {
        m_Parent = p;
        m_Parent->AddChild( *this );
    }

    return *this;
}

Bool CLayoutItem::RemoveChild( CLayoutItem& childToErase )
{
    CLayoutItem* child = GetChild();
    CLayoutItem* previousChild = NULL;

    while( child )
    {
        if( child == &childToErase )
        {
            if( previousChild )
            {
                previousChild->m_Sibling = child->GetSibling();
                m_ChildCount--;
            }
            else
            {
                m_Child = child->GetSibling();
                m_ChildCount--;
            }
        }

        previousChild = child;
        child = child->GetSibling();
    }
    return TRUE;
}

CLayoutItem* CLayoutItem::GetParent() const
{
    return m_Parent;
}

CLayoutItem* CLayoutItem::GetSibling() const
{
    return m_Sibling;
}

UInt32 CLayoutItem::GetChildCount() const
{
    return m_ChildCount;
}

CLayoutItem* CLayoutItem::GetChild() const
{
    return m_Child;
}
