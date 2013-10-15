#ifndef _SABLE_CORE_GEOMETRY_RECT3DI_
#define _SABLE_CORE_GEOMETRY_RECT3DI_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\Math\Vector2i.h>

namespace Sable
{

/** 
\ingroup CoreGeometry
2D Rectangle.

Position represent the UpperLeft corner of the rectangle.
Size represent the width and height of that rectangle
*/
class CRect2Di 
{

public:

	/** @name Constructor/Destructor*/
	//@{
	CRect2Di( );
	CRect2Di( Int32 x, Int32 y, Int32 w, Int32 h );
	CRect2Di( const CVector2i& pos, const CVector2i& size );
	//@}

	/** @name Operator*/
	//@{
	//@}

	/** @name Accessors*/
	//@{
	Void				SetFromTwoPoints( const CVector2i& a, const CVector2i& b );
	const CVector2i&	GetPosition() const;
	const CVector2i&	GetSize() const;
	Void				SetPosition( const CVector2i& p );
	Void				SetSize( const CVector2i& s );
    Bool				IsEmpty() const;
    CVector2i			GetUpperLeftCorner() const;
    CVector2i			GetUpperRightCorner() const;
    CVector2i			GetLowerLeftCorner() const;
    CVector2i			GetLowerRightCorner() const;
	CVector2i			GetCorner( UInt32 i ) const;
	//@}

	/** @name Manipulator*/
	//@{
	Void Inflate( Int32 x, Int32 y );
    Void Contract( Int32 x, Int32 y );
	Void Inflate( const CVector2i& v );
    Void Contract( const CVector2i& v );
	Bool IsInside( const CVector2i& point ) const;
    Void SetEmpty();
	void Add( const CRect2Di& rect );
	//@}

private:

	// Attributes
	CVector2i	m_Position;
	CVector2i	m_Size;

};


}

#endif


