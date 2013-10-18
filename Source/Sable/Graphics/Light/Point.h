#ifndef _GRAPHICS_LIGHT_POINT_
#define _GRAPHICS_LIGHT_POINT_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Graphics/Light/Light.h>

namespace Sable
{

/** 
PerspectiveCamera. 
*/
class CLightPoint : public CLight
{

	DEFINE_MANAGED_CLASS( CLightPoint );

public:

	/** @name Constructor/Destructor*/
	//@{
	CLightPoint();
	CLightPoint( const CLightPoint& other);
	virtual ~CLightPoint();
	//@}

	/** @name Operator*/
	//@{
	CLightPoint& operator=( const CLightPoint& other );
	//@}

	/** @name Accessor*/
	//@{
	Float32	GetRadius() const { return m_Radius; }
	//@}

	/** @name Mutator*/
	//@{
	//@}

	/** @name Manipulator*/
	//@{
	Bool	IsPointUnderInfluence( const CVector3f& point );
	//@}

private:

	//Methods

	//Attributes
	Float32	m_Radius;

};

}
#endif
