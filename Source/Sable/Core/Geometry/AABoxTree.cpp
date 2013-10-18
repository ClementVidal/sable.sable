#include <Sable/Core/Geometry/AABoxTree.h>

#include <Sable/Core/Persistent/Archive.h>

using namespace Sable;

CAABoxTree::SIntersection::SIntersection()
{
    Node = NULL;
    Dist = -1.0f;
}

CAABoxTree::CNode::CNode()
{
    m_LeftNode = NULL;
    m_RightNode = NULL;
    m_Box.SetEmpty();
}   

CAABoxTree::CAABoxTree()
{
    m_MaxDepth = 32;
    m_MinVerticesPerLeaf = 128;
}

CAABoxTree::~CAABoxTree()
{

}

const CAABox& CAABoxTree::CNode::GetBox() const
{
    return m_Box;
}

const CArray<CTriangle>& CAABoxTree::CNode::GetTriangleList() const
{
    return m_TriangleList;
}

const CAABoxTree::CNode*  CAABoxTree::CNode::GetLeftNode() const
{
    return m_LeftNode;
}

const CAABoxTree::CNode*  CAABoxTree::CNode::GetRightNode() const
{
    return m_RightNode;
}

UInt32 CAABoxTree::CNode::FindBestAxis( const CBufferVisitor& bufferVisitor, const CAABoxTree::CNode::IndexTable& indexTable, CAABoxTree& tree  )
{
    UInt32 axis=0;
    UInt32 iAxisResult[3]; //stores how close end result is, the lower the better  

    CVector3f bboxCenter;
    CVector3f faceCenter;
    CVector3f triangleVertex[3];

    bboxCenter = m_Box.GetCenter();

    // For each axis
    for (axis=0;axis<3;axis++)
    {
        UInt32 left=0,right=0;

        // For each vertices
        for(UInt32 i=0;i<indexTable.GetItemCount();i+=3)
        {
            triangleVertex[0] = bufferVisitor.GetChunckElement<CVector3f>( indexTable[i+0] );  
            triangleVertex[1] = bufferVisitor.GetChunckElement<CVector3f>( indexTable[i+1] );  
            triangleVertex[2] = bufferVisitor.GetChunckElement<CVector3f>( indexTable[i+2] );  

            faceCenter = ( triangleVertex[0] + triangleVertex[1] + triangleVertex[2] ) / 3.0f;

            if (faceCenter[axis] <= bboxCenter[axis])
            {
                left++;
            }
            else
            {
                right++;
            }  

        }

        iAxisResult[axis] = (UInt32) MathAbs( (Float32) left-right );
    } 

    UInt32 index=0;
    UInt32 result=iAxisResult[0];
    for (UInt32 i=1;i<3;i++)
    {
        if (iAxisResult[i] < result)
        {
            result = iAxisResult[i];
            index=i;
        }
    }  

    return index;
}

UInt32  CAABoxTree::CNode::FindLongestAxis( )
{
    UInt32 axis = 0 ;

    if( m_Box.GetXSize() > m_Box.GetYSize() && m_Box.GetXSize() > m_Box.GetZSize() )
        axis = 0;
    if( m_Box.GetYSize() > m_Box.GetXSize() && m_Box.GetYSize() > m_Box.GetZSize() )
        axis = 1;
    if( m_Box.GetZSize() > m_Box.GetXSize() && m_Box.GetZSize() > m_Box.GetYSize() )
        axis = 2;

    return axis;
}

