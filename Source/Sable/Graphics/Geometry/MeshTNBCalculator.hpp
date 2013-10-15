
template< class InputProxy>
CGeometryMeshTNBCalculator<InputProxy>::CGeometryMeshTNBCalculator( )
{

}

template< class InputProxy>
CGeometryMeshTNBCalculator<InputProxy>::~CGeometryMeshTNBCalculator()
{

}

template <class InputProxy> 
Void CGeometryMeshTNBCalculator<InputProxy>::GetBase( const UInt32 index, CVector3f& outU, CVector3f& outV, CVector3f& outN ) const
{
	CMatrix3x3f
		& base = m_BaseTable[index];

	outU = base.GetXComponent();
	outV = base.GetYComponent();
	outN = base.GetZComponent();
}

template <class InputProxy> 
UInt32 CGeometryMeshTNBCalculator<InputProxy>::GetBaseCount() const
{
	return m_BaseTable.GetItemCount();
}


template <class InputProxy>
Void CGeometryMeshTNBCalculator<InputProxy>::GetTriangleBaseIndices( const UInt32 index, UInt32 outdwBase[3] ) const
{
	STriBaseIndex 
		& indx = m_TriBaseAssigment[index];

	for( UInt32 i=0;i<3;i++)
		outdwBase[i]=indx.p[i];
}

