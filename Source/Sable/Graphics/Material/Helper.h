#ifndef _SABLE_GRAPHICS_MATERIAL_HELPER_
#define _SABLE_GRAPHICS_MATERIAL_HELPER_

#include <Sable\Graphics\Common\DataTypes.h>

namespace Sable
{

class CMaterial;
class CTexture2D;

/** 
\ingroup GraphicsGeometry
*/
class CMaterialHelper
{
	
public:

    /** @name Constructor/Destructor*/
    //@{
    //@}
    
    /** @name Manipulator*/
    //@{
	static Bool CreateFlatMaterial( CMaterial& material, CTexture2D& texture );
	//@}
    
private:
    
	// Methods
	CMaterialHelper();

    // Attributes 

};

}

#endif


