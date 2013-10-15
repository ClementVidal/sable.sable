#ifndef _SABLE_GRAPHICS_GEOMETRY_IMPL_MSW_HELPER_
#define _SABLE_GRAPHICS_GEOMETRY_IMPL_MSW_HELPER_

#include <Sable\Core\Common\DataTypes.h>

namespace Sable
{

class CImplDirectXVertexStream;

class CImplDirectXGeometryHelper
{
public:

    CImplDirectXGeometryHelper();
    ~CImplDirectXGeometryHelper();

    Void ActivateVertexBuffer( UInt32 index, CImplDirectXVertexStream* vb );
    Void Flush();


    CImplDirectXVertexStream*  ActiveVertexBuffer[8];

};

}

#endif