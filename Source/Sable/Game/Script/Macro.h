#ifndef _SABLE_GAME_SCRIPT_MACRO_
#define _SABLE_GAME_SCRIPT_MACRO_

#include <Sable/Game/Script/ClassDescriptor.h>
#include <Sable/Game/Script/MethodDescriptor.h>


/**
Register a class to the script system
\param nameSpace The namespace of this class
\param className The Name of the class
\param storeCopy	if FALSE this class will be managed internally using reference to only one instance
					if TRUE this class instance will be copied back and forth
\param instanciationAllowed Allow or not the script to allocate instance of that class	
*/
#define REGISTER_SCRIPTED_CLASS( nameSpace, className, storeCopy, instanciationAllowed ) \
	char nameSpace##_##className##_name[] = #className; \
	template<> \
	struct CStoragePolicy< nameSpace :: className >  \
	{ enum { Value = storeCopy }; }; \
	template<> \
	struct CInstanciationPolicy< nameSpace :: className > \
	{ enum { Value = instanciationAllowed }; }; \
	CClassDescriptor< nameSpace :: className >	nameSpace##_##className( &CScriptEngine::ClassList, nameSpace##_##className##_name ); \

#define REGISTER_SCRIPTED_CLASS_METHOD0( nameSpace, className, methodName, returnType, isConst ) \
	char nameSpace##_##className##_##methodName##_name[] = #methodName;\
	CMethodDescriptor< CClassDescriptor< nameSpace :: className > , CClassDescriptor< returnType >, CClassDescriptor< Void >, CClassDescriptor< Void >, CClassDescriptor< Void >, isConst >	nameSpace##_##className##_##methodName ( & nameSpace##_##className.MethodList, nameSpace##_##className##_##methodName##_name, & nameSpace :: className :: methodName ); \

#define REGISTER_SCRIPTED_CLASS_METHOD1( nameSpace, className, methodName, returnType, arg1, isConst ) \
	char nameSpace##_##className##_##methodName##_name[] = #methodName;\
	CMethodDescriptor< CClassDescriptor< nameSpace :: className > , CClassDescriptor< returnType >, CClassDescriptor< arg1 >, CClassDescriptor< Void >, CClassDescriptor< Void >, isConst >	nameSpace##_##className##_##methodName ( & nameSpace##_##className.MethodList, nameSpace##_##className##_##methodName##_name, & nameSpace :: className :: methodName ); \

#define REGISTER_SCRIPTED_CLASS_METHOD2( nameSpace, className, methodName, returnType, arg1, arg2, isConst ) \
	char nameSpace##_##className##_##methodName##_name[] = #methodName;\
	CMethodDescriptor< CClassDescriptor< nameSpace :: className > , CClassDescriptor< returnType >, CClassDescriptor< arg1 >, CClassDescriptor< arg2 >, CClassDescriptor< Void >, isConst >	nameSpace##_##className##_##methodName ( & nameSpace##_##className.MethodList, nameSpace##_##className##_##methodName##_name, & nameSpace :: className :: methodName  ); \

#define REGISTER_SCRIPTED_CLASS_METHOD3( nameSpace, className, methodName, returnType, arg1, arg2, arg3, isConst ) \
	char nameSpace##_##className##_##methodName##_name[] = #methodName;\
	CMethodDescriptor< CClassDescriptor< nameSpace :: className > , CClassDescriptor< returnType >, CClassDescriptor< arg1 >, CClassDescriptor< arg2 >, CClassDescriptor< arg3 >, isConst >	nameSpace##_##className##_##methodName ( & nameSpace##_##className.MethodList, nameSpace##_##className##_##methodName##_name, & nameSpace :: className :: methodName ); \


#endif
