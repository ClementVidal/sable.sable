
template <typename DataType>
CTCBCurve<DataType>::CTCBCurve()
{

}

template <typename DataType>
CTCBCurve<DataType>::~CTCBCurve()
{

}

template<typename DataType>
Void CTCBCurve<DataType>::SetNodeCount( UInt32 count )
{
	m_NodeTable.SetItemCount( count );
}

template<typename DataType>
UInt32 CTCBCurve<DataType>::GetNodeCount( )const
{
	return 	m_NodeTable.GetItemCount();
}

template<typename DataType>
typename CTCBCurve<DataType>::Node& CTCBCurve<DataType>::GetNode( Index index ) const
{
	return m_NodeTable[ index ];
}

template<typename DataType>
Void CTCBCurve<DataType>::SetCapacity( UInt32 c )
{
	m_NodeTable.SetItemCount( c );
}

template<typename DataType>
UInt32 CTCBCurve<DataType>::GetCapacity() const
{
	return m_NodeTable.GetCapacity();
}

template<typename DataType>
Void CTCBCurve<DataType>::UpdateArcLengthParamerizationTable()
{
	UInt32 stepCount = m_ArcLengthReparametrizationTable.GetItemCount();
	if( stepCount == 0 )
		return;

	DataType a,b;

	a = EvaluteAt( 0.0f );
	Float32 len = 0.0f;
	m_ArcLengthReparametrizationTable[0].Set( 0.0f, 0.0f );
	for( UInt32 i=1; i<stepCount; i++ )
	{
		Float32 t = (Float32) i / ( stepCount - 1 );
		b = EvaluteAt( t );

		len = len + DataType( b-a ).GetLength();
		m_ArcLengthReparametrizationTable[i].Set( t, len );
		a = b;
	}

	// Normalize len
	for( UInt32 i=1; i<stepCount; i++ )
	{
		m_ArcLengthReparametrizationTable[i].SetSecond( m_ArcLengthReparametrizationTable[i].GetSecond() / len );
	}
}

template<typename DataType>
Float32 CTCBCurve<DataType>::GetArcLengthParameter( Float32 p ) const
{
	UInt32 stepCount = m_ArcLengthReparametrizationTable.GetItemCount();
	if( stepCount == 0 )
		return -1.0f;

	if( p == 0.0f || p == 1.0f)
		return p;

	for( UInt32 i=0; i<stepCount; i++ )
	{
		if( m_ArcLengthReparametrizationTable[i].GetSecond() > p )
		{
			CPair<Float32,Float32>& alA = m_ArcLengthReparametrizationTable[i-1];
			CPair<Float32,Float32>& alB = m_ArcLengthReparametrizationTable[i];

			Float32 t = ( p - alA.GetSecond() ) / ( alB.GetSecond() - alA.GetSecond() );
			return MathLerp( alA.GetFirst(), alB.GetFirst(), t );
		}
	}

	return -1.0f
}

template<typename DataType>
Void CTCBCurve<DataType>::SetArcLengthParametrizationTableSize( UInt32 c )
{
	DebugAssert( c >= 2 );
	m_ArcLengthReparametrizationTable.SetItemCount( c );
}

template<typename DataType>
Void CTCBCurve<DataType>::EvaluteAt( const Float32 globalT, DataType& position ) const
{
	DataType curTangent,  nextTangent;

	Float32 localT, segmentLength, oneMinusTension, oneMinusContinuity, onePlusContinuity, oneMinusBias, onePlusBias, oneMinusT;

	DataType* curPos;
	DataType* prevPos;
	DataType* nextPos;
	DataType* nextNextPos;

	Int32 segmentIndex, segmentCount;

	DebugAssert( m_NodeTable.GetItemCount() >= 2 );
	DebugAssert( globalT >= 0.0f );

	segmentCount = m_NodeTable.GetItemCount() - 1;
	segmentLength = ( 1.0f / segmentCount);

	segmentIndex = ( UInt32 ) ( globalT / segmentLength );

	if( globalT < 1.0f )
	{
		localT = ( globalT - ( segmentIndex * segmentLength ) ) / segmentLength ;
	}
	else
	{
		segmentIndex = segmentCount - 1;
		localT = 1.0f;
	}

	const SNode<DataType>& curKey = m_NodeTable[ segmentIndex  ];
	const SNode<DataType>& nextKey = m_NodeTable[ segmentIndex + 1 ];

	curPos = &m_NodeTable[ segmentIndex ].Value;
	nextPos = &m_NodeTable[ segmentIndex + 1 ].Value;

	if( segmentIndex == 0 )
	{
		prevPos = &m_NodeTable[ segmentIndex ].Value;
	}
	else
	{
		prevPos = &m_NodeTable[ segmentIndex - 1 ].Value;
	}

	if( segmentIndex == ( segmentCount - 1 ) )
	{
		nextNextPos = &m_NodeTable[ segmentIndex + 1 ].Value;
	}
	else
	{
		nextNextPos = &m_NodeTable[ segmentIndex + 2 ].Value;
	}

	oneMinusT = 1.0f - localT;

	// Compute tangent according to Kochanek–Bartels rules
	// http://en.wikipedia.org/wiki/Kochanek%E2%80%93Bartels_spline
	oneMinusTension = 1.0f - ( curKey.Tension * oneMinusT + nextKey.Tension * localT );
	oneMinusContinuity = 1.0f - ( curKey.Continuity * oneMinusT + nextKey.Continuity * localT );
	onePlusContinuity = 1.0f + ( curKey.Continuity * oneMinusT + nextKey.Continuity * localT );
	oneMinusBias = 1.0f - ( curKey.Bias * oneMinusT + nextKey.Bias * localT );
	onePlusBias = 1.0f + ( curKey.Bias * oneMinusT + nextKey.Bias * localT );

	curTangent =	( ( *nextPos - *curPos ) * oneMinusTension * oneMinusBias * oneMinusContinuity  ) +
					( ( *curPos - *prevPos ) * oneMinusTension * onePlusBias * onePlusContinuity );
	curTangent = curTangent * 0.5;

	nextTangent =	( ( *nextPos - *curPos ) * oneMinusTension * onePlusBias * onePlusContinuity ) + 
					( ( *nextNextPos - *nextPos ) * oneMinusTension * oneMinusBias * oneMinusContinuity );
	nextTangent = nextTangent * 0.5;

	// Compute position using hermite polynomial
	position =	*curPos * ( 2.0f*localT*localT*localT - 3.0f*localT*localT + 1.0f );
	position += *nextPos * ( -2.0f*localT*localT*localT + 3.0f*localT*localT );
	position += curTangent * ( localT*localT*localT - 2.0f*localT*localT + localT );
	position += nextTangent * ( localT*localT*localT - localT*localT );
				 
}

template<typename DataType>
DataType CTCBCurve<DataType>::EvaluteAt( Float32 t ) const
{
	DataType vector;

	EvaluteAt( t, vector );

	return vector;
}