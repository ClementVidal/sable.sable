#include <Sable\Game\Script\Macro.h>

#include <Sable\Core\Math\Header.h>
#include <Sable\Core\File\Header.h>

REGISTER_SCRIPTED_CLASS( Sable, CVector3f, TRUE, TRUE  )
REGISTER_SCRIPTED_CLASS_METHOD0( Sable, CVector3f, GetX, Float32, TRUE )
REGISTER_SCRIPTED_CLASS_METHOD0( Sable, CVector3f, GetY, Float32, TRUE )
REGISTER_SCRIPTED_CLASS_METHOD0( Sable, CVector3f, GetZ, Float32, TRUE )
REGISTER_SCRIPTED_CLASS_METHOD1( Sable, CVector3f, SetX, Void, Float32, FALSE )
REGISTER_SCRIPTED_CLASS_METHOD1( Sable, CVector3f, SetY, Void, Float32, FALSE )
REGISTER_SCRIPTED_CLASS_METHOD1( Sable, CVector3f, SetZ, Void, Float32, FALSE )
REGISTER_SCRIPTED_CLASS_METHOD3( Sable, CVector3f, Set, Void, Float32, Float32, Float32, FALSE )
REGISTER_SCRIPTED_CLASS_METHOD1( Sable, CVector3f, DotProduct, Float32, const CVector3f&, TRUE )

REGISTER_SCRIPTED_CLASS( Sable, CMatrix4x4f, TRUE, TRUE )
REGISTER_SCRIPTED_CLASS_METHOD0( Sable, CMatrix4x4f, GetTranslationComponent, const CVector3f&, TRUE )
REGISTER_SCRIPTED_CLASS_METHOD0( Sable, CMatrix4x4f, SetFromIdentity, Void, FALSE )

REGISTER_SCRIPTED_CLASS( Sable, CFile, FALSE, FALSE )
REGISTER_SCRIPTED_CLASS_METHOD0( Sable, CFile, Close, Void, FALSE )
REGISTER_SCRIPTED_CLASS_METHOD0( Sable, CFile, GetSize, UInt32, TRUE )
REGISTER_SCRIPTED_CLASS_METHOD0( Sable, CFile, GetPosition, UInt32, TRUE )
REGISTER_SCRIPTED_CLASS_METHOD0( Sable, CFile, GetIsEndOfFile, Bool, TRUE )
REGISTER_SCRIPTED_CLASS_METHOD2( Sable, CFile, Open, Bool, const CFilePath&, EAccesMode, FALSE )

/**
Void* not yet supported
REGISTER_SCRIPTED_CLASS_METHOD2( Sable, CFile, Read, Bool, Void*, UInt32, FALSE )
REGISTER_SCRIPTED_CLASS_METHOD2( Sable, CFile, Write, Bool, Void*, UInt32, FALSE )
*/