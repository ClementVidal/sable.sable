#ifndef _SABLE_GAME_SCRIPT_ARGUMENTDESCRIPTOR_
#define _SABLE_GAME_SCRIPT_ARGUMENTDESCRIPTOR_

extern "C" 
{
#include <Sable\Game\Script\Lua\Lua.h>
#include <Sable\Game\Script\Lua\lauxlib.h>
}

namespace Sable
{

// Class used to select the right code to execute when pushing or popping lua argument 
template <typename TType>
class CArgDescriptor
{

public:

	typedef TType& PopReturnType;

	static Bool PushValue( lua_State* L, const TType& value )
	{
		CClassDescriptor<TType>::InstanceProxy *ud = (CClassDescriptor<TType>::InstanceProxy*)lua_newuserdata(L, sizeof( CClassDescriptor<TType>::InstanceProxy ) );
		ud->Set( value );
		luaL_getmetatable(L, CClassDescriptor<TType>::Name );  // lookup metatable in Lua registry
		lua_setmetatable(L, -2);
		return TRUE;
	}

	static PopReturnType PopValue( lua_State* L, Bool success )
	{
		success = FALSE;
		if( lua_type( L, -1 ) == LUA_TUSERDATA )
		{
			success = TRUE;
			CClassDescriptor<TType>::InstanceProxy* ud = (CClassDescriptor<TType>::InstanceProxy*)lua_touserdata(L, -1 );
			PopReturnType tmp = ud->Get();

			lua_pop( L, 1 );
			return tmp;
		}
		return *((TType*)NULL);
	}
};

// Specialized for pointer type
template <typename TType>
class CArgDescriptor<TType*>
{

public:

	typedef TType* PopReturnType;

	static Bool PushValue( lua_State* L, const TType* value )
	{
		if( value )
		{
			CClassDescriptor<TType>::ReferenceProxy *ud = (CClassDescriptor<TType>::ReferenceProxy*)lua_newuserdata(L, sizeof( CClassDescriptor<TType>::ReferenceProxy ) );
			ud->Set( value );
			luaL_getmetatable(L, CClassDescriptor<TType>::Name );  // lookup metatable in Lua registry
			lua_setmetatable(L, -2);
		}
		else
		{
			lua_pushnil( L );
		}
		return TRUE;
	}

	static PopReturnType PopValue( lua_State* L, Bool success )
	{
		success = FALSE;
		if( lua_type( L, -1 ) == LUA_TUSERDATA )
		{
			success = TRUE;
			CClassDescriptor<TType>::ReferenceProxy* ud = (CClassDescriptor<TType>::ReferenceProxy*)lua_touserdata(L, -1 );
			PopReturnType tmp = ud->Obj;

			lua_pop( L, 1 );
			return tmp;
		}
		return NULL;
	}
};


// Specialized for const pointer type
template <typename TType>
class CArgDescriptor<const TType*>
{

public:

	typedef const TType* PopReturnType;

	static Bool PushValue( lua_State* L, const TType* value )
	{
		if( value )
		{
			CClassDescriptor<TType>::ReferenceProxy *ud = (CClassDescriptor<TType>::ReferenceProxy*)lua_newuserdata(L, sizeof( CClassDescriptor<TType>::ReferenceProxy ) );
			ud->Set( value );
			luaL_getmetatable(L, CClassDescriptor<TType>::Name );  // lookup metatable in Lua registry
			lua_setmetatable(L, -2);
		}
		else
		{
			lua_pushnil( L );
		}
		return TRUE;
	}

	static PopReturnType PopValue( lua_State* L, Bool success )
	{
		success = FALSE;
		if( lua_type( L, -1 ) == LUA_TUSERDATA )
		{
			success = TRUE;
			CClassDescriptor<TType>::ReferenceProxy* ud = (CClassDescriptor<TType>::ReferenceProxy*)lua_touserdata(L, -1 );
			PopReturnType tmp = ud->Get();

			lua_pop( L, 1 );
			return tmp;
		}
		return NULL;
	}
};

// Specialized for const ref type
template <typename TType>
class CArgDescriptor<TType&>
{

public:

	typedef TType& PopReturnType;

