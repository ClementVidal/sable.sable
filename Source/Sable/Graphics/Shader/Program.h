#ifndef _SABLE_GRAPHICS_SHADER_PROGRAM_
#define _SABLE_GRAPHICS_SHADER_PROGRAM_

#include <Sable\Core\Common\DataTypes.h>

#include <Sable\Graphics\Shader\Shader.h>
#include <Sable\Graphics\Shader\Impl\Header.h>

namespace Sable
{


/** 
\ingroup GraphicsShader
Package: Graphics
*/
class CShaderProgram : public CManagedObject
{

    DEFINE_MANAGED_CLASS( CShaderProgram ); 

public:
   
    /** @name Constructor/Destructor*/
    //@{
    CShaderProgram( );
    ~CShaderProgram();
    //@}
    
    /** @name Operator*/
    //@{
    //@}
    
    /** @name Accessors*/
    //@{
    EShaderProgramType              GetType() const;
    Void                            SetType( EShaderProgramType type );
    Bool                            SetRawDataFromFile( const CFilePath& path );
	Bool							SetRawData( CIODevice& device, UInt32 byteCount = 0 );
    const CArray<Byte>&             GetRawData() const;
    CImplShaderProgram&				GetImpl();
    //@}
    
    /** @name Manipulator*/
    //@{
    Bool                Load( );
    Bool                Load( const CFilePath& path );
    CShaderParameter*   GetParameter( String name ) const ;
	Bool				Serialize( CPersistentArchive& ar );
    //@}
    
private:
    
	// Friendship 
	friend class CRenderer;

    // Types
    
    // Method
	Void    Activate( CRenderer& renderer );

    // Attribute	
	CArray<Byte>				m_RawData;
    EShaderProgramType          m_Type;
	CImplShaderProgram          m_Impl;

};

}

#endif
