#include <Sable/Game/Script/Macro.h>

#include <Sable/Graphics/Node/Header.h>
#include <Sable/Graphics/Geometry/Header.h>

REGISTER_SCRIPTED_CLASS( Sable, CGeometryModel, FALSE, TRUE )

REGISTER_SCRIPTED_CLASS( Sable, CNodeSpatial, FALSE, TRUE )
REGISTER_SCRIPTED_CLASS_METHOD1( Sable, CNodeSpatial, SetLocalMatrix, Void, const CMatrix4x4f& , FALSE )
REGISTER_SCRIPTED_CLASS_METHOD0( Sable, CNodeSpatial, GetWorldMatrix, const CMatrix4x4f&, TRUE )
REGISTER_SCRIPTED_CLASS_METHOD1( Sable, CNodeSpatial, GetWorldBoundingBox, Void, CAABox&, TRUE )

REGISTER_SCRIPTED_CLASS( Sable, CNodeRender, FALSE, TRUE )
REGISTER_SCRIPTED_CLASS_METHOD0( Sable, CNodeRender, GetModel,CGeometryModel*, TRUE )
REGISTER_SCRIPTED_CLASS_METHOD1( Sable, CNodeRender, SetModel, Void, const CGeometryModel*, FALSE )
