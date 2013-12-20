#ifndef _SABLE_GAME_SCRIPT_ARGUMENTDESCRIPTOR_
#define _SABLE_GAME_SCRIPT_ARGUMENTDESCRIPTOR_


extern "C" 
{
#include <Sable/Game/Script/Lua/lua.h>
#include <Sable/Game/Script/Lua/lauxlib.h>
}

namespace Sable
{



// Class used to select the right code to execute when pushing or popping lua argument 
template < class Type, class TypeCD >
class CPushPullCode
{

public:

    typedef typename TypeCD::ReferenceProxy ReferenceProxy;
    typedef typename TypeCD::InstanceProxy  InstanceProxy;
    typedef Type& PopReturnType;

    static Bool PushValue( lua_State* L, const Type& value )
    {
        InstanceProxy *ud = (InstanceProxy*)lua_newuserdata(L, sizeof( InstanceProxy ) );
        ud->Set( value );
        luaL_getmetatable(L, TypeCD::Name );  // lookup metatable in Lua registry
        lua_setmetatable(L, -2);
        return TRUE;
    }
    
    static PopReturnType PopValue( lua_State* L, Bool success )
    {
        success = FALSE;
        if( lua_type( L, -1 ) == LUA_TUSERDATA )
        {
            success = TRUE;
            InstanceProxy* ud = (InstanceProxy*)lua_touserdata(L, -1 );
            PopReturnType tmp = ud->Get();
            
            lua_pop( L, 1 );
            return tmp;
        }

        return *((Type*)NULL);
    }
};



// Specialized for pointer type
template < class Type, class TypeCD >
class CPushPullCode< Type*, TypeCD >
{

public:

    typedef typename TypeCD::ReferenceProxy ReferenceProxy;
    typedef typename TypeCD::InstanceProxy  InstanceProxy;
    typedef Type* PopReturnType;

    static Bool PushValue( lua_State* L, Type* const & value )
    {
        if( value )
        {
            ReferenceProxy *ud = (ReferenceProxy*)lua_newuserdata(L, sizeof( ReferenceProxy ) );
            ud->Set( value );
            luaL_getmetatable(L, TypeCD::Name );  // lookup metatable in Lua registry
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
            ReferenceProxy* ud = (ReferenceProxy*)lua_touserdata(L, -1 );
            PopReturnType tmp = ud->Obj;
            
            lua_pop( L, 1 );
            return tmp;
        }
        return NULL;
    }
};

// Specialized for const pointer type
template < class Type, class TypeCD >
class CPushPullCode< const Type*, TypeCD>
{

public:

    typedef typename TypeCD::ReferenceProxy ReferenceProxy;
    typedef typename TypeCD::InstanceProxy  InstanceProxy;
    typedef const Type* PopReturnType;

    static Bool PushValue( lua_State* L, const Type& value )
    {
        if( value )
        {
            ReferenceProxy *ud = (ReferenceProxy*)lua_newuserdata(L, sizeof( ReferenceProxy ) );
            ud->Set( value );
            luaL_getmetatable(L, TypeCD::Name );  // lookup metatable in Lua registry
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
            ReferenceProxy* ud = (ReferenceProxy*)lua_touserdata(L, -1 );
            PopReturnType tmp = ud->Get();
            
            lua_pop( L, 1 );
            return tmp;
        }
        return NULL;
    }
};
        
// Specialized for ref type
template < class Type, class TypeCD >
class CPushPullCode< Type&, TypeCD >
{

public:

    typedef typename TypeCD::ReferenceProxy ReferenceProxy;
    typedef typename TypeCD::InstanceProxy  InstanceProxy;
    typedef Type& PopReturnType;

    static Bool PushValue( lua_State* L, const Type& value )
    {
        ReferenceProxy *ud = (ReferenceProxy*)lua_newuserdata(L, sizeof( ReferenceProxy ) );
        ud->Set( &value );
        luaL_getmetatable(L, TypeCD::Name );  // lookup metatable in Lua registry
        lua_setmetatable(L, -2);
    
        return TRUE;
    }
    
