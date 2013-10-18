#include <Sable/Graphics/Node/ShaderConnector/Node.h>

#include <Sable/Graphics/Common/Manager.h>
#include <Sable/Graphics/Node/Render.h>
#include <Sable/Graphics/Camera/Camera.h>
#include <Sable/Graphics/Renderer/Renderer.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1( Sable, CShaderConnectorGraphNode, CShaderSystemConnector );

const char* CShaderConnectorGraphNode::ParametersName[CShaderConnectorGraphNode::nSemantic_Count] =
{ 
	"SC_WorldMatrix", 
	"SC_WorldIMatrix",
	"SC_WorldITMatrix",
	"SC_ItUseInstancing"
};

CShaderConnectorGraphNode::CShaderConnectorGraphNode( CNodeRender& node ):
    CShaderSystemConnector( )
{
	m_Node = & node;
	m_Hashes[nSemantic_WorldMatrix] = StringGetHashCode( ParametersName[nSemantic_WorldMatrix] );
	m_Hashes[nSemantic_WorldIMatrix] = StringGetHashCode( ParametersName[nSemantic_WorldIMatrix] );
	m_Hashes[nSemantic_WorldITMatrix] = StringGetHashCode( ParametersName[nSemantic_WorldITMatrix] );
	m_Hashes[nSemantic_ItUseInstancing] = StringGetHashCode( ParametersName[nSemantic_ItUseInstancing] );

	DebugAssert( CheckHashesUniqueness( m_Hashes, nSemantic_Count ) );
}

CShaderConnectorGraphNode::~CShaderConnectorGraphNode()
{

}

Bool CShaderConnectorGraphNode::GetItSupportParameter( const CShaderParameter& param )const
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

Void CShaderConnectorGraphNode::EvaluateParameterValue( const CShaderParameter& param, Bool& data ) const
{

}

Void CShaderConnectorGraphNode::EvaluateParameterValue( const CShaderParameter& param, CMatrix4x4f& data ) const
{
	CMatrix4x4f worldMatrix = m_Node->GetWorldMatrix();

	if( param.GetNameHash() == m_Hashes[nSemantic_WorldMatrix] )
	{
		data = worldMatrix;
	}
	else if( param.GetNameHash() == m_Hashes[nSemantic_WorldIMatrix] )
	{
		data = worldMatrix;
		data.Invert();
	}
	else if( param.GetNameHash() == m_Hashes[nSemantic_WorldITMatrix] )
	{
		data = worldMatrix;
		data.Invert();
		data.Transpose();
	}
}
