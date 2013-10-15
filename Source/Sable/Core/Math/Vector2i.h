#ifndef _SABLE_CORE_MATH_VECTOR2I_
#define _SABLE_CORE_MATH_VECTOR2I_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\Math\Tuple.h>

namespace Sable
{

class CVector2f;
class CPersistentArchive;

/** 
\ingroup CoreMath
Vector 2. 
*/
class CVector2i : private STuple2i
{

public:

	/** @name Constructor/Destructor*/
    //@{
	CVector2i();
	CVector2i( const CVector2f& other );
    CVector2i( const CVector2i& other );
	CVector2i( Int32 px, Int32  py);
	~CVector2i();
    //@}

	/** @name Operator*/
    //@{
	CVector2i& operator=( const CVector2i& other );
	Bool operator==( const CVector2i& V ) const;
	Bool operator!=( const CVector2i& V ) const;

	CVector2i    operator-( ) const ;
	
    CVector2i    operator+( const CVector2i& v) const ;
	CVector2i    operator-( const CVector2i& v) const;
	CVector2i    operator*( const CVector2i& v) const ;
	CVector2i    operator/( const CVector2i& v) const ;
	CVector2f    operator/( const CVector2f& v) const ;
	
    CVector2i    operator-( const Int32 v) const ;
    CVector2i    operator*( const Int32 v) const ;
	CVector2i    operator/( const Int32 v) const ;
	
	CVector2i&   operator+=( const CVector2i& v);
	CVector2i&   operator-=( const CVector2i& v);
    CVector2i&   operator*=( const CVector2i& v);
	CVector2i&   operator/=( const CVector2i& v);
    //@}

	/** @name Accessors*/
    //@{
	Void	Set( const Int32 px, const Int32  py);

    Int32	GetX() const;
    Int32	GetY() const;
    Void    SetX( Int32 v );
    Void    SetY( Int32 v );
    //@}

	/** @name Manipulator*/
    //@{
	Float32	GetLength() const;
    Bool    Serialize( CPersistentArchive& ar );
    //@}

    /** @name Constants*/
    //@{
    static CVector2i Zero;
    //@}

};

}

#endif


