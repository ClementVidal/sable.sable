#ifndef _CORE_MATH_RANDOM_
#define _CORE_MATH_RANDOM_

#include <Sable\Core\Common\DataTypes.h>

namespace Sable
{

/** 
\ingroup CoreMath
Random number generator. <br>
It uses Georg Marsaglia's MWC algorithm to produce an unsigned integer.
See http://www.bobwheeler.com/statistics/Password/MarsagliaPost.txte
*/
class CRandom
{

public:

	/** @name Constructor/Destructor*/
    //@{
	CRandom();
    CRandom( UInt32 seedA, UInt32 seedB );
	CRandom( const UInt32 seedA );
	//@}

	/** @name Operator*/
    //@{
	//@}

	/** @name Manipulator*/
    //@{
	Float32 GetRandomNumber();
	Float32 GetRandomNumber( const Float32 lowerBound, const Float32 upperBound);
	//@}

private:

	// Methods

	// Attributes
	UInt32	m_SeedA;
	UInt32	m_SeedB;

};

Inline
CRandom::CRandom()
{
	// These values are not magical, just the default values Marsaglia used.
	// Any pair of unsigned integers should be fine.
	m_SeedA = 521288629;
	m_SeedB = 362436069;

}

Inline
CRandom::CRandom( UInt32 seedA, UInt32 seedB )
{
	m_SeedA = seedA;
	m_SeedB = seedB;
}

Inline
CRandom::CRandom( const UInt32 seedA )
{
	m_SeedA = seedA;
}


/**
Produce a uniform random sample from the open interval (0, 1).
The method will not return either end point
*/
Inline
Float32 CRandom::GetRandomNumber()
{
	// 0 <= u <= 2^32
	m_SeedA = 36969 * (m_SeedA & 65535) + (m_SeedA >> 16);
	m_SeedB = 18000 * (m_SeedB & 65535) + (m_SeedB >> 16);
	// The magic number below is 1/(2^32 + 1).
	// The result is strictly between 0 and 1.
	return (Float32) ((m_SeedA << 16) + m_SeedB) * (Float32) 2.328306435996595e-10;
}

/**
Produce a uniform random sample from the open interval (0, 1).
The method will not return either end point
*/
Inline
Float32 CRandom::GetRandomNumber( const Float32 lowerBound, const Float32 upperBound)
{
	return lowerBound + GetRandomNumber() *(upperBound - lowerBound);
}

}

#endif


