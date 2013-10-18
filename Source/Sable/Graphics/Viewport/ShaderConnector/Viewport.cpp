#include <Sable/Graphics/Viewport/ShaderConnector/Viewport.h>


using namespace Sable;

IMPLEMENT_MANAGED_CLASS1( Sable, CShaderConnectorViewport, CShaderSystemConnector );
	
String CShaderConnectorViewport::ParametersName[CShaderConnectorViewport::nSemantic_Count] =
{ 
	"SC_ViewportInfo"
};

CShaderConnectorViewport::CShaderConnectorViewport( CViewport& vp ) :
    CShaderSystemConnector( )
{
	m_Viewport = &vp;
	m_Hashes[nSemantic_ViewportInfo] = StringGetHashCode( ParametersName[nSemantic_ViewportInfo] );
}

CShaderConnectorViewport::~CShaderConnectorViewport()
{

}

Bool CShaderConnectorViewport::GetItSupportParameter( const CShaderParameter& param )const
{
	UInt32 i;
	for( i=0;i<nSemantic_Count;i++ )
	{
		if( param.GetNameHash() == m_Hashes[i] )
		{
			if( StringCompare( param.GetName(), ParametersName[i] ) == 0 )
				return TRUE;
		}
	}

	return FALSE;
}

Void CShaderConnectorViewport::EvaluateParameterValue( const CShaderParameter& param, CVector4f& data ) const
{
	if( param.GetNameHash() == m_Hashes[nSemantic_ViewportInfo] )
	{
		data.SetX( (Float32)m_Viewport->GetWidth() );
		data.SetY( (Float32)m_Viewport->GetHeight() );
		data.SetZ( data.GetY() / data.GetX() );
	}
}
