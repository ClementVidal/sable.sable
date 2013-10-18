#ifndef _SABLE_CORE_GEOMETRY_AABOX_
#define _SABLE_CORE_GEOMETRY_AABOX_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/Math/Vector3f.h>

namespace Sable
{

class CPersistentArchive;
class CBufferVisitor;
class CRay;

/** 
\ingroup CoreGeometry
Axis Aligned Box
*/
class CAABox 
{

public:

	/** @name Constructor/Destructor*/
	//@{
	CAABox();
	CAABox( const CBufferVisitor& bufferVisitor );
	~CAABox();
	//@}

	/** @name Accessors*/
	//@{
    Bool            IsEmpty() const;
	Void			SetMinimum( const CVector3f& min );
	Void			SetMaximum( const CVector3f& min );
	const CVector3f& GetMinimum( ) const;
	const CVector3f& GetMaximum( ) const;
	//@}

	/** @name Mutator*/
	//@{
	Void		AddBox( const CAABox& other );
	Float32		GetXSize() const;
	Float32		GetYSize() const;
	Float32		GetZSize() const;
	CVector3f	GetSize() const;
	CVector3f	GetCenter() const;
    Bool        IsInside( const CVector3f& pos )const;
	//@}

	/** @name Manipulator*/
	//@{
    Float32     Intersect( const CRay& ray ) const;
	Void	    SetEmpty();
	Void	    AddPoint( const CVector3f& point );
	Bool	    Serialize( CPersistentArchive& ar );
	Void	    Transform( const CMatrix4x4f& m );
	Void		Expand( const CVector3f& expand );
	//@}

private:

	// Attributes
	CVector3f	m_Minimum;
	CVector3f	m_Maximum;

};

}

#endif


