#ifndef _SABLE_GAME_SCRIPT_CLASSDESCRIPTOR_
#define _SABLE_GAME_SCRIPT_CLASSDESCRIPTOR_

#include <Sable/Game/Script/MethodDescriptor.h>
#include <Sable/Game/Script/ArgumentDescriptor.h>

extern "C" 
{
#include <Sable/Game/Script/Lua/lua.h>
#include <Sable/Game/Script/Lua/lauxlib.h>
}

namespace Sable
{

// Define if a class instance can be instancied from within a script
template< class ClassType >
struct CInstanciationPolicy
{ enum { Value = TRUE }; };

// Define if class instance is stored within the lua state or externaly (i.e: as a CRef<> )
// TRUE == stored localy, FALSE stored externaly
template< class ClassType >
struct CStoragePolicy
{ enum { Value = TRUE }; };

// Define the right code to call when allocating a new object from LUA
// Object could be either allocated on the stack and then copied back and forth
// or allocated dynamicly using NEWOBJ
template< class ClassDescriptor, Bool allocateOnStack >
struct CAllocateNewObject
{ 
    static Void Do( lua_State* L )
    {
        lua_remove(L, 1);   // use classname:new(), instead of classname.new()
        typename ClassDescriptor::Type  obj;
        CArgDescriptor< ClassDescriptor >::PushValue( L, obj );
    }
};

template< class ClassDescriptor>
struct CAllocateNewObject< ClassDescriptor, FALSE >
{ 
    typedef typename ClassDescriptor::Type ClassType;

    static Void Do( lua_State* L )
    {
        lua_remove(L, 1);   // use classname:new(), instead of classname.new()
        CRef< ClassType > obj = NEWOBJ( ClassType, () );
        CArgDescriptor< ClassDescriptor >::PushValue( L, *obj );
    }
};

// Define the right structure used to old a reference to an object
template< class ClassType >
struct CReferenceProxy
{
    ClassType* Get()
    {
        return Ref;
    }

    Void Set( const ClassType* t )
    {
        Ref = const_cast<ClassType*>(t);
    }
    ClassType*	Ref;
};

// Define the right structure used to old an instance of an object
template< class ClassType, Bool storeCopy >
struct CInstanceProxy { };

// If storeCopy == TRUE data in owned by this instance data
template< class ClassType >
struct CInstanceProxy<ClassType, TRUE>
{ 
    Void Free( )
    {
    }
    
    ClassType& Get()
    {
        return Obj;
    }
    
    Void Set( const ClassType& t )
    {
        Obj = t;
    }

private:
    ClassType Obj;
};


// If storeCopy == FALSE data in only referenced by this instance data
template< class ClassType >
struct CInstanceProxy<ClassType, FALSE>
{	
    Void Free( )
    {
        Obj = NULL;
    }
    
    ClassType& Get()
    {
        return *Obj;
    }
    
    Void Set( const ClassType& t )
    {
        Obj = &t;
    }

private:
    CRef<ClassType> Obj;
};

// USer entry point used to define a class
class CClassDescriptorBase
{
public:
    virtual int Register( lua_State* L ) const =0;
    virtual void RegisterMethods( lua_State* L, int methodTable ) const = 0;
    
    CClassDescriptorBase*	Next;

};



template< class ClassType >
class CClassDescriptor : public CClassDescriptorBase
{

public:

    typedef CStoragePolicy<ClassType> StoragePolicy;
    typedef CInstanceProxy<ClassType, StoragePolicy::Value > InstanceProxy;
    typedef CReferenceProxy< ClassType > ReferenceProxy;
    typedef ClassType                   Type;
    
    CClassDescriptor( CClassDescriptorBase** classList, String name )
    {
        MethodList = NULL;
        BaseClassList = NULL;
        Name = name;
        Next = NULL;
        
        if( *classList == NULL )
        {
            *classList = this;
        }
        else
        {
            Next = *classList;
            *classList = this;
        }
    }

    void RegisterMethods( lua_State* L, int methodTable ) const
    {
        CMethodDescriptorBase* method = MethodList;
        while( method )
        {
            method->Register( L, methodTable );
            method = method->Next;
        }
    }
    
    int Register( lua_State* L ) const
    {
        lua_newtable(L);
        int methodTable = lua_gettop(L);
        
        luaL_newmetatable(L, Name );
        int metatable = lua_gettop(L);
        
        // Retrieve the globals table
        lua_pushinteger(L, LUA_RIDX_GLOBALS );
        lua_gettable(L, LUA_REGISTRYINDEX);
        
        // store method table in globals so that
        // scripts can add functions written in Lua.
        lua_pushstring(L, Name );
        lua_pushvalue(L, methodTable);
        lua_settable(L, -3);
        
        // hide metatable from Lua getmetatable()
        // This is done only by setting any value to the __metatable field
        lua_pushliteral(L, "__metatable");
        lua_pushvalue(L, methodTable);
        lua_settable(L, metatable);  
        
        lua_pushliteral(L, "__index");
        lua_pushvalue(L, methodTable);
        lua_settable(L, metatable);
        
        lua_pushliteral(L, "__tostring");
        lua_pushcfunction(L, CClassDescriptor<ClassType>::ToString );
        lua_settable(L, metatable);
        
        lua_pushliteral(L, "__gc");
        lua_pushcfunction(L, CClassDescriptor<ClassType>::Free);
        lua_settable(L, metatable);
        
        // Install the allocation method
        if( CInstanciationPolicy<ClassType>::Value )
        {
            lua_pushliteral(L, "new");
            lua_pushcfunction(L, CClassDescriptor<ClassType>::New);
            lua_settable(L, methodTable);
        }
        
        // Register base class methods
        CClassDescriptorBase* baseClass = BaseClassList;
        while( baseClass )
        {
            baseClass->RegisterMethods( L, methodTable );
            baseClass = baseClass->Next;
        }
        
        // Register all methods
        RegisterMethods( L, methodTable );
        
        return methodTable;
    }
    
    
    static int New( lua_State *L ) 
    {
        CAllocateNewObject< CClassDescriptor< ClassType > , CStoragePolicy< ClassType >::Value >::Do( L );
        return 1;  // userdata containing pointer to T object
    }
    
    // garbage collection metamethod
    static int Free(lua_State *L) 
    {
        InstanceProxy* ud = (InstanceProxy*)lua_touserdata(L, 1);
        ud->Free();
        
        return 0;
    }
    
    static int ToString (lua_State *L)
    {
        return 1;
    }
    
    static CMethodDescriptorBase*		MethodList;
    static CClassDescriptorBase*		BaseClassList;
    static String				Name;
    
};
    
template< class ClassType >
String CClassDescriptor<ClassType>::Name = NULL;

template< class ClassType >
CMethodDescriptorBase* CClassDescriptor<ClassType>::MethodList = NULL;

template< class ClassType >
CClassDescriptorBase* CClassDescriptor<ClassType>::BaseClassList = NULL;

}

#endif

