#ifndef _GRAPHICS_GEOMETRY_GEOMETRYVERTEXELEMENT_
#define _GRAPHICS_GEOMETRY_GEOMETRYVERTEXELEMENT_

#include <Sable\Core\Common\DataTypes.h>

namespace Sable
{

/** 
\ingroup GraphicsGeometry
Vertex Buffer. 
*/
class CGeometryVertexElement
{

public:

	EVertexComponentType			Type;
	EVertexComponent		Semantic;
	UInt32								ByteOffset;
	UInt32								StreamIndex;
    Bool                                IsPerInstanceData;

};

}

#endif
