#include <Sable/Core/Math/FFT.h>

using namespace Sable;

#define SWAP(a,b) tempr=(a);(a)=(b);(b)=tempr

CFFT::CFFT()
{
    m_SampleCount = 0;
}

CFFT::~CFFT()
{
}

Void CFFT::Initialize( UInt32 inputSize )
{
    m_Input.SetItemCount( inputSize / 2 );
    m_Output.SetItemCount( inputSize / 2 );

    if( !IsPowerOfTwo( inputSize ) )
        return;

    m_SampleCount = inputSize;
}

/*
void CFFT::WindowFunc(windowfunc_t whichFunction, int NumSamples, float *in)
{
    int i;

    switch (whichFunction) {
    case BARTLETT:
        for (i = 0; i < NumSamples / 2; i++) {
            in[i] *= (i / (float) (NumSamples / 2));
            in[i + (NumSamples / 2)] *=
                (1.0 - (i / (float) (NumSamples / 2)));
        }
        break;

    case HAMMING:
        for (i = 0; i < NumSamples; i++)
            in[i] *= 0.54 - 0.46 * cos(2 * M_PI * i / (NumSamples - 1));
        break;

    case HANNING:
        for (i = 0; i < NumSamples; i++)
            in[i] *= 0.50 - 0.50 * cos(2 * M_PI * i / (NumSamples - 1));
        break;
    case RECTANGULAR:
        break;
    }
}
*/
Bool CFFT::Compute( Int16* realIn )
{
    if( m_SampleCount == 0 )
        return FALSE;

   Int32 half = m_SampleCount / 2;
   Int32 i;

   Float32 theta = MathPi / half;
   Float32 wtemp = (Float32) MathSin(0.5f * theta);
   Float32 wpr = -2.0f * wtemp * wtemp;
   Float32 wpi = (Float32) MathSin(theta);
   Float32 wr = 1.0f + wpr;
   Float32 wi = wpi;

   Int32 i3;

   Float32 h1r, h1i, h2r, h2i;

   for (i = 0; i < half; i++) {
      m_Input[i].Real = realIn[2 * i];
      m_Input[i].Imag = realIn[2 * i + 1];
   }

   ComputeComplexFFT( half, m_Input.GetBuffer(), m_Output.GetBuffer() );

   for (i = 1; i < half / 2; i++) {

      i3 = half - i;

      h1r = 0.5f * (m_Output[i].Real + m_Output[i3].Real);
      h1i = 0.5f * (m_Output[i].Imag - m_Output[i3].Imag);
      h2r = 0.5f * (m_Output[i].Imag + m_Output[i3].Imag);
      h2i = -0.5f * (m_Output[i].Real - m_Output[i3].Real);

      m_Output[i].Real = h1r + wr * h2r - wi * h2i;
      m_Output[i].Imag = h1i + wr * h2i + wi * h2r;
      m_Output[i3].Real = h1r - wr * h2r + wi * h2i;
      m_Output[i3].Imag = -h1i + wr * h2i + wi * h2r;

      wr = (wtemp = wr) * wpr - wi * wpi + wr;
      wi = wi * wpr + wtemp * wpi + wi;
   }

   m_Output[0].Real = (h1r = m_Output[0].Real) + m_Output[0].Imag;
   m_Output[0].Imag = h1r - m_Output[0].Imag;

   return TRUE;
}

Bool CFFT::ComputeComplexFFT( UInt32 sampleCount, SOutput* input, SOutput* output )
{
    UInt32 numBits;
    UInt32 i, j, k, n;
    UInt32 blockSize, blockEnd;

    Float32 angleNumerator = 2.0 * MathPi;
    Float32 tr, ti;
     Float32 delta_angle, sm2, sm1, cm2, cm1, w, ar[3], ai[3];

    numBits = NumberOfBitsNeeded ( sampleCount );

    for( i=0; i < sampleCount; i++ )
    {
        j = ReverseBits ( i, numBits );
        output[j].Real = input[i].Real;
        output[j].Imag = input[i].Imag;
    }

    blockEnd = 1;
    for( blockSize = 2; blockSize <= sampleCount; blockSize <<= 1 )
    {
        delta_angle = angleNumerator / (Float32)blockSize;
        sm2 = MathSin ( -2 * delta_angle );
        sm1 = MathSin ( -delta_angle );
        cm2 = MathCos ( -2 * delta_angle );
        cm1 = MathCos ( -delta_angle );
        w = 2 * cm1;

        for( i=0; i < sampleCount; i += blockSize )
        {
            ar[2] = cm2;
            ar[1] = cm1;

            ai[2] = sm2;
            ai[1] = sm1;

            for ( j=i, n=0; n < blockEnd; j++, n++ )
            {
                ar[0] = w*ar[1] - ar[2];
                ar[2] = ar[1];
                ar[1] = ar[0];

                ai[0] = w*ai[1] - ai[2];
                ai[2] = ai[1];
                ai[1] = ai[0];

                k = j + blockEnd;
                tr = ar[0]*output[k].Real - ai[0]*output[k].Imag;
                ti = ar[0]*output[k].Imag + ai[0]*output[k].Real;

                output[k].Real = output[j].Real - tr;
                output[k].Imag = output[j].Imag - ti;

                output[j].Real += tr;
                output[j].Imag += ti;
            }
        }

        blockEnd = blockSize;

    }
    return TRUE;
}

const CArray<CFFT::SOutput>& CFFT::GetOutput() const
{
    return m_Output;
}

UInt32 CFFT::NumberOfBitsNeeded( UInt32 samples )
{
    Int32 i;

    if( samples < 2 )
    {
        return 0;
    }

    for ( i=0; ; i++ )
    {
        if( samples & (1 << i) ) 
            return i;
    }
}

Bool CFFT::IsPowerOfTwo( UInt32 n )
{
    if( n < 2 ) 
        return FALSE;

    if( n & (n-1) ) 
        return FALSE;

    return TRUE;
}