template< class InputProxy>
Void CGeometryMeshTNBCalculator<InputProxy>::Calculate( const InputProxy& input )
{
	UInt32
		triangleCount = input.GetTriangleCount();
	Bool 
		textureCoordinateBroken = FALSE;
	CArray<CMatrix3x3f>
		triangleBaseTable;
	UInt32
		index;
	BaseMap
		baseMap;
	 
	triangleBaseTable.SetItemCount( triangleCount );
	m_TriBaseAssigment.SetItemCount( triangleCount );
	m_BaseTable.SetItemCount( triangleCount * 3 );
	m_UsedBaseCount = 0;

	// calculate the base vectors per triangle -------------------------------------------
	{
		for( index = 0; index < triangleCount; index++ )
		{
			UInt32
				e;

			// get data from caller ---------------------------
			UInt32 
				positionIndex[3],
				normalIndex[3],
				UVIndex[3];

			input.GetTriangleIndices( index ,positionIndex,normalIndex ,UVIndex );

			CVector3f 
				position[3];
			CVector2f 
				TexCoord0[3];

			for( e = 0; e < 3; e++ )
			{
				input.GetPosition( positionIndex[e],position[e]);
				input.GetUV( UVIndex[e],TexCoord0[e]);
			}

			// calculate tangent vectors ---------------------------

			CVector3f 
				vA=position[1]-position[0];
			CVector3f
				vB=position[2]-position[0];

			CVector2f
				delta1 = TexCoord0[1] - TexCoord0[0];
			CVector2f
				delta2 = TexCoord0[2] - TexCoord0[0];

			Float32 
				div	= ( delta1.GetX() * delta2.GetY() - delta2.GetX() * delta1.GetY() );
	
			CVector3f
				vU,
				vV,
				vN = vA.CrossProduct( vB );

			vN.Normalize();

			if( div != 0.0 )
			{
				//	2D triangle area = (u1*v2-u2*v1)/2
				// weight the tangent vectors by the TexCoord0 triangles area size (fix problems with base TexCoord0 assignment)
				Float32 
					areaMulTwo = MathAbs( div );

				Float32 
					a = delta2.GetY() /div;
				Float32 
					b = -delta1.GetY() /div;
				Float32 
					c = -delta2.GetX() /div;
				Float32 
					d = delta1.GetX() /div;

				vU = ( vA * a + vB * b );
				vU.Normalize();
				vU = vU * areaMulTwo;

				vV = ( vA * c + vB * d );
				vV.Normalize();
				vV = vV * areaMulTwo;
			}
			else
			{
				vU = CVector3f(1,0,0);
				vV = CVector3f(0,1,0);
			}

			triangleBaseTable[ index ] = CMatrix3x3f( vU, vV, vN );
		}
	}

	// distribute the normals to the vertices
	{
		// we create a NEW tangent base for every vertex index that has a different normal (later we split further for mirrored use)
		// and sum the base vectors (weighted by angle and mirrored if necessary)
		for( index = 0; index < triangleCount; index++ )
		{
			UInt32
				e;

			UInt32 
				positionIndex[3],
				normalIndex[3],
				UVIndex[3];

			input.GetTriangleIndices( index,positionIndex,normalIndex,UVIndex);

			CMatrix3x3f
				triangleBase; 
			CVector3f
				position[3];

			triangleBase = triangleBaseTable[ index ];

			for( e = 0; e < 3; e++ ) 
				input.GetPosition( positionIndex[e], position[e] );

			// for each triangle corner
			for( e = 0; e < 3; e++ )	
			{
				Float32
					weight;
				
				weight = CalculateAngleBetween(
							position[(e+2)%3]-position[e],
							position[(e+1)%3]-position[e] );			// weight by angle to fix the L-Shape problem

				if( weight <= 0.0f )
					weight=0.0001f;

                DebugAssert( MathIsValidFloat32( weight ) );

				AddNormalToBase(
					baseMap,
					positionIndex[e],
					normalIndex[e],
					triangleBase.GetZComponent() * weight
					);
			}
		}
	}

	// distribute the uv vectors to the vertices
	{
		// we create a NEW tangent base for every vertex index that has a different normal
		// if the base vectors does'nt fit we split as well
		for( index = 0; index < triangleCount ;index++)
		{
			UInt32
				e;
			STriBaseIndex
				triangleBaseIndex;

			// get data from caller ---------------------------
			UInt32 
				positionIndex[3],
				normalIndex[3],
				UVIndex[3];

			input.GetTriangleIndices( index,positionIndex,normalIndex,UVIndex);

			
			CMatrix3x3f
				trianbleBase = triangleBaseTable[ index ];
			CVector3f
				position[3],
				temp;

			for(e=0;e<3;e++) 
				input.GetPosition( positionIndex[e], position[e] );

			temp = trianbleBase.GetZComponent();
			temp.Normalize();

			// for each triangle corner
			for(e=0;e<3;e++)	
			{
				Float32
					weight = CalculateAngleBetween(
					position[(e+2)%3]-position[e],
					position[(e+1)%3]-position[e] 
					);			// weight by angle to fix the L-Shape problem

	

				triangleBaseIndex.p[e] = AddUVToBase(
					baseMap,
					positionIndex[e],
					normalIndex[e],
					trianbleBase.GetXComponent() * weight,
					trianbleBase.GetYComponent() * weight,
					temp
					);
			}

			m_TriBaseAssigment[ index ] = triangleBaseIndex;
		}
	}

	// adjust the base vectors per vertex -------------------------------------------
	{
		for( index = 0; index < m_UsedBaseCount; index ++ )
		{
			CMatrix3x3f
				&ref= m_BaseTable[ index ];

			CVector3f
				& n = ref.GetZComponent();
			CVector3f
				& u = ref.GetXComponent();
			CVector3f
				& v = ref.GetYComponent();

			// rotate u and v in n plane

			CVector3f 
				vUout,
				vVout,
				vNout;

			vNout = n;
			vNout.Normalize();

			vUout = u - vNout * (vNout.GetX()*u.GetX() + vNout.GetY()*u.GetY() + vNout.GetZ()*u.GetZ());
			vVout = v - vNout * (vNout.GetX()*v.GetX() + vNout.GetY()*v.GetY() + vNout.GetZ()*v.GetZ());

			vUout.Normalize();
			vVout.Normalize();

			ref.SetXComponent( vUout );
			ref.SetYComponent( vVout );
			ref.SetZComponent( vNout );
		
		}
	}
}

