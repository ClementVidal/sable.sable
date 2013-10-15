#ifndef _SABLE_CORE_MATH_MATRIX3X3_
#define _SABLE_CORE_MATH_MATRIX3X3_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\Math\Tuple.h>
#include <Sable\Core\Math\Vector3f.h>
#include <Sable\Core\Math\Vector2f.h>
#include <Sable\Core\Math\Quaternion.h>
#include <Sable\Core\Math\EulerAngle.h>

namespace Sable
{

/** 
\ingroup CoreMath
Matrix. 
*/
class CMatrix3x3f : public STuple9f
{

public:

	/** @name Constructor/Destructor*/
    //@{
	CMatrix3x3f();
	CMatrix3x3f( const CMatrix3x3f& other );
	CMatrix3x3f( const CEulerAngle& ea );
	CMatrix3x3f( const CVector3f& xComponent, const CVector3f& yComponent, const CVector3f& zComponent );
	~CMatrix3x3f();
    //@}

	/** @name Operator*/
    //@{
	CMatrix3x3f&    operator=( const CMatrix3x3f& other );
	CMatrix3x3f	   operator*( const CMatrix3x3f& v) const;
    //@}

    /** @name Accessors*/
    //@{
	Void		SetXComponent( const CVector3f& vector );
	CVector3f&	GetXComponent() const;
	Void		SetYComponent( const CVector3f& vector );
	CVector3f&	GetYComponent() const;
	CVector3f&	GetZComponent() const;
	Void		SetZComponent( const CVector3f& vector );
    //@}

	/** @name Manipulator*/
    //@{
    Bool        Invert();
    Void        Transpose();
    Float32     GetDeterminant() const;
    Void        SetFromMultiplication( const CMatrix3x3f& M1, const CMatrix3x3f& M2 );
	Void		SetFromIdentity();
	Void		SetFromTranslation( const CVector2f& V);
    Void        SetFromTranslation( Float32 x, Float32 y );
	Void		SetFromScale( const CVector2f& vector );
	Void		SetFromAxisAndAngle( const CVector3f& Axe, Float32 Angle); 
	Void		SetFromAxisAndAngle( EAxis axis, Float32 angle );
	Void		SetFromQuaternion( const CQuaternion& quaternion ); 
	Void		SetFromEulerAngle( const CEulerAngle& angle ); 
	Void		SetFromLookAt( const CVector3f& pos, const CVector3f& target, const CVector3f& up );
    //@}


  
private:
  
};

}

#endif