	static Bool PushValue( lua_State* L, const TType& value )
	{
		CClassDescriptor<TType>::ReferenceProxy *ud = (CClassDescriptor<TType>::ReferenceProxy*)lua_newuserdata(L, sizeof( CClassDescriptor<TType>::ReferenceProxy ) );
		ud->Set( &value );
		luaL_getmetatable(L, CClassDescriptor<TType>::Name );  // lookup metatable in Lua registry
		lua_setmetatable(L, -2);
		return TRUE;
	}

	static PopReturnType PopValue( lua_State* L, Bool success )
	{
		success = FALSE;
		if( lua_type( L, -1 ) == LUA_TUSERDATA )
		{
			success = TRUE;
			CClassDescriptor<TType>::ReferenceProxy* ud = (CClassDescriptor<TType>::ReferenceProxy*)lua_touserdata(L, -1 );
			PopReturnType tmp = *ud->Get();

			lua_pop( L, 1 );
			return tmp;
		}
		return *((TType*)NULL);
	}
};

// Specialized for const ref type
template <typename TType>
class CArgDescriptor<const TType&>
{

public:

	typedef const TType& PopReturnType;

	static Bool PushValue( lua_State* L, const TType& value )
	{
		CClassDescriptor<TType>::ReferenceProxy *ud = (CClassDescriptor<TType>::ReferenceProxy*)lua_newuserdata(L, sizeof( CClassDescriptor<TType>::ReferenceProxy ) );
		ud->Set( &value );
		luaL_getmetatable(L, CClassDescriptor<TType>::Name );  // lookup metatable in Lua registry
		lua_setmetatable(L, -2);
		return TRUE;
	}

	static PopReturnType PopValue( lua_State* L, Bool success )
	{
		success = FALSE;
		if( lua_type( L, -1 ) == LUA_TUSERDATA )
		{
			success = TRUE;
			CClassDescriptor<TType>::ReferenceProxy* ud = (CClassDescriptor<TType>::ReferenceProxy*)lua_touserdata(L, -1 );
			PopReturnType tmp = *ud->Get();

			lua_pop( L, 1 );
			return tmp;
		}
		return *((const TType*)NULL);
	}
};


template <>
class CArgDescriptor<Float32>
{

public:

	typedef Float32 PopReturnType;

	static Bool PushValue( lua_State* L, const Float32& value )
	{
		if( lua_type( L, -1 ) != LUA_TNUMBER )
			return FALSE;

		lua_pushnumber( L,  value );
		lua_pop( L, 1 );
		return TRUE;
	}

	static PopReturnType PopValue( lua_State* L, Bool success )
	{
		success = FALSE;
		if( lua_type( L, -1 ) == LUA_TNUMBER )
		{
			success = TRUE;
			PopReturnType tmp = (Float32) lua_tonumber( L,  -1 );
			lua_pop( L, 1 );
			return tmp;
		}
		return 0.0f;
	}
};

template <>
class CArgDescriptor<Int32>
{

public:

	typedef Int32 PopReturnType;

	static Bool PushValue( lua_State* L, const Int32& value )
	{
		if( lua_type( L, -1 ) != LUA_TNUMBER )
			return FALSE;

		lua_pushinteger( L,  value );
		lua_pop( L, 1 );
		return TRUE;
	}

	static PopReturnType PopValue( lua_State* L, Bool success )
	{
		success = FALSE;
		if( lua_type( L, -1 ) == LUA_TNUMBER )
		{
			success = TRUE;
			PopReturnType tmp = (Int32) lua_tointeger( L,  -1 );
			lua_pop( L, 1 );
			return tmp;
		}
		return 0;
	}
};

template <>
class CArgDescriptor<Bool>
{

public:

	typedef Bool PopReturnType;

	static Bool PushValue( lua_State* L, const Bool& value )
	{
		if( lua_type( L, -1 ) != LUA_TBOOLEAN )
			return FALSE;

		lua_pushboolean( L,  value );		
		lua_pop( L, 1 );
		return TRUE;
	}

	static PopReturnType PopValue( lua_State* L, Bool success )
	{
		success = FALSE;
		if( lua_type( L, -1 ) == LUA_TBOOLEAN )
		{
			success = TRUE;
			PopReturnType tmp = lua_toboolean( L,  -1 );
			lua_pop( L, 1 );
			return tmp;
		}
		return FALSE;
	}
};

}

#endif
