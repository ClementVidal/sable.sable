#include <Sable/Graphics/States/Blend.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1_ALLOC( Sable, CStatesBlend, CManagedObject );

CStatesBlend::SDesc::SDesc()
{
	for(UInt32 i=0;i<8;i++ )
	{
		BlendEnable[i] = FALSE;
		WriteMask[i] = nStateWriteMask_Red | nStateWriteMask_Green | nStateWriteMask_Blue | nStateWriteMask_Alpha;
	}

	SrcColorBlend = nStateBlend_SrcAlpha;
	DstColorBlend = nStateBlend_InvSrcAlpha;
	ColorBlendOp = nStateBlendOp_Add;

	SrcAlphaBlend = nStateBlend_One;
	DstAlphaBlend = nStateBlend_Zero;
	AlphaBlendOp = nStateBlendOp_Add;
}

CStatesBlend::CStatesBlend() :
    m_Impl( *this )
{
}

CStatesBlend::~CStatesBlend()
{

}

Void CStatesBlend::Activate( CRenderer& renderer )
{
	DebugGraphicCommandGroup( "CStatesBlend::Activate" );
    m_Impl.Activate();
}

Void CStatesBlend::Acquire( const SDesc& desc )
{
	m_Desc = desc;
    m_Impl.Acquire();
}

CImplStatesBlend& CStatesBlend::GetImpl()
{
    return m_Impl;
}

const  CStatesBlend::SDesc& CStatesBlend::GetDesc() const
{
	return m_Desc;
}

Bool CStatesBlend::Serialize( CPersistentArchive& ar )
{
	Int16 version = 0;
    CStaticString<32> str;
    WChar buffer[32];

	if( ar.BeginScope( WT("StatesBlend" ), version ) == version )
	{
        for(UInt32 i=0;i<8;i++)
        {
            str.WriteFormattedText( "BlendEnable_%d", i);
            StringToWString( str.GetBuffer(), buffer, 32 );
		    ar.Serialize( m_Desc.BlendEnable[i], buffer );

            str.WriteFormattedText( "WriteMask_%d", i);
            StringToWString( str.GetBuffer(), buffer, 32 );
		    ar.Serialize( m_Desc.WriteMask[i], buffer );
        }
		ar.Serialize( (UInt32&) m_Desc.SrcColorBlend, WT("SrcColorBlend") );
		ar.Serialize( (UInt32&) m_Desc.DstColorBlend, WT("DstColorBlend") );
		ar.Serialize( (UInt32&) m_Desc.SrcAlphaBlend, WT("SrcAlphaBlend") );
		ar.Serialize( (UInt32&) m_Desc.DstAlphaBlend, WT("DstAlphaBlend") );
		ar.Serialize( (UInt32&) m_Desc.ColorBlendOp, WT("ColorBlendOp") );
		ar.Serialize( (UInt32&) m_Desc.AlphaBlendOp, WT("AlphaBlendOp") );
 
		return CManagedObject::Serialize( ar );
	}
	return FALSE;
}
