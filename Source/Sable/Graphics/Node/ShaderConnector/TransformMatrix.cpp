#include <Sable/Graphics/Node/ShaderConnector/TransformMatrix.h>

#include <Sable/Graphics/Common/Manager.h>
#include <Sable/Graphics/Node/Render.h>
#include <Sable/Graphics/Camera/Camera.h>
#include <Sable/Graphics/Renderer/Renderer.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1( Sable, CShaderConnectorTransformMatrix, CShaderSystemConnector );

const char* CShaderConnectorTransformMatrix::ParametersName[CShaderConnectorTransformMatrix::nSemantic_Count] =
{ 
	"SC_WorldViewProjectionMatrix",
	"SC_WorldViewITMatrix",
};

CShaderConnectorTransformMatrix::CShaderConnectorTransformMatrix( CNodeSpatial& node, CCamera& camera ):
    CShaderSystemConnector( )
{
	m_Camera = &camera;
	m_Node = &node;

	m_Hashes[nSemantic_WorldViewProjectionMatrix] = StringGetHashCode( ParametersName[nSemantic_WorldViewProjectionMatrix] );
	m_Hashes[nSemantic_WorldViewITMatrix] = StringGetHashCode( ParametersName[nSemantic_WorldViewITMatrix] );

	DebugAssert( CheckHashesUniqueness( m_Hashes, nSemantic_Count ) );
}
	
CShaderConnectorTransformMatrix::CShaderConnectorTransformMatrix( ):
	CShaderSystemConnector( )
{
	m_Camera = NULL;
	m_Node = NULL;

	m_Hashes[nSemantic_WorldViewProjectionMatrix] = StringGetHashCode( ParametersName[nSemantic_WorldViewProjectionMatrix] );
	m_Hashes[nSemantic_WorldViewITMatrix] = StringGetHashCode( ParametersName[nSemantic_WorldViewITMatrix] );

	DebugAssert( CheckHashesUniqueness( m_Hashes, nSemantic_Count ) );
}

CShaderConnectorTransformMatrix::~CShaderConnectorTransformMatrix()
{

}

Void CShaderConnectorTransformMatrix::Set( CNodeSpatial& node, CCamera& camera )
{
	m_Camera = &camera;
	m_Node = &node;
}

Bool CShaderConnectorTransformMatrix::GetItSupportParameter( const CShaderParameter& param )const
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

Void CShaderConnectorTransformMatrix::EvaluateParameterValue( const CShaderParameter& param, CMatrix4x4f& data ) const
{
	DebugAssert( m_Node && m_Camera );
	if( param.GetNameHash() == m_Hashes[nSemantic_WorldViewProjectionMatrix] )
	{
		const CMatrix4x4f& world = m_Node->GetWorldMatrix();
		const CMatrix4x4f& viewProj = m_Camera->GetViewProjectionMatrix();

		data = world * viewProj ;
	}
	else if( param.GetNameHash() == m_Hashes[nSemantic_WorldViewITMatrix] )
	{
		const CMatrix4x4f& world = m_Node->GetWorldMatrix();
		const CMatrix4x4f& view = m_Camera->GetViewMatrix();

		data = world * view  ;

		data.Invert();
		data.Transpose();
	}
}
