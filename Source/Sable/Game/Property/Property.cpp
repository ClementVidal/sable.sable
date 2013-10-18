#include <Sable/Game/Property/Property.h>

using namespace Sable;

CGameProperty::CGameProperty( )
{

}

CGameProperty::CGameProperty( EType type )
{
}

CGameProperty::~CGameProperty()
{
}

Float32	CGameProperty::GetAsFloat() const
{
	return m_FloatValue;
}

Int32 CGameProperty::GetAsInt() const
{
	return m_IntValue;
}

Bool CGameProperty::GetAsBool() const
{
	return m_BoolValue;
}

const CVector2f& CGameProperty::GetAsVector2() const
{
	return (const CVector2f&) m_Tuple2fValue;
}

const CVector3f& CGameProperty::GetAsVector3() const
{
	return (const CVector3f&) m_Tuple3fValue;
}

const CVector4f& CGameProperty::GetAsVector4() const
{
	return (const CVector4f&) m_Tuple4fValue;
}

Void CGameProperty::SetAsFloat( Float32 d )
{
	m_FloatValue = d;
}

Void CGameProperty::SetAsInt( Int32 d )
{
	m_BoolValue = d;
}

Void CGameProperty::SetAsBool( Bool d )
{
	m_BoolValue = d;
}

Void CGameProperty::SetAsVector2( const CVector2f& d)
{
	m_Tuple2fValue.x = d.GetX();
	m_Tuple2fValue.y = d.GetY();
}

Void CGameProperty::SetAsVector3( const CVector3f& d)
{
	m_Tuple3fValue.x = d.GetX();
	m_Tuple3fValue.y = d.GetY();
	m_Tuple3fValue.z = d.GetZ();
}

Void CGameProperty::SetAsVector4( const CVector4f& d )
{
	m_Tuple4fValue.x = d.GetX();
	m_Tuple4fValue.y = d.GetY();
	m_Tuple4fValue.z = d.GetZ();
	m_Tuple4fValue.w = d.GetW();
}