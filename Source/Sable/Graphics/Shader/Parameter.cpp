#include <Sable\Graphics\Shader\Parameter.h>
#include <Sable\Graphics\Shader\Shader.h>
#include <Sable\Graphics\Shader\Connector.h>
#include <Sable\Core\ManagedObject\Ref.h>

using namespace Sable;

CShaderParameter::CShaderParameter( ) :
	m_Impl( *this )
{
	m_OwnerShader = NULL;
	m_ArraySize = -1;
}

CShaderParameter::~CShaderParameter()
{

}

CImplShaderParameter& CShaderParameter::GetImpl()
{
	return m_Impl;
}

CShaderParameter& CShaderParameter::operator = (const CShaderParameter& p ) 
{
	m_Name = p.m_Name;
	m_NameHash = p.m_NameHash;
	m_Type = p.m_Type;
	m_ArraySize = p.m_ArraySize;
	m_OwnerShader = p.m_OwnerShader;

	return *this;
}

Void CShaderParameter::SetShader( CShader& shader )
{
	m_OwnerShader = &shader;
}

Void CShaderParameter::SetValue( const CShaderParameterData& data )
{
	DebugAssert( m_OwnerShader != NULL );

	m_OwnerShader->GetImpl().SetParameterValue( *this, data );
}
