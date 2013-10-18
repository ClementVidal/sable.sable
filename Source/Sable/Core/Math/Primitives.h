#ifndef _SABLE_CORE_MATH_PRIMITIVES_
#define _SABLE_CORE_MATH_PRIMITIVES_

#include <Sable/Core/Common/DataTypes.h>

/** 
\file Sable\Core\Math\Primitives.h
Basic math primitives
*/

namespace Sable
{

class CVector3f;

/** 
\def MathPi
PI constant
*/
#define MathPi (3.1415926535897f)

/** 
\def MathPi
Two PI constant
*/
#define MathTwoPi (6.2831853071795f)

/** 
\def MathClamp
Return a value clamped between low and hight
*/
#define MathClamp( value, low, hight ) ( ( value < low ) ? low : ( ( value > hight ) ? hight : value ) )

/** 
\def MathClampToZero
Convert value to 0.0 if: ( value <= FLOAT32_ERROR_THRESHOLD && value >= -FLOAT32_ERROR_THRESHOLD
*/
#define MathClampToZero( value ) ( ( (value) <= FLOAT32_ERROR_THRESHOLD && (value) >= -FLOAT32_ERROR_THRESHOLD ) ? 0.0f : (value) )

/** 
\def MathMax
Return the maximum of a and b
*/
#define MathMax( a, b ) ( ( a > b ) ? a : b )

/** 
\def MathMin
Return the minimum of a and b
*/
#define MathMin( a, b ) ( ( a > b ) ? b : a )

/** 
\def MathIsInRangeInclusive
Return TRUE if value is within the inclusive range comprise between a and b
*/
template< typename DataType >
bool MathIsInRangeInclusive( const DataType& value, const DataType& a, const DataType& b )
{
	return ( ( value >= a ) ? ( ( value <= b ) ? TRUE : FALSE ) : FALSE ) ;
}

/** 
\def MathIsInRangeExclusive
Return TRUE if value is within the exclusive range comprise between a and b
*/
template< typename DataType >
bool MathIsInRangeExclusive( const DataType& value, const DataType& a, const DataType& b )
{
	return ( ( value > a ) ? ( ( value < b ) ? TRUE : FALSE ) : FALSE ) ;
}

/** 
\def MathDegreeToRadian
Convert value from a degree value to a radian value
*/
#define MathDegreeToRadian( value ) ( (value ) * MathPi / 180.0f )

/** 
\def MathRadianToDegree
Convert value from a radian value to a degree value
*/
#define MathRadianToDegree( value ) ( (value ) / MathPi * 180.0f )

/** 
\ingroup CoreMath
\def MathIsFloat32Ind
*/
#define MathIsFloat32Ind( value ) ( ( *(UInt32*)(&value) ) == FLOAT32IND )

/** 
\ingroup CoreMath
\def MathIsFloat32Nan
*/
#define MathIsFloat32Nan( value ) ( ( *(UInt32*)(&value) ) == FLOAT32NAN )

/** 
\ingroup CoreMath
\def MathIsFloat32Inf
*/
#define MathIsFloat32Inf( value ) ( ( *(UInt32*)(&value) ) == FLOAT32INF )

/** 
\ingroup CoreMath
\def MathIsFloat32NegInf
*/
#define MathIsFloat32NegInf( value ) ( ( *(UInt32*)(&value) ) == FLOAT32NINF )

/**
\ingroup CoreMath
Linearly interpolate between two values
*/
template< typename DataType >
DataType MathLerp( const DataType& a, const DataType& b, Float32 t  )
{
	return ( (a)*(1.0f-(t)) + (b)*(t) );
}

/**
\ingroup CoreMath
Compute a radom float whitin a given range
\deprecated Should take as third arg a random number generator
*/
Float32	MathGetRandomFloatInRange( Float32 a, Float32 b);

/**
\ingroup CoreMath
Approximation test
*/
Inline
Bool MathIsNearlyEqual( Float32 a, Float32 b ) ;

/**
\ingroup CoreMath
Approximation test
*/
Inline
Bool MathIsNearlyEqual( Float32 a, Float32 b, Float32 threshold ) ;

/**
\ingroup CoreMath
Approximation test
*/
Bool MathIsNearlyEqual( const CVector3f& a, const CVector3f& b ) ;

/**
\ingroup CoreMath
Compute the reciprocal Square Root ( 1.0f / sqrt(f) ) of f
*/
Float32	MathGetReciprocalSquareRoot( Float32 f);

/**
\ingroup CoreMath
return the floor of f
*/
Float32 MathFloor( Float32 f);

/**
\ingroup CoreMath
Return the ceiled value of f
*/
Float32 MathCeil( Float32 f);

/**
\ingroup CoreMath
Return the square root of f
*/
Float32	MathSqrt( Float32 f);

/**
\ingroup CoreMath
Return the exponential of f
*/
Float32 MathExponential( Float32 f );

/**
\ingroup CoreMath
Return the cosine of f
*/
Float32	MathCos( Float32 f);

/**
\ingroup CoreMath
Return the arc cosine of f
*/
Float32	MathArcCos( Float32 f);

/**
\ingroup CoreMath
Return the arc sine of f
*/
Float32	MathArcSin( Float32 f);

/** 
\ingroup CoreMath
Convert value from a degree value to a radian value
*/
Float32	MathSin( Float32 f);

/**
\ingroup CoreMath
Return the tangent of f
*/
Float32	MathTan( Float32 f);

/**
\ingroup CoreMath
Return the co tangent of f (Wich is equal to Cos(f)/Sin(f) )
*/
Float32	MathCot( Float32 f);

/**
\ingroup CoreMath
Execute the trigonometric function atan2
*/
Float32	MathArcTan2(  Float32 fa, Float32 fb );

/**
\ingroup CoreMath
Execute the trigonometric function atan2
*/
Float32	MathArcTan( Float32 a );

/**
\ingroup CoreMath
Return the base 2 log of v
*/
Float32 MathLog2( Float32 v );

/**
\ingroup CoreMath
Return the decimal log of v
*/
Float32 MathLog10( Float32 v );

/**
\ingroup CoreMath
Return the natural log of v
*/
Float32 MathLog( Float32 v );

/**
\ingroup CoreMath
Return the base 2 exp of v
*/
Float32 MathExp2( Float32 v );

/**
\ingroup CoreMath
Return the natural exp of v
*/
Float32 MathExp( Float32 v );

/**
\ingroup CoreMath
Return the absolute value of f
*/
Float32 MathAbs( Float32 f);

/**
\ingroup CoreMath
Return the absolute value of f
*/
Int32 MathAbs( const Int32 i);

/**
\ingroup CoreMath
Return value raised to the power of expo
*/
Float32 MathPow( Float32 value, Float32 expo );

/**
\ingroup CoreMath
Return value raised to the power of expo
*/
Int32 MathPow( Int32 value, Int32 expo );

/**
\ingroup CoreMath
Round up a given value
*/
UInt32 MathGetRoundedUpValue( Float32 value );

/**
\ingroup CoreMath
Check if a given value is a power of two
*/
Bool MathIsPowerOfTwo( Int32 n );

/**
\ingroup CoreMath
Return the 0 based index of the highest bit set
*/
UInt32 MathGetHighestBitSet( const UInt32 i );

/**
\ingroup CoreMath
Return the 0 based index of the lowest bit set
*/
UInt32 MathGetLowestBitSet( const UInt32 i );

/**
\ingroup CoreMath
Return the nearset prower of two of input
*/
Int32 MathGetNearestPowerOfTwo( const Int32 input );

/**
\ingroup CoreMath
Return true is f is a valid Float32 
*/
Bool MathIsValidFloat32( Float32 f );

/**
\ingroup CoreMath
Normalize an angle in a 2pi wide interval around a center value.
*/
Float32 NormalizeRadianValue( Float32 r, Float32 center = 0.0f );

}

#endif
