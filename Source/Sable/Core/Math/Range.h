#ifndef _CORE_MATH_RANGE_
#define _CORE_MATH_RANGE_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/Math/Random.h>
#include <Sable/Core/Common/Manager.h>

#include <Sable/Core/Math/Vector3f.h>
#include <Sable/Core/Math/Vector4f.h>
#include <Sable/Core/Common/Color.h>

namespace Sable
{

/** 
\ingroup CoreMath
Range of value.
*/
template<class DataType>
class CRange 
{

public:

	/** @name Constructor/Destructor*/
	//@{
	CRange();
	CRange( const DataType& v );
	CRange(const DataType& low, const DataType& high);
	CRange( const CRange& other);
	virtual ~CRange();
	//@}

	/** @name Operator*/
	//@{
	CRange& operator=( const CRange& other );
	//@}

	/** @name Accessors*/
	//@{
	const DataType& GetLowValue( ) const { return m_LowValue;}
	const DataType& GetHighValue( ) const { return m_HighValue;}
	Void            SetLowValue( const DataType& value ) { m_LowValue = value; }
	Void            SetHighValue( const DataType& value ) { m_HighValue = value; }
	Void            SetValues( const DataType& lowValue, const DataType& highValue ) ;
	DataType        GetLinearInterpolationValue( const Float32 t ) const;
    DataType        GetNormalizedCoeficient( const DataType& value ) const;
    DataType        GetRandomValueInRange(CRandom& randomGen)const;
	DataType        GetRandomValueInRange()const;
	//@}

	/** @name Manipulator*/
	//@{
	Void			Expand( const DataType& d );
	DataType		Clamp( const DataType& d );
	Bool			Serialize( CPersistentArchive& ar );
	DataType        GetDeltaValue( ) const;
	//@}

private:

	// Methods

	// Attributes
	DataType	m_LowValue;
	DataType	m_HighValue;

};

typedef CRange<CVector4f> CVector4Range;
typedef CRange<CVector3f> CVector3Range;
typedef CRange<Float32> CFloat32Range;
typedef CRange<Int32> CInt32Range;
typedef CRange<UInt32> CUInt32Range;
typedef CRange<CColor> CColorRange;

#include <Sable/Core/Math/Range.hpp>

}

#endif
