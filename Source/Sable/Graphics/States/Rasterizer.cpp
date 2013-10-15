#include <Sable\Graphics\States\Rasterizer.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1_ALLOC( Sable, CStatesRasterizer, CManagedObject );

CStatesRasterizer::SDesc::SDesc()
{
	FillMode = nStateFillMode_Solid;
	CullMode = nStateCullMode_CCW;
	MultiSamplingEnabled = FALSE;
	ScissorRectEnabled = FALSE;
	DepthBias = 0.0f;
}

CStatesRasterizer::CStatesRasterizer() :
    m_Impl( *this )
{
}

CStatesRasterizer::~CStatesRasterizer()
{

}

const CStatesRasterizer::SDesc& CStatesRasterizer::GetDesc() const
{
	return m_Desc;
}

Void CStatesRasterizer::Activate( CRenderer& renderer )
{
	DebugGraphicCommandGroup( "CStatesRasterizer::Activate" );

    m_Impl.Activate();
}

CImplStatesRasterizer& CStatesRasterizer::GetImpl()
{
    return m_Impl;
}

Bool CStatesRasterizer::Serialize( CPersistentArchive& ar )
{
	Int16 version = 0;
	CStaticString<32> str;

	if( ar.BeginScope( WT("StatesRasterizer" ), version ) == version )
	{
		ar.Serialize( (UInt32&) m_Desc.FillMode, WT("FillMode") );
		ar.Serialize( (UInt32&) m_Desc.CullMode, WT("CullMode") );
		ar.Serialize( (UInt32&) m_Desc.MultiSamplingEnabled, WT("MultiSamplingEnabled") );

		if(! CManagedObject::Serialize( ar ) )
			return FALSE;

		ar.EndScope();

		Acquire( m_Desc );
	}
	return FALSE;
}

Void CStatesRasterizer::Acquire( const SDesc& desc )
{
	m_Desc = desc;
    m_Impl.Acquire( );
}