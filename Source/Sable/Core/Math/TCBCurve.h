#ifndef _SABLE_CORE_MATH_TCBCURVE_
#define _SABLE_CORE_MATH_TCBCURVE_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/Math/Tuple.h>
#include <Sable/Core/Collection/Pair.h>

namespace Sable
{

/** 
\ingroup CoreMath
Implement Kochanek–Bartels TCBSplines.
*/
template<typename DataType>
class CTCBCurve
{

public:

	/** @name DataTypes*/
	//@{
	template <typename DataType>
	struct SNode  
	{
		SNode():
		Tension( 0.0f ),
		Bias( 0.0f ),
		Continuity( 0.0f )
		{}

		DataType	Value;
		Float32		Tension;
		Float32		Continuity;
		Float32		Bias;
	};

	typedef SNode<DataType> Node;
	//@}

	/** @name Constructor/Destructor*/
    //@{
	CTCBCurve();
    ~CTCBCurve();
    //@}

	/** @name Operator*/
    //@{
	//@}

	/** @name Accessors*/
    //@{
	Float32				GetArcLengthParameter( Float32 p ) const;
	Void				SetArcLengthParametrizationTableSize( UInt32 c );
	Void				SetCapacity( UInt32 c );
	UInt32				GetCapacity() const;
	UInt32				GetNodeCount( )const;
	Void				SetNodeCount( UInt32 count );
	Node&				GetNode( Index index ) const;
	//@}

	/** @name Manipulator*/
    //@{
	Void		EvaluteAt( Float32 t, DataType& v ) const;
	DataType	EvaluteAt( Float32 t )const;
	Void		UpdateArcLengthParamerizationTable();
    //@}

private:

	// Methods
	
	// Attributes
	CArray< SNode<DataType> >			m_NodeTable;
	CArray< CPair<Float32, Float32> >	m_ArcLengthReparametrizationTable;

};

#include <Sable/Core/Math/TCBCurve.hpp>

typedef CTCBCurve<CVector3f> CTCBCurve3f;
typedef CTCBCurve<CVector2f> CTCBCurve2f;

}

#endif


