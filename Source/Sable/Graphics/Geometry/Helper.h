#ifndef _SABLE_GRAPHICS_GEOMETRY_HELPER_
#define _SABLE_GRAPHICS_GEOMETRY_HELPER_

#include <Sable/Graphics/Common/DataTypes.h>

namespace Sable
{

class CGeometryVertexBuffer;
class CGeometryIndexBuffer;
class CGeometryModel;

/** 
\ingroup GraphicsGeometry
*/
class CGeometryHelper
{
	
public:

    /** @name Constructor/Destructor*/
    //@{
    //@}
    
    /** @name Manipulator*/
    //@{
	static Bool CreatePlane( CGeometryModel& model, const CColor& color, const CVector2f& size, const CVector2f& uvSize );
	//@}
    
private:
    
	// Methods
	CGeometryHelper();

    // Attributes 

};

}

#endif


