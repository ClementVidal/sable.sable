#ifndef _SABLE_CORE_MATH_MATRIX_
#define _SABLE_CORE_MATH_MATRIX_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/Math/Tuple.h>
#include <Sable/Core/Math/Vector3f.h>
#include <Sable/Core/Math/Vector4f.h>
#include <Sable/Core/Math/Quaternion.h>
#include <Sable/Core/Math/EulerAngle.h>

namespace Sable
{

class CPersistentArchive;
class CVector3f;
class CVector4f;
class CMatrix3x3f;

/** 
\ingroup CoreMath
Matrix. 
*/
class CMatrix4x4f : public STuple16f
{

public:

	/** @name Constructor/Destructor*/
    //@{
    CMatrix4x4f();
    CMatrix4x4f( const CMatrix3x3f& m, CVector3f& trs );
    CMatrix4x4f( Float32 _11, Float32 _12, Float32 _13, Float32 _14, 
                Float32 _21, Float32 _22, Float32 _23, Float32 _24, 
                Float32 _31, Float32 _32, Float32 _33, Float32 _34, 
                Float32 _41, Float32 _42, Float32 _43, Float32 _44 );
    //@}

	/** @name Operator*/
    //@{
	Bool           operator!=( const CMatrix4x4f& other );
	Bool           operator==( const CMatrix4x4f& other );
	CMatrix4x4f&    operator=( const CMatrix4x4f& other );
	CMatrix4x4f	   operator*( const CMatrix4x4f& v) const;
    //@}

    /** @name Accessors*/
    //@{
	Void				SetXComponent( const CVector3f& vector );
	CVector3f&			GetXComponent() const;
	Void				SetYComponent( const CVector3f& vector );
	CVector3f&			GetYComponent() const;
	CVector3f&			GetZComponent() const;
	Void				SetZComponent( const CVector3f& vector );
	const CVector3f&	GetTranslationComponent() const;
	Void				SetTranslationComponent( const CVector3f& v );
	Void				SetRotationComponent( const CMatrix3x3f& v );
	CMatrix3x3f			GetRotationComponent( ) const;
    //@}

	/** @name Manipulator*/
    //@{
	Void		Invert();
	Void		Transpose();	
	Void		SetFromIdentity();
    Void		SetFromMultiplication( const CMatrix4x4f& M1, const CMatrix4x4f& M2 );
	Void		SetFromScale( const CVector3f& vector );
	Void		SetFromScale( Float32 xyzScale );
	Void		SetFromTranslation( const CVector3f& V);
	Void		SetFromTranslation( Float32 x, Float32 y, Float32 z);
	Void		SetFromLHPerspProjectionValues( Float32 Fov, Float32 Aspect, Float32 zn, Float32 zf);
	Void		SetFromOrthoProjectionValues( Float32 width, Float32 height, Float32 zn, Float32 zf);
    Void        SetFromOrthoProjectionValues( Float32 l, Float32 r, Float32 b, Float32 t, Float32 zn,  Float32 zf);
	Void		SetFromAxisAndAngle( const CVector3f& Axe, Float32 Angle ); 
	Void		SetFromAxisAndAngle( EAxis axis, Float32 Angle ); 
	Void		SetFromQuaternion( const CQuaternion& quaternion ); 
	Void		SetFromEulerAngle( const CEulerAngle& angle ); 
	Void		SetFromLookAt( const CVector3f& pos, const CVector3f& target, const CVector3f& up );

	Void		TranslateOverAxis( Float32 delta, EAxis axis );
	Void		SetFromBasisAxis( const CVector3f& basisAxis, EAxis axis );

	Bool		Serialize( CPersistentArchive& ar );
	//@}

private:

	//Methods
	Float32		GetDeterminant();
    Void        GetSubMatrix( CMatrix3x3f& result,  const UInt8 i, const UInt8 j);

};


}

#endif


