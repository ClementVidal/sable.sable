#include <Sable/Graphics/Shader/Impl/DirectX/Shader.h>

using namespace Sable;

CImplDirectXShader::CImplDirectXShader( CShader& publicImpl ) :
    CImplStubShader( publicImpl )
{
}

CImplDirectXShader::~CImplDirectXShader()
{
}

Bool CImplDirectXShader::Initialize( )
{
    return TRUE;
}

Void CImplDirectXShader::Activate( )
{
	if( m_PublicImpl->GetVertexShaderProgram() )
		m_PublicImpl->GetVertexShaderProgram()->GetImpl().Activate();

	if( m_PublicImpl->GetPixelShaderProgram() )
		m_PublicImpl->GetPixelShaderProgram()->GetImpl().Activate();

	if( m_PublicImpl->GetGeometryShaderProgram() )
		m_PublicImpl->GetGeometryShaderProgram()->GetImpl().Activate();
}

UInt32 CImplDirectXShader::GetParameterCount( )
{
	UInt32 pCount = 0;

	if( m_PublicImpl->GetVertexShaderProgram() )
		pCount += m_PublicImpl->GetVertexShaderProgram()->GetImpl().GetParameterCount();

	if( m_PublicImpl->GetPixelShaderProgram() )
		pCount += m_PublicImpl->GetPixelShaderProgram()->GetImpl().GetParameterCount();

	if( m_PublicImpl->GetGeometryShaderProgram() )
		pCount += m_PublicImpl->GetGeometryShaderProgram()->GetImpl().GetParameterCount();

    return pCount;
}

Void CImplDirectXShader::GetParameterNameAtIndex( UInt32 index, CStaticString<64>& name )
{
	CShaderProgram* vs = m_PublicImpl->GetVertexShaderProgram();
	CShaderProgram* ps = m_PublicImpl->GetPixelShaderProgram();
	CShaderProgram* gs = m_PublicImpl->GetGeometryShaderProgram();

	Int32 vsPCount = (vs?vs->GetImpl().GetParameterCount():0);
	Int32 psPCount = (ps?ps->GetImpl().GetParameterCount():0);
	Int32 gsPCount = (gs?gs->GetImpl().GetParameterCount():0);

	if( vs && (Int32)index < vsPCount )
	{
		vs->GetImpl().GetParameterNameAtIndex( index, name );
	}
	else if( vs && ps && ( (Int32)index - vsPCount )  < psPCount )
	{
		vs->GetImpl().GetParameterNameAtIndex( index, name );
	}
	else if( vs && ps && gs && ( (Int32)index - vsPCount - psPCount ) < gsPCount )
	{
		vs->GetImpl().GetParameterNameAtIndex( index, name );
	}
}

EShaderParameterType CImplDirectXShader::GetParameterDataType( String semantic )
{
	CShaderProgram* vs = m_PublicImpl->GetVertexShaderProgram();
	CShaderProgram* ps = m_PublicImpl->GetPixelShaderProgram();
	CShaderProgram* gs = m_PublicImpl->GetGeometryShaderProgram();

	if(vs)
	{
		return vs->GetImpl().GetParameterDataType( semantic );
	}
	else if(ps)
	{
		return ps->GetImpl().GetParameterDataType( semantic );
	}
	else if(gs)
	{
		return gs->GetImpl().GetParameterDataType( semantic );
	}

    return nShaderParameterType_None;
}

UInt8 CImplDirectXShader::GetParameterArraySize( String semantic )
{
    return 0;
}


Void CImplDirectXShader::SetParameterValue( const CShaderParameter& parameter, const CShaderParameterData& data) 
{
	CImplDirectXShaderProgram& program = const_cast<CShaderParameter&>(parameter).GetImpl().GetProgram();

	return program.SetParameterValue( parameter, data );
}

Void CImplDirectXShader::ParseParameters()
{
	m_PublicImpl->m_ParameterMap.ClearAllItems();

	if( m_PublicImpl->GetVertexShaderProgram() )
		m_PublicImpl->GetVertexShaderProgram()->GetImpl().ParseParameters( *this );

	if( m_PublicImpl->GetPixelShaderProgram() )
		m_PublicImpl->GetPixelShaderProgram()->GetImpl().ParseParameters( *this );

	if( m_PublicImpl->GetGeometryShaderProgram() )
		m_PublicImpl->GetGeometryShaderProgram()->GetImpl().ParseParameters( *this );
}