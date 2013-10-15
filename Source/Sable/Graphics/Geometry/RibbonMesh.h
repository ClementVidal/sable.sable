#ifndef _SABLE_GRAPHICS_GEOMETRY_RIBBONMESH_
#define _SABLE_GRAPHICS_GEOMETRY_RIBBONMESH_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Graphics\Common\DataTypes.h>

#include <Sable\Core\Math\TCBCurve.h>
#include <Sable\Graphics\Geometry\Header.h>
#include <Sable\Graphics\Geometry\Vertexlayout.h>

namespace Sable
{

/** 
\ingroup GraphicsGeometry
*/
class CGeometryRibbonMesh : public CGeometryMesh
{

    DEFINE_MANAGED_CLASS( CGeometryRibbonMesh );
	
public:

    /** DataTypes*/
    //@{
    //@}
    
    /** @name Constructor/Destructor*/
    //@{
    CGeometryRibbonMesh();
    ~CGeometryRibbonMesh();
    //@}
    
    /** @name Accessors*/
    //@{
	CTCBCurve3f&	GetCurve();
	Void			SetStepCount( UInt32 count );
	Void			SetWidth( Float32 width );
    //@}
    
    /** @name Manipulator*/
    //@{
	Void	ReBuild( const CCamera& cam );
	//@}
    
private:
    
	// DataTypes
	struct SVertex
	{
		CVector3f	Position;
		CVector2f	UVCoord;
	};

	// Methods
	Void	CreateBuffer();
	Void	AddSegment( const CCamera& cam, Byte* vtxBuffer, const CVector3f& a, const CVector3f& b );

    // Attributes
	CTCBCurve3f				m_Curve;
	CGeometryIndexBuffer	m_IndexBuffer;
	CGeometryVertexBuffer	m_VertexBuffer;
	CGeometryVertexLayout	m_VertexLayout;
	UInt32					m_StepCount;
	Float32					m_Width;
};

}

#endif


