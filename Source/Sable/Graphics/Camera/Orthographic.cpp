#include <Sable/Graphics/Camera/Orthographic.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1( Sable, CCameraOrthographic, CCamera );

CCameraOrthographic::CCameraOrthographic():
CCamera()
{
}

CCameraOrthographic::CCameraOrthographic( CNode& parent ):
CCamera( parent )
{

}

CCameraOrthographic::~CCameraOrthographic()
{
}

Void CCameraOrthographic::SetProjectionMatrix( const Float32 width, const Float32 height, const Float32 near, const Float32 far)
{

}
