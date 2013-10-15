#ifndef _GRAPHICS_CAMERA_ORTHOGRAPHIC_
#define _GRAPHICS_CAMERA_ORTHOGRAPHIC_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Graphics\Camera\Camera.h>

namespace Sable
{

/** 
\ingroup GraphicsCamera
Orthographic Camera. 
*/
class CCameraOrthographic : public CCamera
{

	DEFINE_MANAGED_CLASS( CCameraOrthographic );

public:

	/** @name Constructor/Destructor*/
	//@{
	CCameraOrthographic();
	CCameraOrthographic( CNode& other);
	virtual ~CCameraOrthographic();
	//@}

	/** @name Operator*/
	//@{
	//@}

	/** @name Mutator*/
	//@{
	//@}

	/** @name Accessor*/
	//@{
	//@}

	/** @name Manipulator */
	//@{
	Void SetProjectionMatrix( const Float32 width, const Float32 height, const Float32 near, const Float32 far);
	//@}

};

}
#endif
