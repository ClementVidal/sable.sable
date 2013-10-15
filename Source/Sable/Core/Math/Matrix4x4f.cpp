#include <Sable\Core\Math\Matrix4x4f.h>

#include <Sable\Core\Math\Matrix3x3f.h>
#include <Sable\Core\Math\Primitives.h>
#include <Sable\Core\Persistent\Archive.h>

#if defined( SETUP_IMPLTYPE_MSW )
#include <xmmintrin.h>
#endif

using namespace Sable;

CMatrix4x4f::CMatrix4x4f( )
{
}

CMatrix4x4f::CMatrix4x4f( const CMatrix3x3f& m, CVector3f& trs )
{
    SetFromIdentity();
    SetXComponent( m.GetXComponent() );
    SetYComponent( m.GetYComponent() );
    SetZComponent( m.GetZComponent() );
    SetTranslationComponent( trs );
}   

CMatrix4x4f::CMatrix4x4f( Float32 _11, Float32 _12, Float32 _13, Float32 _14, Float32 _21, Float32 _22, Float32 _23, Float32 _24, Float32 _31, Float32 _32, Float32 _33, Float32 _34, Float32 _41, Float32 _42, Float32 _43, Float32 _44 )
{
    this->_11 = _11;
    this->_12 = _12;
    this->_13 = _13;
    this->_14 = _14;
    this->_21 = _21;
    this->_22 = _22;
    this->_23 = _23;
    this->_24 = _24;
    this->_31 = _31;
    this->_32 = _32;
    this->_33 = _33;
    this->_34 = _34;
    this->_41 = _41;
    this->_42 = _42;
    this->_43 = _43;
    this->_44 = _44;
}

Bool CMatrix4x4f::operator==( const CMatrix4x4f& other )
{
    return  _11 == other._11 && _12 == other._12 && _13 == other._13 && _14 == other._14 &&
            _21 == other._21 && _22 == other._22 && _23 == other._23 && _24 == other._24 &&
            _31 == other._31 && _32 == other._32 && _33 == other._33 && _34 == other._34 &&
            _41 == other._41 && _42 == other._42 && _43 == other._43 && _44 == other._44;
}

Bool CMatrix4x4f::operator!=( const CMatrix4x4f& other )
{
    return ! (*this == other );
}

CMatrix4x4f& CMatrix4x4f::operator=( const CMatrix4x4f& other )
{
	MemoryCopy( (Void*) &other, this, sizeof( CMatrix4x4f ) );
	return *this;
}

Void CMatrix4x4f::SetXComponent( const CVector3f& vector )
{
	_11 = vector.GetX();
	_12 = vector.GetY();
	_13 = vector.GetZ();
}

CVector3f& CMatrix4x4f::GetXComponent() const
{
	return * (CVector3f*) &_11;
}

Void CMatrix4x4f::SetYComponent( const CVector3f& vector )
{
	_21 = vector.GetX();
	_22 = vector.GetY();
	_23 = vector.GetZ();
}

CVector3f& CMatrix4x4f::GetYComponent() const
{
	return * (CVector3f*) &_21;
}

Void CMatrix4x4f::SetZComponent( const CVector3f& vector )
{
	_31 = vector.GetX();
	_32 = vector.GetY();
	_33 = vector.GetZ();
}

CVector3f& CMatrix4x4f::GetZComponent() const
{
	return * (CVector3f*) &_31;
}

Void	CMatrix4x4f::SetTranslationComponent( const CVector3f& V )
{
     DebugAssert( MathIsValidFloat32( V.GetX() ) && MathIsValidFloat32( V.GetY() ) && MathIsValidFloat32( V.GetZ() ) );
	_41 = V.GetX();
	_42 = V.GetY();
	_43 = V.GetZ();
}

CMatrix3x3f CMatrix4x4f::GetRotationComponent( ) const
{
    CMatrix3x3f t;
    t.SetXComponent( GetXComponent() );
    t.SetYComponent( GetYComponent() );
    t.SetZComponent( GetZComponent() );

    return t;
}

