#include <Sable/Core/ManagedObject/ObjectMethod.h>

using namespace Sable;

CObjectMethod::CObjectMethod()
{
    m_Method = NULL;
    m_Object = NULL;
}

CObjectMethod::CObjectMethod( CManagedObject& object, MethodPtr method)
{
    m_Method = method;
    m_Object = &object;
}

Bool CObjectMethod::operator==( const CObjectMethod& om ) const
{
    return ( m_Object == om.m_Object ) && ( m_Method == om.m_Method );
}

CObjectMethod& CObjectMethod::operator=( const CObjectMethod& other )
{
    m_Object = other.m_Object;
    m_Method = other.m_Method;
    return *this;
}

Int32 CObjectMethod::Call()
{
    if( m_Object )
        return (m_Object->*m_Method)(NULL, 0);
    
    return 0;
}

Int32 CObjectMethod::Call(Void** args, UInt16 argCount)
{
    if( m_Object )
        return (m_Object->*m_Method)(args, argCount);
    
    return 0;
}
