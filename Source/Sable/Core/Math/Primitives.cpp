#include <Sable\Core\Math\Primitives.h>

#include <Sable\Core\Math\Vector3f.h>

#include <math.h>
#include <float.h>

using namespace Sable;

Bool Sable::MathIsNearlyEqual( Float32 a, Float32 b ) 
{
	return ( ( a ) > ( ( b ) - FLOAT32_ERROR_THRESHOLD ) ? ( ( a ) < ( ( b ) + FLOAT32_ERROR_THRESHOLD ) ? TRUE : FALSE ) : FALSE );
}

Bool Sable::MathIsNearlyEqual( Float32 a, Float32 b, Float32 threshold ) 
{
	return ( ( a ) > ( ( b ) - threshold ) ? ( ( a ) < ( ( b ) + threshold ) ? TRUE : FALSE ) : FALSE );
}

Bool Sable::MathIsNearlyEqual( const CVector3f& a, const CVector3f& b )
{
	return	MathIsNearlyEqual( a.GetX(), b.GetX() ) && 
			MathIsNearlyEqual( a.GetY(), b.GetY() ) &&
			MathIsNearlyEqual( a.GetZ(), b.GetZ() );

};

UInt32 Sable::MathGetHighestBitSet( const UInt32 i )
{
	return  (i & (1<<31))?31:
			(i & (1<<30))?30:
			(i & (1<<29))?29:
			(i & (1<<28))?28:
			(i & (1<<27))?27:
			(i & (1<<26))?26:
			(i & (1<<25))?25:
			(i & (1<<24))?24:
			(i & (1<<23))?23:
			(i & (1<<22))?22:
			(i & (1<<21))?21:
			(i & (1<<20))?20:
			(i & (1<<19))?19:
			(i & (1<<18))?18:
			(i & (1<<17))?17:
			(i & (1<<16))?16:
			(i & (1<<15))?15:
            (i & (1<<14))?14:
            (i & (1<<13))?13:
            (i & (1<<12))?12:
            (i & (1<<11))?11:
            (i & (1<<10))?10:
            (i & (1<<9))?9:
            (i & (1<<8))?8:
            (i & (1<<7))?7:
            (i & (1<<6))?6:
            (i & (1<<5))?5:
            (i & (1<<4))?4:
            (i & (1<<3))?3:
            (i & (1<<2))?2:
            (i & (1<<1))?1:
            (i & (1<<0))?0:0xffff;
}

UInt32 Sable::MathGetLowestBitSet ( const UInt32 i)
{
    return  (i & (1<<0))?0:
            (i & (1<<1))?1:
            (i & (1<<2))?2:
            (i & (1<<3))?3:
            (i & (1<<4))?4:
            (i & (1<<5))?5:
            (i & (1<<6))?6:
            (i & (1<<7))?7:
            (i & (1<<8))?8:
            (i & (1<<9))?9:
            (i & (1<<10))?10:
            (i & (1<<11))?11:
            (i & (1<<12))?12:
            (i & (1<<13))?13:
            (i & (1<<14))?14:
			(i & (1<<15))?15:
			(i & (1<<16))?16:
			(i & (1<<17))?17:
			(i & (1<<18))?18:
			(i & (1<<19))?19:
			(i & (1<<20))?20:
			(i & (1<<21))?21:
			(i & (1<<22))?22:
			(i & (1<<23))?23:
			(i & (1<<24))?24:
			(i & (1<<25))?25:
			(i & (1<<26))?26:
			(i & (1<<27))?27:
			(i & (1<<28))?28:
			(i & (1<<29))?29:
            (i & (1<<30))?30:
			(i & (1<<31))?31:0xffff;
}

Float32	Sable::MathGetRandomFloatInRange( Float32 a, Float32 b)
{
	Float32
		tmp = (Float32)rand() / ((Float32)RAND_MAX);
	return a + ( tmp * b );
}

Int32 Sable::MathGetNearestPowerOfTwo( const Int32 input )
{
	// the least possible power-of-two value is 1
	if (input <= 1)
		return 1;

	UInt32
		highestBit = MathGetHighestBitSet(input);
	UInt32
		roundingTest = input & (1<< (highestBit-1)); 

	if (roundingTest) 
		highestBit++;

	return (Int32) (1 << highestBit);
}

UInt32 Sable::MathGetRoundedUpValue( Float32 value )
{
	return (UInt32)( value + 0.5f );
}

Float32	Sable::MathSqrt( Float32 f)
{
    DebugAssert( f >= 0.0f && MathIsValidFloat32( f ) );
	return sqrtf(f);
}

Bool Sable::MathIsValidFloat32( Float32 f )
{
#if defined( SETUP_IMPLTYPE_MSW )
    return _isnan( f ) == 0;
#else
	DebugError("Not yet implemented");
    return FALSE;
#endif
}

Float32	Sable::MathGetReciprocalSquareRoot( Float32 f)
{
	return 1.0f / sqrtf(f);
}


Float32 Sable::MathExponential( Float32 f )
{
	return expf( f );
}

Float32	Sable::MathCos( Float32 f)
{
	return cos( f );
}

Float32	Sable::MathArcCos( Float32 f)
{
	return acos( f );
}

Float32	Sable::MathSin( Float32 f)
{
	return sin( f );
}

Float32	Sable::MathArcSin( Float32 f)
{
	return asin( f );
}

Float32	Sable::MathTan( Float32 f)
{
	return tan( f);
}

Float32	Sable::MathCot( Float32 f)
{
	return MathCos( f ) / MathSin( f );
}

Float32	Sable::MathArcTan2( Float32 fa, Float32 fb )
{
	return atan2f( fa, fb );
}

Float32	Sable::MathArcTan( Float32 a )
{
	return atanf( a );
}

Float32 Sable::MathLog( Float32 v )
{
	return log(v);
}

Float32 Sable::MathLog2( Float32 v )
{
    return MathLog(v) / MathLog(2.0f);
}

Float32 Sable::MathLog10( Float32 v )
{
	return log10(v);
}

Float32 Sable::MathExp2( Float32 v )
{
    return exp( v * log( 2.0f ) );
}

Float32 Sable::MathFloor( Float32 f)
{
	return floor( f );
}

Float32 Sable::MathCeil( Float32 f)
{
	return ceil( f );
}

Float32 Sable::MathAbs( Float32 f)
{
	return fabsf( f );
}

Int32 Sable::MathAbs( const Int32 f)
{
	return abs( f );
}

Float32 Sable::MathPow( Float32 value, Float32 expo )
{
	return pow( value, expo );
}

Int32 Sable::MathPow( Int32 value, Int32 expo )
{
	return (Int32) pow( (Float32)value, (Float32)expo );
}

Bool Sable::MathIsPowerOfTwo( Int32 n )
{
	return (n) && !(n & (n - 1)); //this checks if the integer n is a power of two or not
}

Float32 NormalizeRadianValue( Float32 r, Float32 center )
{
	return r - MathTwoPi * MathFloor((r + MathPi - center) / MathTwoPi);
}

