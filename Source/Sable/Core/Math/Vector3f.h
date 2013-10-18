#ifndef _CORE_MATH_VECTOR3_
#define _CORE_MATH_VECTOR3_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/Math/Tuple.h>


namespace Sable
{

class CPersistentArchive;
class CMatrix4x4f;

/** 
\ingroup CoreMath
Vector 3. 
*/
class CVector3f : private STuple3f
{

public:

	/** @name Constructor/Destructor*/
    //@{
	CVector3f();
	CVector3f( const CVector3f& other );
	CVector3f( const Float32 xyz );
	CVector3f( const Float32* xyz );
	CVector3f(const Float32 px, const Float32 py, const Float32 pz);
    //@}

	/** @name Operator*/
    //@{
	CVector3f&   operator=( const CVector3f& other );
	CVector3f    operator-( ) const ;

	CVector3f    operator+( const Float32 v) const ;
	CVector3f    operator-( const Float32 v) const ;
	CVector3f    operator*( const Float32 v) const ;
	CVector3f    operator/( const Float32 v) const ;

	CVector3f    operator+( const CVector3f& v) const ;
	CVector3f    operator-( const CVector3f& v) const;
	CVector3f    operator*( const CVector3f& v) const ;
	CVector3f    operator/( const CVector3f& v) const ;

	CVector3f&   operator+=( const Float32 v);
	CVector3f&   operator-=( const Float32 v);
    CVector3f&   operator*=( const Float32 v);
	CVector3f&   operator/=( const Float32 v);

	CVector3f&   operator+=( const CVector3f& v);
	CVector3f&   operator-=( const CVector3f& v);
    CVector3f&   operator*=( const CVector3f& v);
	CVector3f&   operator/=( const CVector3f& v);

    Bool        operator!=( const CVector3f& V ) const ;
	Bool        operator==( const CVector3f& V ) const ;

	Float32     operator[]( const UInt32 i ) const ;
    //@}

    /** @ Accessor*/
    //@{
    Float32 GetX() const;
    Float32 GetY() const;
    Float32 GetZ() const;
    Void	SetX( Float32 v );
    Void	SetY( Float32 v );
    Void	SetZ( Float32 v );
	Float32	GetSum() const;
    //@}

    /** @ Manipulator*/
    //@{
	Void	    Set( Float32 px, Float32 py, Float32 pz);
	Void	    Negate();
	Void	    Normalize();
	Float32	    DotProduct( const CVector3f& v) const ;	
    Float32     ScalarTripleProduct( const CVector3f& b, const CVector3f& c );
	CVector3f   CrossProduct( const CVector3f& v) const ;
	Void	    CrossProduct( const CVector3f& v1, const CVector3f& v2);	
	Void		SetFromReflectionVector( const CVector3f& input, const CVector3f& normal );
	CVector3f	LinearInterpolation( const CVector3f& q2, Float32 t);
	Void	    TransformPosition( const CMatrix4x4f& m );
	Void	    Transform(const CMatrix4x4f& m);
	Float32 	GetLength() const;
	CVector3f	Reflect(const CVector3f& n);
	Bool		IsNormalized( ) const;
    //@}

	/** @name Constants*/
	//@{
	static CVector3f Zero;
	static CVector3f XAxis;
	static CVector3f YAxis;
	static CVector3f ZAxis;
    static CVector3f Axis[];
	//@}

    Bool Serialize( CPersistentArchive& ar );

};

}

#endif


