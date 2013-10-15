#ifndef _SABLE_GRAPHICS_GEOMETRY_MESHTNBCALCULATOR_
#define _SABLE_GRAPHICS_GEOMETRY_MESHTNBCALCULATOR_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\Math\Matrix3x3f.h>

#include <Sable\Graphics\Geometry\Mesh.h>

namespace Sable
{


class CInputProxy
{
public:

	UInt32 GetTriangleCount() const 
	{
		return 0;
	}

	void GetTriangleIndices( 
		UInt32 indwTriNo, 
		UInt32 outdwPos[3], 
		UInt32 outdwNorm[3], 
		UInt32 outdwUV[3] ) const
	{

	}

	void GetPosition( UInt32 indwPos, CVector3f& outfPos ) const
	{

	}

	//! not virtual to save the call overhead
	//! /param indwPos 0..
	//! /param outfUV 
	void GetUV( UInt32 indwPos, CVector2f& outfUV ) const
	{

	}

};

/** 
\ingroup GraphicsGeometry
Compute the pervertex Tangent, Normal and BiNormal basis( for per pixel lighting ... )
*/
template <class InputProxy>
class CGeometryMeshTNBCalculator
{

public:

	/** @name Constructor/Destructor*/
    //@{
	CGeometryMeshTNBCalculator();
	virtual ~CGeometryMeshTNBCalculator();
    //@}

	/** @name Operator*/
    //@{
    //@}

	/** @name Accessors*/
    //@{
	//@}

	/** @name Manipulator*/
	//@{
	Void	Calculate( const InputProxy& input );
	UInt32	GetBaseCount() const;
	Void GetTriangleBaseIndices( const UInt32 index , UInt32 outdwBase[3] ) const;
	Void GetBase( const UInt32 index, CVector3f& outU, CVector3f& outV, CVector3f& outN ) const;

	//@}

private:	

	// DataTypes
	struct STriBaseIndex
	{
		UInt32 p[3];							//!< index in m_BaseVectors 
	};

	struct SBaseIndex
	{
		Bool        operator==( const SBaseIndex& other ) const ;
		Bool        operator<( const SBaseIndex& other ) const ;
		UInt32 PositionIndex;
		UInt32 NormalIndex;
	};
	typedef CMap<SBaseIndex, UInt32> BaseMap;

	// Methods
	Float32 CalculateAngleBetween( const CVector3f& invA, const CVector3f&invB );
	Void AddNormalToBase( BaseMap& basemMap, UInt32 positionIndex, UInt32 normalIndex, const CVector3f& normal );
	UInt32 AddUVToBase( BaseMap& baseMap, UInt32 positionIndex, UInt32 normalIndex,const CVector3f &U, const CVector3f &V, const CVector3f &normal );

	// Attribute
	CArray<CMatrix3x3f>			m_BaseTable;
	UInt32						m_UsedBaseCount;
	CArray<STriBaseIndex>		m_TriBaseAssigment;

};

#include <Sable\Graphics\Geometry\MeshTNBCalculator.hpp>

}

#endif
