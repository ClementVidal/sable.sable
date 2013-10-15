

template <class DataType>
CRange<DataType>::CRange()
{
}

template <class DataType>
CRange<DataType>::CRange(const DataType& v )
{
	m_LowValue = v;
	m_HighValue = v;
}

template <class DataType>
Void CRange<DataType>::Expand( const DataType& d )
{
	m_LowValue -= d;
	m_HighValue += d;
}

template <class DataType>
CRange<DataType>::CRange(const DataType& low, const DataType& high)
{
	m_LowValue = low;
	m_HighValue = high;
    DebugAssert( m_LowValue <= m_HighValue );
}

template <class DataType>
CRange<DataType>::CRange( const CRange<DataType>& other)
{
	m_LowValue = other.m_LowValue;
	m_HighValue = other.m_HighValue;
}

template <class DataType>
CRange<DataType>::~CRange()
{

}


template <class DataType>
DataType CRange<DataType>::Clamp( const DataType& d )
{
	if( d < m_LowValue )
		return m_LowValue;

	if( m_HighValue < d )
		return m_HighValue;

	return d;
}

template <class DataType>
Bool CRange<DataType>::Serialize( CPersistentArchive& ar )
{
	if( ar.Serialize( m_LowValue, WT("Min") ) )
	{
		if( ar.Serialize( m_HighValue, WT("Max") ) )
		{
			return TRUE;
		}
	}
	
	return FALSE;
}

template <class DataType>
CRange<DataType>& CRange<DataType>::operator=( const CRange<DataType>& other )
{
	m_LowValue = other.m_LowValue;
	m_HighValue = other.m_HighValue;
	return *this;
}

template <class DataType>
DataType CRange<DataType>::GetLinearInterpolationValue( const Float32 t ) const
{
	return m_LowValue * ( 1.0f - t ) + m_HighValue * ( t );
}

/**
Get the delta value between HighValue and LowValue
\n return m_HighValue - m_LowValue
*/
template <class DataType>
DataType CRange<DataType>::GetDeltaValue( ) const 
{ 
	return m_HighValue - m_LowValue; 
}

template <class DataType>
Void  CRange<DataType>::SetValues( const DataType& lowValue, const DataType& highValue ) 
{
	m_LowValue = lowValue;
	m_HighValue = highValue;
    DebugAssert( m_LowValue <= m_HighValue );
}

/**
Compute a random value in the specified range.
\param randomGen A pseudo random number generator used to compute the initial random value
\return The random value in range
*/
template <class DataType>
DataType CRange<DataType>::GetRandomValueInRange(CRandom& randomGen)const
{
	return m_LowValue + GetDeltaValue() * randomGen.GetRandomNumber(0.0f, 1.0f) ;
}

/**
Compute a random value in the specified range. ( this version use the default rendom generator )
\param randomGen A pseudo random number generator used to compute the initial random value
\return The random value in range
*/
template <class DataType>
DataType CRange<DataType>::GetRandomValueInRange()const
{
	return m_LowValue + GetDeltaValue() * CoreManager.GetRandomGenerator().GetRandomNumber(0.0f, 1.0f) ;
}

/**
Return a coeficient that represent where the given value is located 
inbetween the two bound. ( For Float32 type, this coeficient range betwen 0 and 1 )
*/
template <class DataType>
DataType CRange<DataType>::GetNormalizedCoeficient( const DataType& value ) const
{
    DataType t = ( value - m_LowValue ) / ( m_HighValue - m_LowValue );

    return t;
}