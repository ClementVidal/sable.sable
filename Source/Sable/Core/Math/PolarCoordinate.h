#ifndef _SABLE_CORE_MATH_POLARCOORDINATE_
#define _SABLE_CORE_MATH_POLARCOORDINATE_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\Math\Tuple.h>
#include <Sable\Core\Math\Vector3f.h>

namespace Sable
{

/** 
\ingroup CoreMath
CPolarCoordinate. 
*/
class CPolarCoordinate : private STuple3f
{

public:

	/** @name Constructor/Destructor*/
    //@{
	CPolarCoordinate();
	CPolarCoordinate( const CVector3f& other );
	CPolarCoordinate( Float32 azimuth, Float32 zenith, Float32 radius = 1.0f );
    //@}

	/** @name Operator*/
	//@{
	CPolarCoordinate    operator+( const CPolarCoordinate& v) const;
	CPolarCoordinate&   operator+=( const CPolarCoordinate& v);
    //@}

    /** @name Accessor*/
    //@{
	CVector3f	ConvertToCartesianCoordinate() const;
    Float32		GetAzimuth() const;
    Float32		GetZenith() const;
	Float32		GetRadius() const;
    //@}

    /** @name Manipulator*/
	//@{
	Void		Normalize();
	Void	    SetFromCartesianCoordinate( const CVector3f& vector );
	Void	    Set( Float32 azimuth, Float32 zenith, Float32 radius = 1.0f );
    //@}

private:

};

}

#endif


