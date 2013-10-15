#include <Sable\Graphics\Camera\ShaderConnector\Camera.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1( Sable, CShaderConnectorCamera, CShaderSystemConnector );

const char* ParametersName[CShaderConnectorCamera::nSemantic_Count] =
{ 
	"SC_CameraPosition", 
	"SC_CameraDirection"
	"SC_ViewProjectionMatrix",
	"SC_ViewMatrix",
	"SC_ViewITMatrix",
};

CShaderConnectorCamera::CShaderConnectorCamera( CCamera& camera ):
	CShaderSystemConnector( )
{
	m_Camera = &camera;	
	m_Hashes[nSemantic_Position] = StringGetHashCode( ParametersName[nSemantic_Position] );
	m_Hashes[nSemantic_Direction] = StringGetHashCode( ParametersName[nSemantic_Direction] );
	m_Hashes[nSemantic_ViewProjectionMatrix] = StringGetHashCode( ParametersName[nSemantic_ViewProjectionMatrix] );
	m_Hashes[nSemantic_ViewMatrix] = StringGetHashCode( ParametersName[nSemantic_ViewMatrix] );
	m_Hashes[nSemantic_ViewITMatrix] = StringGetHashCode( ParametersName[nSemantic_ViewITMatrix] );
}

CShaderConnectorCamera::CShaderConnectorCamera( ):
    CShaderSystemConnector( )
{
	m_Hashes[nSemantic_Position] = StringGetHashCode( ParametersName[nSemantic_Position] );
	m_Hashes[nSemantic_Direction] = StringGetHashCode( ParametersName[nSemantic_Direction] );
	m_Hashes[nSemantic_ViewProjectionMatrix] = StringGetHashCode( ParametersName[nSemantic_ViewProjectionMatrix] );
	m_Hashes[nSemantic_ViewMatrix] = StringGetHashCode( ParametersName[nSemantic_ViewMatrix] );
	m_Hashes[nSemantic_ViewITMatrix] = StringGetHashCode( ParametersName[nSemantic_ViewITMatrix] );
}

CShaderConnectorCamera::~CShaderConnectorCamera()
{

}

Bool CShaderConnectorCamera::GetItSupportParameter( const CShaderParameter& param )const
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

Void CShaderConnectorCamera::EvaluateParameterValue( const CShaderParameter& param, CMatrix4x4f& data ) const
{
	if( param.GetNameHash() == m_Hashes[nSemantic_ViewProjectionMatrix] )
	{
		const CMatrix4x4f& view = m_Camera->GetViewMatrix();
		const CMatrix4x4f& projection = m_Camera->GetProjectionMatrix();

		data =  view * projection ;
	}
	else if( param.GetNameHash() == m_Hashes[nSemantic_ViewMatrix] )
	{
		data = m_Camera->GetViewMatrix();
	}
	else if( param.GetNameHash() == m_Hashes[nSemantic_ViewITMatrix] )
	{
		data = m_Camera->GetViewMatrix();
		data.Invert();
		data.Transpose();
	}
}

Void CShaderConnectorCamera::EvaluateParameterValue( const CShaderParameter& param, CVector3f& data ) const
{
	if( param.GetNameHash() == m_Hashes[nSemantic_Direction] )
	{
		data = m_Camera->GetCameraDirection();
    }
	else if( param.GetNameHash() == m_Hashes[nSemantic_Position] )	
	{
		data = m_Camera->GetCameraPosition();
	}
}
