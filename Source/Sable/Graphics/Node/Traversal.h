#ifndef _SABLE_GRAPHICS_NODE_TRAVERSAL_
#define _SABLE_GRAPHICS_NODE_TRAVERSAL_

#include <Sable\Graphics\Common\DataTypes.h>
#include <Sable\Core\Common\MethodPointer.h>

namespace Sable
{

class CNode;

/** 
\ingroup GraphicsSceneGraph
*/
template <class TInstance, class TArgs1=Void*, class TArgs2=Void*, class TArgs3=Void*>
class CNodeTraversal
{

public:

    /** @name DataTypes*/
    //@{
    typedef CMethodPointer< TInstance, CNode&, TArgs1, TArgs2, TArgs3> MethodPointer;
    //@}

    /** @name Constructor/Destructor*/
    //@{
	CNodeTraversal( MethodPointer preTravesalCallback, MethodPointer postTravesalCallback = MethodPointer() )
    {
        m_PreTraversalCallBack = preTravesalCallback;        
        m_PostTraversalCallBack = postTravesalCallback;
    }
	virtual ~CNodeTraversal()
    {

    }
    //@}

    /** @name Accessors*/
    //@{
	//\}

    /** @name Manipulator*/
    //@{
    Void Traverse( CNode& root )
    {
        m_PreTraversalCallBack( root );
        CNode* child = root.GetChild();
        while( child )
        {
            Traverse( *child );
            child = child->GetSibling();
        }
        m_PostTraversalCallBack( root );
    }

    Void Traverse( CNode& root, TArgs1 arg1 )
    {
        m_PreTraversalCallBack( root, arg1 );
        CNode* child = root.GetChild();
        while( child )
        {
            Traverse( *child, arg1 );
            child = child->GetSibling();
        }
        m_PostTraversalCallBack( root, arg1 );
    }

    Void Traverse( CNode& root, TArgs1 arg1, TArgs2 arg2 )
    {
        m_PreTraversalCallBack( root, arg1, arg2 );
        CNode* child = root.GetChild();
        while( child )
        {
            Traverse( *child, arg1, arg2 );
            child = child->GetSibling();
        }
        m_PostTraversalCallBack( root, arg1, arg2 );
    }

    Void Traverse( CNode& root, TArgs1 arg1, TArgs2 arg2, TArgs3 arg3 )
    {
        m_PreTraversalCallBack( root, arg1, arg2, arg3 );
        CNode* child = root.GetChild();
        while( child )
        {
            Traverse( *child, arg1, arg2, arg3 );
            child = child->GetSibling();
        }
        m_PostTraversalCallBack( root, arg1, arg2, arg3 );
    }
    //@}

private:    

	//Methods
    
	//Attributes
    MethodPointer   m_PreTraversalCallBack;
    MethodPointer   m_PostTraversalCallBack;
};

}

#endif