Void CMatrix4x4f::SetRotationComponent( const CMatrix3x3f& v )
{
	SetXComponent( v.GetXComponent() );
	SetYComponent( v.GetYComponent() );
	SetZComponent( v.GetZComponent() );
}

const CVector3f& CMatrix4x4f::GetTranslationComponent() const
{
	return * (CVector3f*) &_41;
}

Void CMatrix4x4f::GetSubMatrix( CMatrix3x3f& result, const UInt8 i, const UInt8 j )
{
    switch (i*4+j)
    {
    // i == 0
    case 0:     // 0,0
        result._11 = _22; result._12 = _23; result._13 = _24;
        result._21 = _32; result._22 = _33; result._23 = _34;
        result._31 = _42; result._32 = _43; result._33 = _44;
        break;
    case 1:     // 0,1
        result._11 = _21; result._12 = _23; result._13 = _24;
        result._21 = _31; result._22 = _33; result._23 = _34;
        result._31 = _41; result._32 = _43; result._33 = _44;
        break;
    case 2:     // 0,2
        result._11 = _21; result._12 = _22; result._13 = _24;
        result._21 = _31; result._22 = _32; result._23 = _34;
        result._31 = _41; result._32 = _42; result._33 = _44;
        break;
    case 3:     // 0,3
        result._11 = _21; result._12 = _22; result._13 = _23;
        result._21 = _31; result._22 = _32; result._23 = _33;
        result._31 = _41; result._32 = _42; result._33 = _43;
        break;

    // i == 1
    case 4:     // 1,0
        result._11 = _12; result._12 = _13; result._13 = _14;
        result._21 = _32; result._22 = _33; result._23 = _34;
        result._31 = _42; result._32 = _43; result._33 = _44;
        break;
    case 5:     // 1,1
        result._11 = _11; result._12 = _13; result._13 = _14;
        result._21 = _31; result._22 = _33; result._23 = _34;
        result._31 = _41; result._32 = _43; result._33 = _44;
        break;
    case 6:     // 1,2
        result._11 = _11; result._12 = _12; result._13 = _14;
        result._21 = _31; result._22 = _32; result._23 = _34;
        result._31 = _41; result._32 = _42; result._33 = _44;
        break;
    case 7:     // 1,3
        result._11 = _11; result._12 = _12; result._13 = _13;
        result._21 = _31; result._22 = _32; result._23 = _33;
        result._31 = _41; result._32 = _42; result._33 = _43;
        break;

    // i == 2
    case 8:     // 2,0
        result._11 = _12; result._12 = _13; result._13 = _14;
        result._21 = _22; result._22 = _23; result._23 = _24;
        result._31 = _42; result._32 = _43; result._33 = _44;
        break;
    case 9:     // 2,1
        result._11 = _11; result._12 = _13; result._13 = _14;
        result._21 = _21; result._22 = _23; result._23 = _24;
        result._31 = _41; result._32 = _43; result._33 = _44;
        break;
    case 10:    // 2,2
        result._11 = _11; result._12 = _12; result._13 = _14;
        result._21 = _21; result._22 = _22; result._23 = _24;
        result._31 = _41; result._32 = _42; result._33 = _44;
        break;
    case 11:    // 2,3
        result._11 = _11; result._12 = _12; result._13 = _13;
        result._21 = _21; result._22 = _22; result._23 = _23;
        result._31 = _41; result._32 = _42; result._33 = _43;
        break;

    // i == 3
    case 12:    // 3,0
        result._11 = _12; result._12 = _13; result._13 = _14;
        result._21 = _22; result._22 = _23; result._23 = _24;
        result._31 = _32; result._32 = _33; result._33 = _34;
        break;
    case 13:    // 3,1
        result._11 = _11; result._12 = _13; result._13 = _14;
        result._21 = _21; result._22 = _23; result._23 = _24;
        result._31 = _31; result._32 = _33; result._33 = _34;
        break;
    case 14:    // 3,2
        result._11 = _11; result._12 = _12; result._13 = _14;
        result._21 = _21; result._22 = _22; result._23 = _24;
        result._31 = _31; result._32 = _32; result._33 = _34;
        break;
    case 15:    // 3,3
        result._11 = _11; result._12 = _12; result._13 = _13;
        result._21 = _21; result._22 = _22; result._23 = _23;
        result._31 = _31; result._32 = _32; result._33 = _33;
        break;
    }


}