template< class InputProxy >
UInt32 CGeometryMeshTNBCalculator<InputProxy>::AddUVToBase( 
	BaseMap& baseMap, 
	UInt32 positionIndex, 
	UInt32 normalIndex,
	const CVector3f &U, 
	const CVector3f &V, 
	const CVector3f &normal )
{
	SBaseIndex 
		key;

	key.PositionIndex = positionIndex;
	key.NormalIndex = normalIndex;

/*	CVector3f 
		vNormal = m_BaseVectors[ baseMap.GetItem( key ) ].GetZComponent();
*/
	UInt32
		baseUVIndex = baseMap.GetItem( key ); // 0xffffffff													// init with not found

/*	bool bParity=(cross(inU,inV)*inNormN>0.0f);

	for(;iFind!=iFindEnd;++iFind)
	{
		CBase33 &refFound=m_BaseVectors[(*iFind).second];

		if(!IsZero(refFound.u)) 
		{
			bool bParityRef=(cross(refFound.u,refFound.v)*refFound.n>0.0f);
			bool bParityCheck=(bParityRef==bParity);

			if(!bParityCheck)
				continue;

			CVec3 vrefUV = refFound.u+refFound.v;

			// project down to the plane (plane normal = inNormN)
			CVec3 vRotHalf = vrefUV - inNormN*(inNormN*vrefUV);

			//			bool bHalfAngleCheck=normalize(inU+inV) * normalize(vRotHalf) > cos(fThreshold);
			bool bHalfAngleCheck = (inU+inV) * vRotHalf > 0.0f;		// length doesn't matter so normalize is not needed

			if(!bHalfAngleCheck)
				continue;
		}

		dwBaseUVIndex=(*iFind).second;break;
	}

	if(dwBaseUVIndex==0xffffffff)														// not found
	{	
		// otherwise create a NEW base

		CBase33 Base( CVec3(0,0,0), CVec3(0,0,0), vNormal );

		dwBaseUVIndex = m_BaseVectors.size();

		inMap.insert( std::pair<CBaseIndex,unsigned int>(Indx,dwBaseUVIndex) );
		m_BaseVectors.push_back(Base);
	}
*/
	CMatrix3x3f
		&refBaseUV = m_BaseTable[baseUVIndex];

	refBaseUV.SetXComponent( refBaseUV.GetXComponent() + U );
	refBaseUV.SetYComponent( refBaseUV.GetYComponent() + V );


	return baseUVIndex;
}

template< class InputProxy >
Void CGeometryMeshTNBCalculator<InputProxy>::AddNormalToBase( 
	BaseMap& basemMap, 
	UInt32 positionIndex, 
	UInt32 normalIndex, 
	const CVector3f& normal 
	)
{
	SBaseIndex baseIndex;
	typename BaseMap::Iterator iterator;
	UInt32 baseNIndex;

	baseIndex.PositionIndex = positionIndex;
	baseIndex.NormalIndex = normalIndex;


	if( basemMap.HasItem( baseIndex ) )	// found
	{
		// resuse the existing one
		baseNIndex= basemMap.GetItem( baseIndex );
	}
	else
	{
		// otherwise create a NEW base

		CMatrix3x3f 
			base( CVector3f(0,0,0), CVector3f(0,0,0), CVector3f(0,0,0) );

		baseNIndex = m_UsedBaseCount;
		basemMap.AddItem( baseIndex, baseNIndex );

		m_BaseTable[ m_UsedBaseCount ] = base;
		m_UsedBaseCount++;
	}

	CMatrix3x3f 
		& refBaseN=m_BaseTable[ baseNIndex ];

	refBaseN.SetZComponent( refBaseN.GetZComponent() + normal );
}

template< class InputProxy >
Bool CGeometryMeshTNBCalculator<InputProxy>::SBaseIndex::operator==( const SBaseIndex& other ) const
{
	if( ( PositionIndex == other.PositionIndex) && (NormalIndex == other.NormalIndex) )
		return TRUE;

	return FALSE;
}

template< class InputProxy >
Bool CGeometryMeshTNBCalculator<InputProxy>::SBaseIndex::operator<( const SBaseIndex& other ) const
{
	if(PositionIndex<other.PositionIndex)
		return TRUE;
	if(PositionIndex>other.PositionIndex)
		return FALSE;

	// then by normal
	if(NormalIndex<other.NormalIndex)
		return TRUE;
	if(NormalIndex>other.NormalIndex)
		return FALSE;

	return FALSE;
}

template< class InputProxy >
Float32 CGeometryMeshTNBCalculator<InputProxy>::CalculateAngleBetween( const CVector3f& invA, const CVector3f&invB )
{
	Float32 
		lenghtQ = invA.GetLength() * invB.GetLength();

	if(lenghtQ<0.0001f)
		lenghtQ=0.0001f;// to prevent division by zero

	Float32 
		f= invA.DotProduct( invB ) / lenghtQ;

	if( f > 1.0f ) 
		f = 1.0f;		// acos need input in the range [-1..1]
	else if( f < -1.0f )
		f = -1.0f;		//

	Float32 
		returnValue =( Float32 )MathArcCos(f);// cosf is not avaiable on every plattform

	return returnValue;
}
