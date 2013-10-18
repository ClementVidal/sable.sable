#include <Sable/Core/Math/Matrix3x3f.h>

#include <Sable/Core/Math/Primitives.h>
#include <Sable/Core/Persistent/Archive.h>

using namespace Sable;

CMatrix3x3f::CMatrix3x3f()
{
}

CMatrix3x3f::CMatrix3x3f( const CEulerAngle& ea )
{
    SetFromEulerAngle( ea );
}

CMatrix3x3f::CMatrix3x3f( const CMatrix3x3f& other )
{
	_11 = other._11;
	_12 = other._12;
	_13 = other._13;

	_21 = other._21;
	_22 = other._22;
	_23 = other._23;

	_31 = other._31;
	_32 = other._32;
	_33 = other._33;
}

CMatrix3x3f::CMatrix3x3f( const CVector3f& xComponent, const CVector3f& yComponent, const CVector3f& zComponent )
{
	SetXComponent( xComponent );
	SetYComponent( yComponent );
	SetZComponent( zComponent );
}

CMatrix3x3f::~CMatrix3x3f()
{

}

CMatrix3x3f& CMatrix3x3f::operator=( const CMatrix3x3f& other )
{
	MemoryCopy( (Void*) &other, this, sizeof( CMatrix3x3f ) );
	return *this;
}


Void CMatrix3x3f::SetFromLookAt( const CVector3f& pos, const CVector3f& target, const CVector3f& up )
{
	CVector3f z = target - pos;
	z.Normalize();

	CVector3f x = up.CrossProduct( z );

	if( x.GetLength() == 0.0f )
	{
		x = CVector3f::XAxis;
	}
	else
	{
		x.Normalize();
	}

	CVector3f y = z.CrossProduct( x );
	DebugAssert( y.GetLength() != 0.0f );

	SetFromIdentity();

	SetXComponent( x );
	SetYComponent( y );
	SetZComponent( z );
}

Float32 CMatrix3x3f::GetDeterminant() const
{
	Float32 Det;

	Det = _11 * (_22 * _33 - _32 * _23)
		- _12 * (_21 * _33 - _31 * _23)
		+ _13 * (_21 * _32 - _31 * _22);

	return Det;
}

Void CMatrix3x3f::SetXComponent( const CVector3f& vector )
{
	_11 = vector.GetX();
	_12 = vector.GetY();
	_13 = vector.GetZ();
}

CVector3f& CMatrix3x3f::GetXComponent() const
{
	return * (CVector3f*) &_11;
}

Void CMatrix3x3f::SetYComponent( const CVector3f& vector )
{
	_21 = vector.GetX();
	_22 = vector.GetY();
	_23 = vector.GetZ();
}

CVector3f& CMatrix3x3f::GetYComponent() const
{
	return * (CVector3f*) &_21;
}

Void CMatrix3x3f::SetZComponent( const CVector3f& vector )
{
	_31 = vector.GetX();
	_32 = vector.GetY();
	_33 = vector.GetZ();
}

Bool CMatrix3x3f::Invert()
{
    Float32 d =  GetDeterminant();
    if( d == 0.0f )
        return FALSE;

    CMatrix3x3f adj;

    adj._11 = +(_22 * _33 - _23 * _32);
    adj._12 = -(_21 * _33 - _23 * _31);
    adj._13 = +(_21 * _32 - _22 * _31);

    adj._21 = -(_12 * _33 - _13 * _32);
    adj._22 = +(_11 * _33 - _13 * _31);
    adj._23 = -(_11 * _32 - _12 * _31);

    adj._31 = +(_12 * _23 - _13 * _22);
    adj._32 = -(_11 * _23 - _13 * _21);
    adj._33 = +(_11 * _22 - _12 * _21);

    adj.Transpose();

    _11 = adj._11 / d;
    _12 = adj._12 / d;
    _13 = adj._13 / d;
          
    _21 = adj._21 / d;
    _22 = adj._22 / d;
    _23 = adj._23 / d;
          
    _31 = adj._31 / d;
    _32 = adj._32 / d;
    _33 = adj._33 / d;


    return TRUE;
}

Void CMatrix3x3f::Transpose()
{
	CMatrix3x3f 
		Temp; 

	Temp.m[0][0] = m[0][0];
	Temp.m[0][1] = m[1][0];
	Temp.m[0][2] = m[2][0];
	Temp.m[1][0] = m[0][1];
	Temp.m[1][1] = m[1][1];
	Temp.m[1][2] = m[2][1];
	Temp.m[2][0] = m[0][2];
	Temp.m[2][1] = m[1][2];
	Temp.m[2][2] = m[2][2];

	*this = Temp;
}

CVector3f& CMatrix3x3f::GetZComponent() const
{
	return * (CVector3f*) &_31;
}

Void CMatrix3x3f::SetFromIdentity()
{
    m[0][1] = m[0][2] = 
    m[1][0] = m[1][2] = 
    m[2][0] = m[2][1] = 0.0f;

    m[0][0] = m[1][1] = m[2][2] = 1.0f;
}

CMatrix3x3f CMatrix3x3f::operator * ( const CMatrix3x3f& v) const
{
	CMatrix3x3f m;
	m.SetFromMultiplication( *this, v );
	return m;
}