Void   CMatrix4x4f::SetFromMultiplication( const CMatrix4x4f& M1, const CMatrix4x4f& M2 )
{
	CMatrix4x4f Tmp = *this;

#if defined( SETUP_IMPLTYPE_MSW )

	UInt8 i,j;
	__m128 a;
	CMatrix4x4f tmp = M2;
	CVector4f t;
	tmp.Transpose();

	for( i=0; i <4 ; i++ )
	{
		for( j=0; j <4 ; j++ )
		{
			a = _mm_mul_ps( _mm_loadu_ps( (Float32*)M1.m[i] ), _mm_loadu_ps( (Float32*)tmp.m[j] ) );
			_mm_storeu_ps( (Float32*) &t, a );
			Tmp.m[i][j] = t.GetSum();
		}
	}

#else

	Float32 Val;
	for(UInt8 i=0; i <4 ; i++)
	{
		for(UInt8 j=0; j <4 ; j++)
		{
			Val = 0;
			Val += M1.m[i][0] * M2.m[0][j];
			Val += M1.m[i][1] * M2.m[1][j];
			Val += M1.m[i][2] * M2.m[2][j];
			Val += M1.m[i][3] * M2.m[3][j];
			Tmp.m[i][j] = Val;
		}
	}

#endif

	*this = Tmp;
}

Void CMatrix4x4f::SetFromAxisAndAngle( EAxis axis, Float32 angle )
{
	CMatrix3x3f r;
	r.SetFromAxisAndAngle( axis, angle );
	SetFromIdentity();
	SetRotationComponent( r );
}

/**
Construct a rotation matrix from an axis and an angle given in Radian
*/
Void   CMatrix4x4f::SetFromAxisAndAngle( const CVector3f& axis, Float32 angle)
{
	CMatrix3x3f r;
	r.SetFromAxisAndAngle( axis, angle );
	SetFromIdentity();
	SetRotationComponent( r );

}

Void CMatrix4x4f::SetFromQuaternion( const CQuaternion& v )
{
	_41 = _42 = _43 = 0.0f;
	_14 = _24 = _34 = 0.0f;
	_44 = 1.0f;

	_11 = 1.0f - 2.0f * ( v.GetY() * v.GetY() + v.GetZ() * v.GetZ() );
	_12 = 2.0f * ( v.GetX() * v.GetY() + v.GetZ() * v.GetW() );
	_13 = 2.0f * ( v.GetX() * v.GetZ() - v.GetY() * v.GetW() );

	_21 = 2.0f * ( v.GetX() * v.GetY() - v.GetZ() * v.GetW() );
	_22 = 1.0f - 2.0f * ( v.GetX() * v.GetX() + v.GetZ() * v.GetZ() );
	_23 = 2.0f * ( v.GetY() * v.GetZ() + v.GetX() * v.GetW() );

	_31 = 2.0f * ( v.GetX() * v.GetZ() + v.GetY() * v.GetW() );
	_32 = 2.0f * ( v.GetY() * v.GetZ() - v.GetX() * v.GetW() );
	_33 = 1.0f - 2.0f * ( v.GetX() * v.GetX() + v.GetY() * v.GetY() );

/*
	Float32
		n = v.GetX() *v.GetX() + v.GetY() *v.GetY() + v.GetZ() *v.GetZ() + v.w*v.GetW();
	
	if ( n > 0.0f )
		n = 2.0f/n;
	else 
		n = 0.0;

	Float32
		x = v.GetX() *n,
		y = v.GetY() *n,
		z = v.GetZ() *n;

	Float32
		wX = v.w*x,
		wY = v.w*y,
		wZ = v.w*z,
		xX = v.GetX() *x,
		xY = v.GetX() *y,
		xZ = v.GetX() *z,
		yY = v.GetY() *y,
		yZ = v.GetY() *z,
		zZ = v.GetZ() *z;

	_41 = _42 = _43 = 0.0f;
	_14 = _24 = _34 = 0.0f;
	_44 = 1.0f;
	_11=1.0f-(yY+zZ)	;	_12=xY-wZ;			_13=xZ+wY;
	_21=xY+wZ;			_22=1.0f-(xX+zZ);	_23=yZ-wX;
	_31=xZ-wY;			_32=yZ+wX;			_33=1.0f-(xX+yY);
*/
}