    static PopReturnType PopValue( lua_State* L, Bool success )
    {
        success = FALSE;
        if( lua_type( L, -1 ) == LUA_TUSERDATA )
        {
            success = TRUE;
            ReferenceProxy* ud = (ReferenceProxy*)lua_touserdata(L, -1 );
            PopReturnType tmp = *ud->Get();
            
            lua_pop( L, 1 );
            return tmp;
        }

        return *((Type*)NULL);
    }
};
            
// Specialized for const ref type
template < class Type, class TypeCD >
class CPushPullCode< const Type&, TypeCD >
{

public:

    typedef typename TypeCD::ReferenceProxy ReferenceProxy;
    typedef typename TypeCD::InstanceProxy  InstanceProxy;
    typedef const Type& PopReturnType;

    static Bool PushValue( lua_State* L, const Type& value )
    {
        ReferenceProxy *ud = (ReferenceProxy*)lua_newuserdata(L, sizeof( ReferenceProxy ) );
        ud->Set( &value );
        luaL_getmetatable(L, TypeCD::Name );  // lookup metatable in Lua registry
        lua_setmetatable(L, -2);
    
        return TRUE;
    }
    
    static PopReturnType PopValue( lua_State* L, Bool success )
    {
        success = FALSE;
        if( lua_type( L, -1 ) == LUA_TUSERDATA )
        {
            success = TRUE;
            ReferenceProxy* ud = (ReferenceProxy*)lua_touserdata(L, -1 );
            PopReturnType tmp = *ud->Get();
            
            lua_pop( L, 1 );
            return tmp;
        }

        return *((Type*)NULL);
    }
};
  
            
// Specialized for float
template < class TypeCD >
class CPushPullCode< Float32, TypeCD >
{

public:

    typedef typename TypeCD::ReferenceProxy ReferenceProxy;
    typedef typename TypeCD::InstanceProxy  InstanceProxy;
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

// Specialized for Int
template < class TypeCD >
class CPushPullCode< Int32, TypeCD >
{

public:

    typedef typename TypeCD::ReferenceProxy ReferenceProxy;
    typedef typename TypeCD::InstanceProxy  InstanceProxy;
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
    
// Specialized for Bool
template < class TypeCD >
class CPushPullCode< Bool, TypeCD >
{

public:

    typedef typename TypeCD::ReferenceProxy ReferenceProxy;
    typedef typename TypeCD::InstanceProxy  InstanceProxy;
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
            PopReturnType tmp = (Bool) lua_toboolean( L,  -1 );
            lua_pop( L, 1 );
            return tmp;
        }
        return 0;
    }
};

// Specialized for Void
template < class TypeCD >
class CPushPullCode< Void, TypeCD >
{

public:

    typedef typename TypeCD::ReferenceProxy ReferenceProxy;
    typedef typename TypeCD::InstanceProxy  InstanceProxy;
    typedef Void PopReturnType;

    static Bool PushValue( lua_State* L, const Bool& value )
    {
        return TRUE;
    }

    static PopReturnType PopValue( lua_State* L, Bool success )
    {
    }
};


template <class ClassDescriptor>
class CArgDescriptor
{

public:

    typedef typename ClassDescriptor::ReferenceProxy ReferenceProxy;
    typedef typename ClassDescriptor::InstanceProxy  InstanceProxy;
    typedef typename ClassDescriptor::Type           Type;
    typedef CPushPullCode< Type, ClassDescriptor >   PushPullCode;
    typedef typename PushPullCode::PopReturnType     PopReturnType;

    static Bool PushValue( lua_State* L, const Type& value )
    {
        return PushPullCode::PushValue( L, value );
    }
    
    static PopReturnType PopValue( lua_State* L, Bool success )
    {
        return PushPullCode::PopValue( L, success );
    }
};

    
}

#endif
