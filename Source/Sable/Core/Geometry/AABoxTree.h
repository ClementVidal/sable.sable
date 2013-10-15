#ifndef _SABLE_CORE_GEOMETRY_AABOXTREE_
#define _SABLE_CORE_GEOMETRY_AABOXTREE_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\Geometry\AABox.h>
#include <Sable\Core\Geometry\Triangle.h>

namespace Sable
{

class CBufferVisitor;
class CPersistentArchive;

/** 
\ingroup CoreGeometry
Axis Aligned Box tree
*/
class CAABoxTree 
{

public:

    /** @name DataTypes*/
    //@{
    struct SIntersection;

    class CNode
    {
    public:

        typedef CArrayUInt32 IndexTable;
        CNode();

        const CArray<CTriangle>& GetTriangleList() const;
        const CAABox& GetBox() const;
        const CNode*  GetLeftNode() const;
        const CNode*  GetRightNode() const;

        Bool    Intersect( const CRay& r, SIntersection& intersection ) const;
        Void    Build( const CBufferVisitor& bufferVisitor, const IndexTable& indexTable, CAABoxTree& tree, UInt32 depth );

    private:

        CAABox              m_Box;
        CNode*              m_LeftNode;
        CNode*              m_RightNode;
        CArray<CTriangle>   m_TriangleList;

        UInt32  FindBestAxis( const CBufferVisitor& bufferVisitor, const IndexTable& indexTable, CAABoxTree& tree );
        UInt32  FindLongestAxis( );

    };

    struct SIntersection
    {
        SIntersection();
        Float32         Dist;
        const CNode*    Node;
    };       
    //@}

	/** @name Constructor/Destructor*/
	//@{
	CAABoxTree();
	~CAABoxTree();
	//@}

	/** @name Accessors*/
	//@{
    const CNode*  GetRootNode() const;
    UInt32  GetMaxDepth() const;
    UInt32  GetMinVerticesPerLeaf() const;
	//@}

	/** @name Manipulator*/
	//@{
    SIntersection         Intersect( const CRay& r ) const;

    Bool Build( const CBufferVisitor& vbVisitor, const CBufferVisitor& ibVisitor );
	//@}

private:

    // Method

	// Attributes
    UInt32      m_MaxDepth;
    UInt32      m_MinVerticesPerLeaf;
    CNode*      m_RootNode;
	CFreeList< CNode >	m_NodeFreeList;

};

}

#endif


