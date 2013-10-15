#ifndef _SABLE_CORE_MATH_COMPLEX_
#define _SABLE_CORE_MATH_COMPLEX_

#include <Sable\Core\Common\DataTypes.h>

namespace Sable
{

/** 
\ingroup CoreMath
Complex number 
*/
class CComplex
{

public:

	/** @name Constructor/Destructor*/
    //@{
	CComplex();
    CComplex( const CComplex& other );
	CComplex( const Float32 px, const Float32  py);
	~CComplex();
    //@}

	/** @name Operator*/
    //@{
    CComplex    operator+( const CComplex& v) const ;
	CComplex    operator-( const CComplex& v) const;
	CComplex    operator*( const CComplex& v) const ;
    //@}

	/** @name Accessors*/
    //@{
	Void	Set( const Float32 r, const Float32  i);

    Float32 GetReal() const;
    Float32 GetImg() const;
    Void    SetReal( Float32 v );
    Void    SetImg( Float32 v );

	Float32 	GetLength() const;
    //@}

	/** @name Manipulator*/
    //@{
    //@}

private:

	// Attributes
	Float32	m_Real;
	Float32 m_Img;

};

}

#endif


