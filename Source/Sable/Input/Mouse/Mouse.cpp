#include <Sable/Input/Mouse/Mouse.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1( Sable, CMouse, CMouseInterface );

CMouse::CMouse( CApplicationWindow& window ) :
    CMouseInterface( window ),
	m_Impl( *this )
{
}

CMouse::~CMouse()
{

}

Void CMouse::Update()
{
	m_Impl.Update();
}
