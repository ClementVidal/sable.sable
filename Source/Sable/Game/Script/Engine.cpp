#include <Sable/Game/Script/Engine.h>

#include <Sable/Game/Script/ClassDescriptor.h>
#include <Sable/Game/Script/MethodDescriptor.h>
#include <Sable/Game/Script/ArgumentDescriptor.h>
#include <Sable/Game/Script/Macro.h>

#include <stdlib.h>

extern "C" 
{
#include <Sable/Game/Script/Lua/LAuxLib.h>
}

using namespace Sable;


IMPLEMENT_MANAGED_CLASS( Sable, CScriptEngine );

CClassDescriptorBase* CScriptEngine::ClassList = NULL;

CScriptEngine::CScriptEngine()
{
	m_State = lua_newstate( &Sable::CScriptEngine::Alloc, NULL );
	DebugAssert( m_State );

	CClassDescriptorBase* currentClass = ClassList;
	while( currentClass )
	{
		currentClass->Register( m_State );
		currentClass = currentClass->Next;
	}
}

CScriptEngine::~CScriptEngine()
{
	lua_close( m_State );
}

Void * CScriptEngine::Alloc(void *ud, void *ptr, size_t osize, size_t nsize) 
{
  (void)ud;  (void)osize;  /* not used */
  if (nsize == 0) 
  {
	  ::free(ptr);
	  return NULL;
  }
  else
	  return ::realloc(ptr, nsize);
}

Bool CScriptEngine::Execute( String code )
{
	DebugAssert( m_State );
	//char* test = "v = CVector3f:new(); v:SetX( 2.1 );";
	if( luaL_dostring( m_State, code ) != LUA_OK )
	{
		String error = lua_tostring( m_State, -1 );
		lua_pop( m_State, 1 );
		return FALSE;
	}
	return TRUE;
}