/**
Build a matrix according to Euler angle rotation description.
This method use the following convention to factorize the final rotation matrix:
FinalM = RotationM( Euler.X ) * RotationM( Euler.Y ) * RotationM( Euler.Z ) 
Angles are given in Radian
*/
Void CMatrix4x4f::SetFromEulerAngle( const CEulerAngle& angle )
{
	Float32
		sx = MathSin( angle.GetPitch() ),
		cx = MathCos( angle.GetPitch() ),
		sy = MathSin( angle.GetYaw() ),
		cy = MathCos( angle.GetYaw() ),
		sz = MathSin( angle.GetRoll() ),
		cz = MathCos( angle.GetRoll() );

	_11 = cy*cz;				_12 = cy*sz;				_13 = sy;		_14 = 0.0f;
	_21 = cz*sx*sy - cx*sz;		_22 = cx*cz + sx*sy*sz;		_23 = -cy*sx;	_24 = 0.0f;
	_31 = -cx*cz*sy - sx*sz;	_32 = cz*sx - cx*sy*sz;		_33 = cx*cy;	_34 = 0.0f;
	_41 = 0.0f;					_42 = 0.0f;					_43 = 0.0f;		_44 = 1.0f;
}

Void	CMatrix4x4f::SetFromTranslation( const CVector3f& V )
{
    SetFromTranslation( V.GetX(), V.GetY(), V.GetZ() );
}

Void CMatrix4x4f::SetFromTranslation( Float32 x, Float32 y, Float32 z)
{
    DebugAssert( MathIsValidFloat32( x ) && MathIsValidFloat32( y ) && MathIsValidFloat32( z ) );

    _12 = _13 = _14 = 
	_21 = _23 = _24 = 
	_31 = _32 = _34 = 0.0f;
	
	_11 = _22 = _33 = _44 = 1.0f;

	_41 = x;
	_42 = y;
	_43 = z;
}

Void CMatrix4x4f::Transpose()
{
	CMatrix4x4f 
		Temp; 

	Temp.m[0][0] = m[0][0];
	Temp.m[0][1] = m[1][0];
	Temp.m[0][2] = m[2][0];
	Temp.m[0][3] = m[3][0];
	Temp.m[1][0] = m[0][1];
	Temp.m[1][1] = m[1][1];
	Temp.m[1][2] = m[2][1];
	Temp.m[1][3] = m[3][1];
	Temp.m[2][0] = m[0][2];
	Temp.m[2][1] = m[1][2];
	Temp.m[2][2] = m[2][2];
	Temp.m[2][3] = m[3][2];
	Temp.m[3][0] = m[0][3];
	Temp.m[3][1] = m[1][3];
	Temp.m[3][2] = m[2][3];
	Temp.m[3][3] = m[3][3];

	*this = Temp;
}

Void CMatrix4x4f::SetFromIdentity()
{
    m[0][1] = m[0][2] = m[0][3] = 
    m[1][0] = m[1][2] = m[1][3] = 
    m[2][0] = m[2][1] = m[2][3] = 
    m[3][0] = m[3][1] = m[3][2] = 0.0f;

    m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1.0f;
}

