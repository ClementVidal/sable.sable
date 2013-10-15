#ifndef _SABLE_CORE_MATH_FFT_
#define _SABLE_CORE_MATH_FFT_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\Collection\Array.h>

namespace Sable
{

/**
Implementation of a Fast fourrier transform
*/
class CFFT
{

public:

    /** @name DataTypes*/
    //@{
    struct SOutput
    {
        Float32 Real;
        Float32 Imag;
    };
    //@}

    /** @name Constructor/Destructor*/
    //@{
    CFFT();
    ~CFFT();
    //@}

    /** @name Manipulator*/
    //@{
    Void Initialize( UInt32 inputSize );
    Bool Compute( Int16* realIn );
    const CArray<SOutput>& GetOutput() const;
    //@}

private:

    // Methods
    Bool  IsPowerOfTwo(UInt32 p_nX);
    UInt32 NumberOfBitsNeeded(UInt32 sampleCount);
    UInt32 ReverseBits(UInt32 index, UInt32 bit);
    //Float32 Index_to_frequency(UInt32 baseFreq, UInt32 samples, UInt32 index);
    Bool ComputeComplexFFT( UInt32 sampleCount, SOutput* input, SOutput* output );

    // Attributes
    CArray<SOutput>     m_Input;
    CArray<SOutput>     m_Output;

    UInt32              m_SampleCount;

};

Inline
UInt32 CFFT::ReverseBits( UInt32 index, UInt32 bit )
{
    UInt32 i, rev;

    for(i=rev=0; i < bit; i++)
    {
        rev = (rev << 1) | (index& 1);
        index >>= 1;
    }

    return rev;
}

}

#endif