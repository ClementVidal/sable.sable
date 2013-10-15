#ifndef _GRAPHICS_LIGHT_ORTHOGRAPHIC_
#define _GRAPHICS_LIGHT_ORTHOGRAPHIC_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Graphics\Light\Light.h>

namespace Sable
{

/** 
PerspectiveCamera. 
*/
class CLightOrthographic : public CLight
{

	DEFINE_MANAGED_CLASS( CLightOrthographic );

public:

	/** @name Constructor/Destructor*/
	//@{
	CLightOrthographic();
	CLightOrthographic( CLightOrthographic& other);
	virtual ~CLightOrthographic();
	//@}

	/** @name Operator*/
	//@{
	CLightOrthographic& operator=( const CLightOrthographic& other );
	//@}

	/** @name Mutator*/
	//@{
	//@}

	/** @name Accessor*/
	//@{
	//@}

	/** @name Manipulator*/
	//@{
	Bool	IsPointUnderInfluence( const CVector3f& point );
	//@}


};

}
#endif
