#include <Sable\Graphics\States\DepthStencil.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1_ALLOC( Sable, CStatesDepthStencil, CManagedObject );

CStatesDepthStencil::SDesc::SDesc()
{
	DepthTestEnable = TRUE;
	DepthWriteEnable = TRUE;
	DepthFunc = nStateDepthFunc_LessEqual;
}

CStatesDepthStencil::CStatesDepthStencil() :
    m_Impl( *this )
{

}

CStatesDepthStencil::~CStatesDepthStencil()
{

}

const CStatesDepthStencil::SDesc& CStatesDepthStencil::GetDesc() const
{
	return m_Desc;
}

Void CStatesDepthStencil::Activate( CRenderer& renderer )
{
	DebugGraphicCommandGroup( "CStatesDepthStencil::Activate" );
    m_Impl.Activate();
}

CImplStatesDepthStencil& CStatesDepthStencil::GetImpl()
{
    return m_Impl;
}

Void CStatesDepthStencil::Acquire( const SDesc& desc )
{
	m_Desc = desc;
    m_Impl.Acquire();
}

Bool CStatesDepthStencil::Serialize( CPersistentArchive& ar )
{
	Int16 version = 0;

	if( ar.BeginScope( WT("StatesDepthStencil" ), version ) == version )
	{
		ar.Serialize( m_Desc.DepthTestEnable, WT("TestEnable") );
		ar.Serialize( m_Desc.DepthWriteEnable, WT("WriteEnable") );
		ar.Serialize( (UInt32&) m_Desc.DepthFunc, WT("DepthFunc") );

		return CManagedObject::Serialize( ar );
	}
	return FALSE;
}

