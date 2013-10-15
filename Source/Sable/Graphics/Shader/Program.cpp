#include <Sable\Graphics\Shader\Program.h>

#include <Sable\Graphics\Common\Manager.h>
#include <Sable\Graphics\Shader\Parameter.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1_ALLOC( Sable, CShaderProgram, CManagedObject );

/**
*/
CShaderProgram::CShaderProgram( ) :
    m_Impl( *this )
{
    m_Type = nShaderProgramType_None;
}

CShaderProgram::~CShaderProgram()
{

}

EShaderProgramType CShaderProgram::GetType( ) const
{
    return m_Type;
}

Void CShaderProgram::SetType( EShaderProgramType type )
{
    m_Type = type;
}

CImplShaderProgram& CShaderProgram::GetImpl()
{
    return m_Impl;
}

Bool CShaderProgram::SetRawDataFromFile( const CFilePath& path )
{
    if( path.Exist() == FALSE )
        return FALSE;

    Sable::CShaderCompiler compiler;
    if( !compiler.Compile( GetType(), path ) )
    {
		CoreManager.GetLog().LogError( "Failed to compile shader program: %s:\n\t%s", path.GetBuffer(), compiler.GetErrorString() );
        return FALSE;
    }

    // Set raw data
    Sable::CBuffer byteCodeBuffer;
    byteCodeBuffer.Open( compiler.GetByteCode(), nAccesMode_Read );
    return SetRawData( byteCodeBuffer );
}

Bool CShaderProgram::SetRawData( CIODevice& device, UInt32 byteCount )
{
    if( byteCount == 0 )
        m_RawData.SetItemCount( device.GetSize() );
    else
        m_RawData.SetItemCount( byteCount );

    return device.Read( m_RawData.GetBuffer(), m_RawData.GetItemCount() );
}

Bool CShaderProgram::Load( const CFilePath& path )
{
    if( path.Exist() == FALSE )
        return FALSE;

    if( SetRawDataFromFile( path ) )
        return Load( );

    return FALSE;
}

/**
Load a specific shader program.

This method load the file specified by SetFilePath or the file speficied at construct time
*/
Bool CShaderProgram::Load( )
{
    if( m_RawData.GetItemCount() )
    {
        DebugAssert( m_Type != nShaderProgramType_None );

        if( m_Impl.Initialize( ) )
        {
            return TRUE;
        }
    }

    return FALSE;
}

const CArray<Byte>& CShaderProgram::GetRawData() const
{
    return m_RawData;
}

Bool CShaderProgram::Serialize( CPersistentArchive& ar )
{
	Int16 version = 0;

	if( ar.BeginScope( WT("ShaderProgram" ), version ) == version )
	{
        UInt32 byteCount = m_RawData.GetItemCount();
        ar.Serialize( (Int32&) m_Type, WT("Type") );
        ar.Serialize( byteCount, WT("RawDataSize" ) );
        if( ar.IsLoading() )
        {
            m_RawData.SetItemCount( byteCount );
        }

        ar.Serialize( m_RawData.GetBuffer(), byteCount, WT("RawData" ) );

		if( ar.IsLoading() )
		{
			Load();
		}

        ar.EndScope();

		return CManagedObject::Serialize( ar );
	}

    return FALSE;
}

Void CShaderProgram::Activate( CRenderer& renderer )
{
    m_Impl.Activate();
}