Float32 CMatrix4x4f::GetDeterminant()
{
	Float32   
		res = 0.0f, 
		det;

	Float32 
		in_3344_4334 = _33 * _44 - _43 * _34;
	Float32 
		in_3244_4234 = _32 * _44 - _42 * _34;
	Float32 
		in_3243_4233 = _32 * _43 - _42 * _33;
	Float32 
		in_3144_4134 = _31 * _44 - _41 * _34;
	Float32
		in_3143_4133 = _31 * _43 - _41 * _33;
	Float32 
		in_3142_4132 = _31 * _42 - _41 * _32;

    det = _22 * in_3344_4334 - _23 * in_3244_4234 + _24 * in_3243_4233;
    res += _11 * det;

    det = _21 * in_3344_4334 - _23 * in_3144_4134 + _24 * in_3143_4133;
    res -= _12 * det;

    det = _21 * in_3244_4234 - _22 * in_3144_4134 + _24 * in_3142_4132;
    res += _13 * det;

    det = _21 * in_3243_4233 - _22 * in_3143_4133 + _23 * in_3142_4132;
    res -= _14 * det;
	return res;
}

Void CMatrix4x4f::Invert()
{
	CMatrix4x4f TmpM = *this;
	TmpM.Transpose();

    Float32   mdet = TmpM.GetDeterminant();
    CMatrix3x3f   mtemp;

	if (MathAbs (mdet) < 0.0005f)
        SetFromIdentity();			//Cas ou il est impossible de calculer son inverse

    mdet = 1.0f / mdet;

	TmpM.GetSubMatrix(mtemp, 0,0 );
    _11 =  mtemp.GetDeterminant() * mdet;

	TmpM.GetSubMatrix(mtemp, 0,1 );
    _12 = -mtemp.GetDeterminant() * mdet;

	TmpM.GetSubMatrix(mtemp, 0,2 );
    _13 =  mtemp.GetDeterminant() * mdet;

	TmpM.GetSubMatrix(mtemp, 0,3 );
    _14 = -mtemp.GetDeterminant() * mdet;


	TmpM.GetSubMatrix(mtemp, 1,0 );
    _21 = -mtemp.GetDeterminant() * mdet;

	TmpM.GetSubMatrix(mtemp, 1,1 );
    _22 =  mtemp.GetDeterminant() * mdet;

	TmpM.GetSubMatrix(mtemp, 1,2 );
    _23 = -mtemp.GetDeterminant() * mdet;

	TmpM.GetSubMatrix(mtemp, 1,3 );
    _24 =  mtemp.GetDeterminant() * mdet;


	TmpM.GetSubMatrix(mtemp, 2,0 );
    _31 =  mtemp.GetDeterminant() * mdet;

	TmpM.GetSubMatrix(mtemp, 2,1 );
    _32 = -mtemp.GetDeterminant() * mdet;

	TmpM.GetSubMatrix(mtemp, 2,2 );
    _33 =  mtemp.GetDeterminant() * mdet;

	TmpM.GetSubMatrix(mtemp, 2,3 );
    _34 = -mtemp.GetDeterminant() * mdet;


	TmpM.GetSubMatrix(mtemp, 3,0 );
    _41 = -mtemp.GetDeterminant() * mdet;

	TmpM.GetSubMatrix(mtemp, 3,1 );
    _42 =  mtemp.GetDeterminant() * mdet;

	TmpM.GetSubMatrix(mtemp, 3,2 );
    _43 = -mtemp.GetDeterminant() * mdet;

	TmpM.GetSubMatrix(mtemp, 3,3 );
    _44 =  mtemp.GetDeterminant() * mdet;
}

Void CMatrix4x4f::SetFromScale( Float32 xyzScale )
{
	SetFromScale( CVector3f( xyzScale ) );
}

Void CMatrix4x4f::SetFromScale( const CVector3f& vector )
{
	_12 = _13 = _14 = 
	_21 = _23 = _24 = 
	_31 = _32 = _34 = 0.0f;

	_11 = vector.GetX();
	_22 = vector.GetY();
	_33 = vector.GetZ();
	_44 = 1.0f;

	_41 = 0;
	_42 = 0;
	_43 = 0;
}

