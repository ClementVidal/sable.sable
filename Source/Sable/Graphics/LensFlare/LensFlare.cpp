#include <Sable/Graphics/LensFlare/LensFlare.h>

#include <Sable/Graphics/LensFlare/RenderPass.h>

#define WorldLensFlare_DefaultShaderFilePath "World\\LensFlare.fx"

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1( Sable, CLensFlare, CNodeSpatial );

CLensFlare::SSpot::SSpot()
{
    Pos = 0.0f;
    Size = 1.0;
}

CLensFlare::CLensFlare( CNodeSpatial& node ) :
    CNodeSpatial( node )
{
    m_Length = 2.0f;
}

CLensFlare::~CLensFlare()
{
}

Void CLensFlare::SetSpotCount( UInt32 i)
{
    m_SpotTable.SetItemCount( i );
}

UInt32 CLensFlare::GetSpotCount() const
{
    return m_SpotTable.GetItemCount();
}

CLensFlare::SSpot& CLensFlare::GetSpotAtIndex( UInt32 i )
{
    return m_SpotTable[i];
}
