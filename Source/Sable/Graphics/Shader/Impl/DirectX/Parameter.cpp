#include <Sable/Graphics/Shader/Impl/DirectX/Parameter.h>

using namespace Sable;

CImplDirectXShaderParameter::CImplDirectXShaderParameter( CShaderParameter& publicImpl ) :
    CImplStubShaderParameter( publicImpl )
{
	m_Program = NULL;
}

CImplDirectXShaderParameter::~CImplDirectXShaderParameter()
{
}


Void CImplDirectXShaderParameter::SetProgram( CImplDirectXShaderProgram& p )
{
	m_Program = &p;
}

CImplDirectXShaderProgram& CImplDirectXShaderParameter::GetProgram()
{
	return *m_Program;
}