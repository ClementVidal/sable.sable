#ifndef _SABLE_CORE_GEOMETRY_RECT3DF_
#define _SABLE_CORE_GEOMETRY_RECT3DF_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\Math\Vector2f.h>

namespace Sable
{

class CRect2Di;

/** 
\ingroup CoreGeometry
2D Rectangle.

Position represent the UpperLeft corner of the rectangle.
Size represent the width and height of that rectangle
*/
class CRect2Df 
{

public:

	/** @name Constructor/Destructor*/
	//@{
	CRect2Df();
	CRect2Df( const CRect2Di& other );
	//@}

	/** @name Operator*/
	//@{
	//@}

	/** @name Accessors*/
	//@{	
	const CVector2f&	GetPosition() const;
	const CVector2f&	GetSize() const;

    Bool				IsEmpty() const;
	CVector2f			GetCorner( UInt32 i ) const;
    CVector2f			GetUpperLeftCorner() const;
    CVector2f			GetUpperRightCorner() const;
    CVector2f			GetLowerLeftCorner() const;
    CVector2f			GetLowerRightCorner() const;
	//@}

	/** @name Manipulator*/
	//@{
	Void SetFromTwoPoints( const CVector2f& ul, const CVector2f& br );
	Void Inflate( Float32 x, Float32 y );
    Void Contract( Float32 x, Float32 y );
	Void Inflate( const CVector2f& v );
    Void Contract( const CVector2f& v );
	Bool IsInside( const CVector2f& point ) const;
    Void SetEmpty();
	//@}

private:

	// Attributes	
	CVector2f	m_Position;
	CVector2f	m_Size;

};


}

#endif


