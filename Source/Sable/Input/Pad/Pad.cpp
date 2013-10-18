#include <Sable/Input/Pad/Pad.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1( Sable, CPad, CPadInterface );

CPad::CPad() :
	m_Impl( *this )
{
}

CPad::~CPad()
{

}

Bool CPad::IsAvailable() const
{
	return m_Impl.IsAvailable();
}

Float32	CPad::GetAnalogButton( UInt32 id ) const
{
	return m_Impl.GetAnalogButton( id );
}

Bool CPad::GetButton( UInt32 id ) const
{
	return m_Impl.GetButton( id );
}

CVector2f CPad::GetAnalogStick( UInt32 id ) const
{
	return m_Impl.GetAnalogStick( id );
}

Void CPad::Update()
{
	m_Impl.Update();
}