Void   CMatrix3x3f::SetFromMultiplication( const CMatrix3x3f& M1, const CMatrix3x3f& M2 )
{
	CMatrix3x3f Tmp = *this;

	Float32 Val;
	for(UInt8 i=0; i <3 ; i++)
	{
		for(UInt8 j=0; j <3 ; j++)
		{
			Val = 0;
			Val += M1.m[i][0] * M2.m[0][j];
			Val += M1.m[i][1] * M2.m[1][j];
			Val += M1.m[i][2] * M2.m[2][j];

			Tmp.m[i][j] = Val;
		}
	}

	*this = Tmp;
}


Void CMatrix3x3f::SetFromTranslation( const CVector2f& V)
{
    SetFromTranslation( V.GetX(), V.GetY() );
}

Void CMatrix3x3f::SetFromScale( const CVector2f& vector )
{
	_12 = _13 = 
	_21 = _23= 0.0f;

	_11 = vector.GetX();
	_22 = vector.GetY();
	_33 = 1.0f;

	_31 = 0;
	_32 = 0;
}

Void CMatrix3x3f::SetFromTranslation( Float32 x, Float32 y )
{
    DebugAssert( MathIsValidFloat32( x ) && MathIsValidFloat32( y ) );

    _12 = _13 = 
	_21 = _23= 
	_31 = _32= 0.0f;
	
	_11 = _22 = _33 = 1.0f;

	_31 = x;
	_32 = y;
}

Void CMatrix3x3f::SetFromAxisAndAngle( EAxis axis, Float32 angle )
{
	Float32 cosA = MathCos( angle );
	Float32 sinA = MathSin( angle );

	if( axis == nAxis_X )
	{
		_11 = 1.0f      ;_12 = 0.0f				;_13 = 0.0f;
		_21 = 0.0f		;_22 = cosA				;_23 = sinA;
		_31 = 0.0f		;_32 = -sinA			;_33 = cosA;
	}
	else if( axis == nAxis_Y )
	{
		_11 = cosA      ;_12 = 0.0f				;_13 = -sinA;
		_21 = 0.0f		;_22 = 1.0f				;_23 = 0.0f;
		_31 = sinA		;_32 = 0.0f				;_33 = cosA;
	}
	else if( axis == nAxis_Z )
	{
		_11 = cosA      ;_12 = sinA				;_13 = 0.0f;
		_21 = -sinA		;_22 = cosA				;_23 = 0.0f;
		_31 = 0.0f		;_32 = 0.0f				;_33 = 1.0f;
	}
}

Void CMatrix3x3f::SetFromAxisAndAngle( const CVector3f& Axe, Float32 Angle)
{
    CVector3f    normalizedaxe = Axe;
    normalizedaxe.Normalize();

    Float32 
        c = (Float32) MathCos(Angle) , 
        s = (Float32) MathSin(Angle) , 
        t = 1.0f - c,
        x =  normalizedaxe.GetX(),
        y =  normalizedaxe.GetY(),
        z =  normalizedaxe.GetZ();


    _11 = t*x*x+c       ;_12 = t*x*y - z*s          ;_13 = t*x*z + y*s;
    _21 = t*x*y + z*s   ;_22 = t*y*y +c             ;_23 = t*y*z - x*s;
    _31 = t*x*z - y*s   ;_32 = t*y*z + x*s          ;_33 = t*z*z + c;
}

Void CMatrix3x3f::SetFromQuaternion( const CQuaternion& v )
{
    _11 = 1.0f - 2.0f * ( v.GetY() * v.GetY() + v.GetZ() * v.GetZ() );
    _12 = 2.0f * ( v.GetX() * v.GetY() + v.GetZ() * v.GetW() );
    _13 = 2.0f * ( v.GetX() * v.GetZ() - v.GetY() * v.GetW() );

    _21 = 2.0f * ( v.GetX() * v.GetY() - v.GetZ() * v.GetW() );
    _22 = 1.0f - 2.0f * ( v.GetX() * v.GetX() + v.GetZ() * v.GetZ() );
    _23 = 2.0f * ( v.GetY() * v.GetZ() + v.GetX() * v.GetW() );

    _31 = 2.0f * ( v.GetX() * v.GetZ() + v.GetY() * v.GetW() );
    _32 = 2.0f * ( v.GetY() * v.GetZ() - v.GetX() * v.GetW() );
    _33 = 1.0f - 2.0f * ( v.GetX() * v.GetX() + v.GetY() * v.GetY() );
} 

/**
Build a matrix according to Euler angle rotation description.
This method use the following convention to factorize the final rotation matrix:
FinalM = RotationM( Euler.X ) * RotationM( Euler.Y ) * RotationM( Euler.Z ) 
Angles are given in Radian
*/
Void CMatrix3x3f::SetFromEulerAngle( const CEulerAngle& angle )
{
	CMatrix3x3f a,b,c;
	a.SetFromAxisAndAngle( nAxis_Y, angle.GetYaw() );
	b.SetFromAxisAndAngle( nAxis_Z, angle.GetRoll() );
	c.SetFromAxisAndAngle( nAxis_X, angle.GetPitch() );

	*this = a*b*c;
}
