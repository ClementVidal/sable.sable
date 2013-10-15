#include <Sable\Graphics\Shader\Shader.h>

#include <Sable\Graphics\Common\Manager.h>
#include <Sable\Graphics\Shader\Parameter.h>
#include <Sable\Graphics\Renderer\Header.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1_ALLOC( Sable, CShader, CManagedObject );


/**
Create a shader object without loading or compiling any shader code.
This can be done afterward using the CShader::Load() method
*/
CShader::CShader( ) :
	m_Impl( *this )
{
}

CShader::~CShader()
{

}


CImplShader& CShader::GetImpl()
{
	return m_Impl;
}

Bool CShader::Load( const CFilePath& vertexShaderProgramPath, const CFilePath& pixelShaderProgramPath, const CFilePath& geometryShaderProgramPath )
{
    if( vertexShaderProgramPath.Exist() )
    {
        m_VertexShader = NEWOBJ( CShaderProgram, () );
        m_VertexShader->SetType( nShaderProgramType_Vertex );
        if( !m_VertexShader->Load( vertexShaderProgramPath ) )
            return FALSE;
    }

    if( pixelShaderProgramPath.Exist() )
    {
        m_PixelShader = NEWOBJ( CShaderProgram, () );
        m_PixelShader->SetType( nShaderProgramType_Pixel );
        if( !m_PixelShader->Load( pixelShaderProgramPath ) )
            return FALSE;
    }

    if( geometryShaderProgramPath.Exist() )
    {
        m_GeometryShader = NEWOBJ( CShaderProgram, () );
        m_GeometryShader->SetType( nShaderProgramType_Geometry );
        if( !m_GeometryShader->Load( geometryShaderProgramPath ) )
            return FALSE;
    }

	m_Impl.Initialize();
	m_Impl.ParseParameters();

    return TRUE;
}


/**
Load a specific shader program.

This method load the file specified by SetFilePath or the file speficied at construct time
*/
Bool CShader::Load( )
{
    if( m_PixelShader )
        if( !m_PixelShader->Load() )
            return FALSE;

    if( m_VertexShader )
        if( !m_VertexShader->Load() )
            return FALSE;

    if( m_GeometryShader )
        if( !m_GeometryShader->Load() )
            return FALSE;

	m_Impl.Initialize();
	m_Impl.ParseParameters();

    return TRUE;
}

Bool CShader::Serialize( CPersistentArchive& ar )
{
	Int16 version = 0;

	if( ar.BeginScope( WT("Shader" ), version ) == version )
	{
		ar.Serialize( m_StatesBlend, WT("StatesBlend") );
		ar.Serialize( m_StatesRasterizer, WT("StatesRasterizer") );
		ar.Serialize( m_StatesDepthStencil, WT("StatesDepthStencil") );
		ar.Serialize( m_VertexShader, WT("VertexShader") );
		ar.Serialize( m_PixelShader, WT("PixelShader") );
        ar.Serialize( m_GeometryShader, WT("GeometryShader") );

        ar.EndScope();

		return CManagedObject::Serialize( ar );
	}
	return FALSE;
}

Void CShader::Activate( CRenderer& renderer )
{
	DebugProfile("CShader::Activate");
	DebugGraphicCommandGroup( "CShader::Activate" );

    if( m_StatesBlend )
        renderer.Activate(*m_StatesBlend);

	if( m_StatesRasterizer )
		renderer.Activate(*m_StatesRasterizer);

	if( m_StatesDepthStencil )
		renderer.Activate(*m_StatesDepthStencil);

    m_Impl.Activate();
}

Void CShader::SetBlendStates( CStatesBlend* s )
{
    m_StatesBlend = s;
}

Void CShader::SetDepthStencilStates( CStatesDepthStencil* s )
{
    m_StatesDepthStencil = s;
}

Void CShader::SetRasterizerStates( CStatesRasterizer* s )
{
    m_StatesRasterizer = s;
}

CStatesBlend* CShader::GetBlendStates( ) const
{
    return m_StatesBlend;
}

CShaderParameter* CShader::GetParameter( String name ) 
{
	return m_ParameterMap.GetItemPtr( name );
}

const CShader::ParameterMap& CShader::GetParameterMap() const
{
	return m_ParameterMap;
}

CStatesDepthStencil* CShader::GetDepthStencilStates( ) const
{
    return m_StatesDepthStencil;
}

CStatesRasterizer* CShader::GetRasterizerStates( ) const
{
    return m_StatesRasterizer;
}

CShaderProgram*	CShader::GetPixelShaderProgram( ) const
{
    return m_PixelShader;
}

CShaderProgram* CShader::GetVertexShaderProgram( ) const
{
    return m_VertexShader;
}

CShaderProgram* CShader::GetGeometryShaderProgram( ) const
{
    return m_GeometryShader;
}

Void CShader::SetPixelShaderProgram( CShaderProgram* program ) 
{
    m_PixelShader = program;
}

Void CShader::SetVertexShaderProgram( CShaderProgram* program ) 
{
    m_VertexShader = program;
}

Void CShader::SetGeometryShaderProgram( CShaderProgram* program ) 
{
    m_GeometryShader = program;
}