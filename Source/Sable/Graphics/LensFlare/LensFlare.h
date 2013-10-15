#ifndef _SABLE_SCENE_WORLD_LENSFLARE_
#define _SABLE_SCENE_WORLD_LENSFLARE_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Graphics\Node\Header.h>
#include <Sable\Graphics\Texture\Header.h>
#include <Sable\Core\ManagedObject\Ref.h>

namespace Sable
{

class CSceneWorld;

/**  
\ingroup SceneWorld
WorldLensFlare
*/
class CLensFlare : public CNodeSpatial
{

    DEFINE_MANAGED_CLASS( CLensFlare );

public:

    /** @name DataTypes*/
    //@{
    struct SSpot
    {
        SSpot();
        Float32             Pos;
        Float32             Size;
        CColor              Color;
        CRef<CTexture2D>      Texture;
    };
    //@}

    /** @name Constructor/Destructor*/
    //@{
    CLensFlare( CNodeSpatial& node );
    ~CLensFlare();
    //@}

    /** @name Accessors*/
    //@{
    Void                SetSpotCount( UInt32 i) ;
    UInt32              GetSpotCount() const;
    SSpot&              GetSpotAtIndex( UInt32 i );
    Float32             GetLength() const;
    //@}

    /** @name Manipulator*/
    //@{
    //@}


private:

    // Method

    //Attribute
    CSceneWorld*                         m_World;
    CArray<SSpot>                   m_SpotTable;
    Float32                         m_Length;

};

Inline
Float32 CLensFlare::GetLength() const
{
    return m_Length;
}

}

#endif
