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
template <typename ClassDescriptor>
class CArgDescriptor
{

public:

    typedef typename ClassDescriptor::Type&         PopReturnType;
    typedef typename ClassDescriptor::InstanceProxy ClassInstanceProxy;
    typedef typename ClassDescriptor::Type          ClassType;

    static Bool PushValue( lua_State* L, const ClassType& value )
    {
        ClassInstanceProxy *ud = (ClassInstanceProxy*)lua_newuserdata(L, sizeof( ClassInstanceProxy ) );
        ud->Set( value );
        luaL_getmetatable(L, ClassDescriptor::Name );  // lookup metatable in Lua registry
        lua_setmetatable(L, -2);
        return TRUE;
    }
    
    static PopReturnType PopValue( lua_State* L, Bool success )
    {
        success = FALSE;
        if( lua_type( L, -1 ) == LUA_TUSERDATA )
        {
            success = TRUE;
            ClassInstanceProxy* ud = (ClassInstanceProxy*)lua_touserdata(L, -1 );
            PopReturnType tmp = ud->Get();
            
            lua_pop( L, 1 );
            return tmp;
        }

        // THIS IS NOT A GOOD THING , BUT I DID NOT FIND ANY GOOD SOLUTION FOR NOW
        //return ((ClassType*)NULL);
    }
};
    
// Specialized for pointer type
template <typename ClassDescriptor>
class CArgDescriptor<ClassDescriptor*>
{

public:

    typedef typename ClassDescriptor::Type*          PopReturnType;
    typedef typename ClassDescriptor::ReferenceProxy ClassReferenceProxy;
    typedef typename ClassDescriptor::Type           ClassType;

    static Bool PushValue( lua_State* L, const ClassType* value )
    {
        if( value )
        {
            ClassReferenceProxy *ud = (ClassReferenceProxy*)lua_newuserdata(L, sizeof( ClassReferenceProxy ) );
            ud->Set( value );
            luaL_getmetatable(L, ClassDescriptor::Name );  // lookup metatable in Lua registry
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
            ClassReferenceProxy* ud = (ClassReferenceProxy*)lua_touserdata(L, -1 );
            PopReturnType tmp = ud->Obj;
            
            lua_pop( L, 1 );
            return tmp;
        }
        return NULL;
    }
};
    
    
// Specialized for const pointer type
template <typename ClassDescriptor>
class CArgDescriptor<const ClassDescriptor*>
{

public:
    
    typedef const typename ClassDescriptor::Type*    PopReturnType;
    typedef typename ClassDescriptor::ReferenceProxy ClassReferenceProxy;
    typedef typename ClassDescriptor::Type           ClassType;

    static Bool PushValue( lua_State* L, const ClassType* value )
    {
        if( value )
        {
            ClassReferenceProxy *ud = (ClassReferenceProxy*)lua_newuserdata(L, sizeof( ClassReferenceProxy ) );
            ud->Set( value );
            luaL_getmetatable(L, ClassDescriptor::Name );  // lookup metatable in Lua registry
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
            ClassReferenceProxy* ud = (ClassReferenceProxy*)lua_touserdata(L, -1 );
            PopReturnType tmp = ud->Get();
            
            lua_pop( L, 1 );
            return tmp;
        }
        return NULL;
    }
};
    
// Specialized for const ref type
template <typename ClassDescriptor>
class CArgDescriptor<ClassDescriptor&>
{

public:

    typedef typename ClassDescriptor::Type&          PopReturnType;
    typedef typename ClassDescriptor::ReferenceProxy ClassReferenceProxy;
    typedef typename ClassDescriptor::Type           ClassType;

    static Bool PushValue( lua_State* L, const ClassType& value )
    {
        ClassReferenceProxy *ud = (ClassReferenceProxy*)lua_newuserdata(L, sizeof( ClassReferenceProxy ) );
        ud->Set( &value );
        luaL_getmetatable(L, ClassDescriptor::Name );  // lookup metatable in Lua registry
        lua_setmetatable(L, -2);
        return TRUE;
    }

    static PopReturnType PopValue( lua_State* L, Bool success )
    {
        success = FALSE;
        if( lua_type( L, -1 ) == LUA_TUSERDATA )
        {
            success = TRUE;
            ClassReferenceProxy* ud = (ClassReferenceProxy*)lua_touserdata(L, -1 );
            PopReturnType tmp = *ud->Get();
            
            lua_pop( L, 1 );
            return tmp;
        }
        return *((ClassType*)NULL);
    }
};

// Specialized for const ref type
template <typename ClassDescriptor>
class CArgDescriptor<const ClassDescriptor&>
{

public:
    
    typedef const typename ClassDescriptor::Type& PopReturnType;
    typedef typename ClassDescriptor::ReferenceProxy ClassReferenceProxy;
    typedef typename ClassDescriptor::Type ClassType;

    static Bool PushValue( lua_State* L, const ClassType& value )
    {
        ClassReferenceProxy *ud = (ClassReferenceProxy*)lua_newuserdata(L, sizeof( ClassReferenceProxy ) );
        ud->Set( &value );
        luaL_getmetatable(L, ClassDescriptor::Name );  // lookup metatable in Lua registry
        lua_setmetatable(L, -2);
        return TRUE;
    }
    
    static PopReturnType PopValue( lua_State* L, Bool success )
    {
        success = FALSE;
        if( lua_type( L, -1 ) == LUA_TUSERDATA )
        {
            success = TRUE;
            ClassReferenceProxy* ud = (ClassReferenceProxy*)lua_touserdata(L, -1 );
            PopReturnType tmp = *ud->Get();
            
            lua_pop( L, 1 );
            return tmp;
        }
        return *((const ClassType*)NULL);
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

//Specialized for void type
template <>
class CArgDescriptor<Void>
{

public:

    typedef Void PopReturnType;

    static Bool PushValue( lua_State* L, const Bool& value )
    {
        return TRUE;
    }
    
    static PopReturnType PopValue( lua_State* L, Bool success )
    {
    }
};
    
}

#endif
