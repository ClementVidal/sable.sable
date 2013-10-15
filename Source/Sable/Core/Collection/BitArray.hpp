template< UInt32 BitCount >
CBitArray<BitCount>::CBitArray()
{
	Clear();
}

template< UInt32 BitCount >
CBitArray<BitCount>::CBitArray( const CBitArray<BitCount>& other )
{
	for( Int32 i=0;i<ByteCount; i++ )
	{
		m_Value[i] = other.m_Value[i];
	}
}

template< UInt32 BitCount >
Bool CBitArray<BitCount>::operator ==( const CBitArray<BitCount>& other )
{
	for( Int32 i=0;i<ByteCount; i++ )
	{
		if( m_Value[i] != other.m_Value[i] )
			return FALSE;
	}

	return TRUE;
}

template< UInt32 BitCount >
Void CBitArray<BitCount>::SetBit( UInt32 bit, Bool value )
{
	if( value )
	{
		SetBit( bit );
	}
	else
	{
		ClearBit( bit );
	}
}

template< UInt32 BitCount >
CBitArray<BitCount>& CBitArray<BitCount>::operator=( const CBitArray<BitCount>& other )
{
	for( Int32 i=0;i<ByteCount; i++ )
	{
		m_Value[i] = other.m_Value[i];
	}
	return *this;
}

template< UInt32 BitCount >
CBitArray<BitCount>::~CBitArray()
{
}

template< UInt32 BitCount >
Void CBitArray<BitCount>::SetBit( UInt32 bit )
{
	m_Value[ bit / 8 ] |= ( 1 << (bit%8) );
}

template< UInt32 BitCount >
Void CBitArray<BitCount>::ClearBit( UInt32 bit )
{
	m_Value[ bit / 8 ] &= ( ~( 1 << (bit%8) ) );
}

template< UInt32 BitCount >
Bool CBitArray<BitCount>::GetBit( UInt32 bit ) const
{
    return ( m_Value[ bit / 8 ] & ( 1 << (bit%8) ) ) ? TRUE : FALSE;
}

template< UInt32 BitCount >
Void CBitArray<BitCount>::Clear()
{
	for( Int32 i=0;i<ByteCount; i++ )
	{
		m_Value[i] = 0;
	}
}

template< UInt32 BitCount >
Bool CBitArray<BitCount>::Serialize( CPersistentArchive& ar )
{
	return ar.Serialize( (Byte*)m_Value, ByteCount, WT("Value") );
}