/**
Construct a left hand perspective projection matrix using the following parameters:
\param fov Y Field of view in radian
\param aspect The aspect ration ( the Height divided by the width of the view volume )
\param zn Z near clip plane
\param zf Z far clip plane
*/
Void CMatrix4x4f::SetFromLHPerspProjectionValues( Float32 fov, Float32 aspect, Float32 zn, Float32 zf)
{
	MemoryFill(this, 0, sizeof(CMatrix4x4f) );

	Float32
		cotFov = MathCot( fov / 2.0f ),
		width = aspect * cotFov,
		height = 1.0f * cotFov,
		q = zf / ( zf - zn );

	_11 = width;
	_22 = height;
	_33 = q;
	_34 = 1.0f;
	_43 = -q*zn;

}

Void CMatrix4x4f::SetFromOrthoProjectionValues( Float32 width, Float32 height, Float32 zn, Float32 zf)
{
    Float32 l = -width/2;
    Float32 r = width/2;
    Float32 b = height/2;
    Float32 t = -height/2;

    SetFromOrthoProjectionValues( l, r, b, t, zn, zf );
}

Void CMatrix4x4f::SetFromOrthoProjectionValues( Float32 l, Float32 r, Float32 b, Float32 t, Float32 zn,  Float32 zf)
{
    MemoryFill(this, 0, sizeof(CMatrix4x4f) );

    _11 = 2.0f / ( r - l );
    _22 = 2.0f / ( b - t );
    _33 = 1.0f / ( zf-zn );
    _34 = zn / (zf-zn);


    _41 = ( l+r ) / ( l-r );
    _42 = ( b+t ) / ( t-b );
    _44 = 1.0f;
}


CMatrix4x4f CMatrix4x4f::operator * ( const CMatrix4x4f& v) const
{
	CMatrix4x4f m;
	m.SetFromMultiplication( *this, v );
	return m;
}

Bool CMatrix4x4f::Serialize( CPersistentArchive& ar )
{
	Int16 version = 0;
	Byte* buff = (Byte*)&m;

	if( ar.BeginScope( WT("Matrix4x4"), version ) == version )
	{
        ar.Serialize( _11, WT("_11"));
        ar.Serialize( _12, WT("_12"));
        ar.Serialize( _13, WT("_13"));
        ar.Serialize( _14, WT("_14"));

        ar.Serialize( _21, WT("_21"));
        ar.Serialize( _22, WT("_22"));
        ar.Serialize( _23, WT("_23"));
        ar.Serialize( _24, WT("_24"));

        ar.Serialize( _31, WT("_31"));
        ar.Serialize( _32, WT("_32"));
        ar.Serialize( _33, WT("_33"));
        ar.Serialize( _34, WT("_34"));

        ar.Serialize( _41, WT("_41"));
        ar.Serialize( _42, WT("_42"));
        ar.Serialize( _43, WT("_43"));
        ar.Serialize( _44, WT("_44"));

		ar.EndScope();
	}
	else
	{
		return FALSE;
	}

	return TRUE;
}

Void CMatrix4x4f::SetFromLookAt( const CVector3f& pos, const CVector3f& target, const CVector3f& up )
{
	CMatrix3x3f r;
	r.SetFromLookAt( pos, target, up );
	SetRotationComponent( r );
}


Void CMatrix4x4f::SetFromBasisAxis( const CVector3f& basisAxis, EAxis axis )
{
	CVector3f up, right, forward;
	forward = basisAxis;

	DebugAssert( axis == nAxis_Z );

	up = CVector3f::Axis[nAxis_Y];
	if( forward == up )
	{
		right = CVector3f::Axis[nAxis_X];
		up = CVector3f::Axis[nAxis_Z];
	}
	else
	{
		right.CrossProduct( up, basisAxis  );
		up.CrossProduct(  forward, right );
	}

	forward.Normalize();
	up.Normalize();
	right.Normalize();

	SetFromIdentity();
	SetXComponent( right );
	SetYComponent( up );
	SetZComponent( forward );
}

Void CMatrix4x4f::TranslateOverAxis( Float32 delta, EAxis axis )
{
	CVector3f comp;
	if( axis == nAxis_X)
		comp = GetXComponent();
	else if( axis == nAxis_Y)
		comp = GetYComponent();
	else if( axis == nAxis_Z)
		comp = GetZComponent();

	comp.Normalize();

	comp = comp * delta;

	SetTranslationComponent( GetTranslationComponent() + comp );
}