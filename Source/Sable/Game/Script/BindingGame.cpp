#include <Sable/Game/Script/Macro.h>

#include <Sable/Game/Service/Header.h>
#include <Sable/Game/Common/Header.h>
#include <Sable/Game/Object/Header.h>

REGISTER_SCRIPTED_CLASS( Sable, CGameContext, FALSE, FALSE )

REGISTER_SCRIPTED_CLASS( Sable, CGameProperty, FALSE, TRUE )
REGISTER_SCRIPTED_CLASS_METHOD0( Sable, CGameProperty, GetAsFloat, Float32, TRUE )
REGISTER_SCRIPTED_CLASS_METHOD0( Sable, CGameProperty, GetAsBool, Bool, TRUE )
REGISTER_SCRIPTED_CLASS_METHOD0( Sable, CGameProperty, GetAsInt, Int32, TRUE )
REGISTER_SCRIPTED_CLASS_METHOD0( Sable, CGameProperty, GetAsVector2, const CVector2f&, TRUE )
REGISTER_SCRIPTED_CLASS_METHOD0( Sable, CGameProperty, GetAsVector3, const CVector3f&, TRUE )
REGISTER_SCRIPTED_CLASS_METHOD0( Sable, CGameProperty, GetAsVector4, const CVector4f&, TRUE )

REGISTER_SCRIPTED_CLASS( Sable, CGameObjectPrototype, FALSE, TRUE  )
REGISTER_SCRIPTED_CLASS_METHOD1( Sable, CGameObjectPrototype, GetParameter, CGameProperty*, const CStringIdentifier&, FALSE )
REGISTER_SCRIPTED_CLASS_METHOD1( Sable, CGameObjectPrototype, AddParameter, CGameProperty*, const CStringIdentifier&, FALSE )
REGISTER_SCRIPTED_CLASS_METHOD1( Sable, CGameObjectPrototype, AddService, CGameService*, const CStringIdentifier&, FALSE )
REGISTER_SCRIPTED_CLASS_METHOD1( Sable, CGameObjectPrototype, GetService, CGameService*, const CStringIdentifier&, TRUE )

REGISTER_SCRIPTED_CLASS( Sable, CGameObject, FALSE, TRUE  )
REGISTER_SCRIPTED_CLASS_METHOD1( Sable, CGameObject, GetParameter, CGameProperty*, const CStringIdentifier&, FALSE )
REGISTER_SCRIPTED_CLASS_METHOD1( Sable, CGameObject, GetService, CGameService*, const CStringIdentifier&, TRUE )

