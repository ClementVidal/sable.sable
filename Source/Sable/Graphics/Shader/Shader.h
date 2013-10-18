#ifndef _SABLE_GRAPHICS_SHADER_SHADER_
#define _SABLE_GRAPHICS_SHADER_SHADER_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/String/StaticString.h>
#include <Sable/Core/Collection/HashTable.h>
#include <Sable/Graphics/Common/DataTypes.h>
#include <Sable/Graphics/Shader/Connector.h>

#include <Sable/Graphics/States/Blend.h>
#include <Sable/Graphics/States/DepthStencil.h>
#include <Sable/Graphics/States/Sampler.h>
#include <Sable/Graphics/States/Rasterizer.h>

#include <Sable/Graphics/Shader/Parameter.h>
#include <Sable/Graphics/Shader/Impl/Header.h>

namespace Sable
{

class CShaderConnector;
class CRenderer;
class CShaderParameter;
class CIODevice;

/** 
\ingroup GraphicsShader
Bas class of the shader system.
\n\n
Package: Graphics
*/
class CShader : public CManagedObject
{

    DEFINE_MANAGED_CLASS( CShader ); 

public:

    /** @name Type*/
    //@{
	typedef CMap< CStringIdentifier, CShaderParameter > ParameterMap;
    //@}
    
    /** @name Constructor/Destructor*/
    //@{
    CShader( );
    ~CShader();
    //@}
    
    /** @name Operator*/
    //@{
    //@}
    
    /** @name Accessors*/
    //@{
	CImplShader&					GetImpl();
	Void							SetBlendStates( CStatesBlend* s );
	Void							SetDepthStencilStates( CStatesDepthStencil* s );
	Void							SetRasterizerStates( CStatesRasterizer* s );

    Void        					SetPixelShaderProgram( CShaderProgram* program );
    Void					        SetVertexShaderProgram( CShaderProgram* program );
    Void					        SetGeometryShaderProgram( CShaderProgram* program );

	CShaderProgram*					GetPixelShaderProgram( ) const;
	CShaderProgram*					GetVertexShaderProgram( ) const;
	CShaderProgram*					GetGeometryShaderProgram( ) const;

    CStatesBlend*					GetBlendStates( ) const;
	CStatesDepthStencil*			GetDepthStencilStates( ) const;
	CStatesRasterizer*				GetRasterizerStates( ) const;

	CShaderParameter*				GetParameter( String name );
	const ParameterMap&				GetParameterMap() const;
    //@}
    
    /** @name Manipulator*/
    //@{
    Bool                Load( );
    Bool                Load( const CFilePath& vertexShaderProgramPath, const CFilePath& pixelShaderProgramPath, const CFilePath& geometryShaderProgramPath );

	Bool				Serialize( CPersistentArchive& ar );
    //@}
    
private:
    
	// Friendship 
	friend class CRenderer;
	friend class CImplGLESShader;
	friend class CImplDirectXShaderProgram;
	friend class CImplDirectXShader;

    // Types
    
    // Method
	Void    Activate( CRenderer& renderer );

	// Attribute	
	ParameterMap                m_ParameterMap;
	CImplShader					m_Impl;
	CRef<CStatesBlend>			m_StatesBlend;
	CRef<CStatesRasterizer>		m_StatesRasterizer;
	CRef<CStatesDepthStencil>	m_StatesDepthStencil;

    CRef<CShaderProgram>        m_PixelShader;
    CRef<CShaderProgram>        m_VertexShader;
    CRef<CShaderProgram>        m_GeometryShader;

};

}

#endif