Void CAABoxTree::CNode::Build( const CBufferVisitor& bufferVisitor, const CAABoxTree::CNode::IndexTable& indexTable, CAABoxTree& tree, UInt32 depth )
{
    DebugAssert(indexTable.GetItemCount() % 3 == 0);  

    // Build the node bounding box based from the triangle list
    m_Box.SetEmpty();  

    if( indexTable.GetItemCount() == 0 )
    {
        return;
    }

    for(UInt32 i=0;i<indexTable.GetItemCount();i++)
    {
        m_Box.AddPoint( bufferVisitor.GetChunckElement<CVector3f>( indexTable[i] ) );
    }

    UInt32 axis = FindLongestAxis( );
    Bool subdivide = indexTable.GetItemCount() > tree.GetMinVerticesPerLeaf() && depth < tree.GetMaxDepth();
    CVector3f bboxCenter;
    CVector3f faceCenter;
    CTriangle triangle;
    UInt32 triCount = indexTable.GetItemCount() / 3;
    CNode::IndexTable leftSide;
    CNode::IndexTable rightSide; 

	bboxCenter = m_Box.GetCenter();

    rightSide.SetCapacity( indexTable.GetItemCount() / 2 );
    leftSide.SetCapacity( indexTable.GetItemCount() / 2 );

    // If we are on a leaf, store triangle data
    if( subdivide == FALSE )
    {
        m_TriangleList.SetItemCount( triCount );
    }

    for(UInt32 i=0;i<indexTable.GetItemCount();i+=3)
    {
        triangle[0] = bufferVisitor.GetChunckElement<CVector3f>( indexTable[i+0] );  
        triangle[1] = bufferVisitor.GetChunckElement<CVector3f>( indexTable[i+1] );  
        triangle[2] = bufferVisitor.GetChunckElement<CVector3f>( indexTable[i+2] );  

        faceCenter = triangle.GetCenter();

        if( subdivide )
        {
            if (faceCenter[axis] <= bboxCenter[axis]) 
            {
                //Store the verts to the left.
                leftSide.AddItemAtEnd( indexTable[i+0] );
                leftSide.AddItemAtEnd( indexTable[i+1] );
                leftSide.AddItemAtEnd( indexTable[i+2] );  
            }
            else
            {
                //Store the verts to the right.
                rightSide.AddItemAtEnd( indexTable[i+0] );
                rightSide.AddItemAtEnd( indexTable[i+1] );
                rightSide.AddItemAtEnd( indexTable[i+2] );  
            }  
        }
        else
        {
            m_TriangleList[i/3] = triangle;
        }
    }  

    if( subdivide  )
    {
        // Build child nodes
        if( leftSide.GetItemCount() > 0 )
        {
            DebugAssert(leftSide.GetItemCount() % 3 == 0);
            if( !tree.m_NodeFreeList.IsFull() )
            {
                CNode& newNode = tree.m_NodeFreeList.AddItem();
                m_LeftNode = &newNode;
                m_LeftNode->Build( bufferVisitor, leftSide, tree, depth + 1 );
            }
        }
        if (rightSide.GetItemCount() > 0)
        {
            DebugAssert(rightSide.GetItemCount() % 3 == 0);  
            if( !tree.m_NodeFreeList.IsFull() )
            {
                CNode& newNode = tree.m_NodeFreeList.AddItem();
                m_RightNode = &newNode;
                m_RightNode->Build( bufferVisitor, rightSide, tree, depth + 1 );
            }
        }
    }
}

Bool CAABoxTree::CNode::Intersect( const CRay& r, CAABoxTree::SIntersection& inter ) const
{
    Float32 dist = GetBox().Intersect( r );

    if( dist == -1.0f )
        return FALSE;

    // If we hit the bounding box and if we are a leaf
    if( GetLeftNode() == NULL && GetRightNode() == NULL )
    {
        // the test for each triangles
        for(UInt32 i=0;i<m_TriangleList.GetItemCount();i++)
        {
            dist = m_TriangleList[i].IntersectWithoutCulling( r );
            if( dist > -1.0f )
            {
                inter.Node = this;
                inter.Dist = dist;
                return TRUE;
            }
        }
    }
    else
    {
        if( GetLeftNode() )
        {
            if( GetLeftNode()->Intersect( r, inter ) )
                return TRUE;
        }

        if( GetRightNode() )
        {
            if( GetRightNode()->Intersect( r, inter ) )
                return TRUE;
        }
    }

    return FALSE;
}

const CAABoxTree::CNode* CAABoxTree::GetRootNode() const
{
    return m_RootNode;
}

UInt32 CAABoxTree::GetMaxDepth() const
{
    return m_MaxDepth;
}

UInt32 CAABoxTree::GetMinVerticesPerLeaf() const
{
    return m_MinVerticesPerLeaf;
}

CAABoxTree::SIntersection CAABoxTree::Intersect( const CRay& r ) const
{
    SIntersection inter;
    inter.Dist = -1.0f;
    inter.Node = NULL;
    m_RootNode->Intersect( r, inter );
    return inter;
}

Bool CAABoxTree::Build( const CBufferVisitor& vbVisitor, const CBufferVisitor& ibVisitor )
{
	m_NodeFreeList.SetCapacity( 4096 );
	m_RootNode = &m_NodeFreeList.AddItem();
    CNode::IndexTable indexTable( ibVisitor.GetChunckCount() );

    for(UInt32 i = 0;i<ibVisitor.GetChunckCount();i++ )
    {
        indexTable[i] = ibVisitor.GetChunckElement<UInt32>(i);
    }

	m_RootNode->Build( vbVisitor, indexTable, *this, 0 );

	return TRUE;
}