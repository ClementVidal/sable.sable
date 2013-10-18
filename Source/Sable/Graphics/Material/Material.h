#ifndef _GRAPHICS_MATERIAL_METERIAL_
#define _GRAPHICS_MATERIAL_METERIAL_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Graphics/Material/Parameter.h>
#include <Sable/Graphics/Renderer/Header.h>
#include <Sable/Graphics/Shader/Connector.h>

#include <Sable/Graphics/States/Blend.h>
#include <Sable/Graphics/States/DepthStencil.h>
#include <Sable/Graphics/States/Rasterizer.h>

#define MATERIAL_MAX_SHADER 4

namespace Sable
{

class CRenderPass;
class CTexture;
class CShaderParameter;

/** 
\ingroup GraphicsMaterial
Store material specific parameters.

*/
class CMaterial : public CShaderConnector
{

    DEFINE_MANAGED_CLASS( CMaterial );

public:

    /** @name Constructor/Destructor*/
    //@{
    CMaterial();
    ~CMaterial();
    //@}

    /** @name Operator*/
    //@{
    //@}

    /** @name Accessors*/
    //@{
	Void					SetShader( CShader* sh );
    CShader*				GetShader( ) const;
    Void                    AddParameter( String name );
    CMaterialParameter*     GetParameter( String name );

	Void					SetParameterValue( String name, const CMaterialParameter& data );
	Void					SetParameterValue( String name, const Float32 data );
	Void					SetParameterValue( String name, const STuple2f& data );
	Void					SetParameterValue( String name, const STuple3f& data );
	Void					SetParameterValue( String name, const STuple4f& data );
	Void					SetParameterValue( String name, const CVector2f& data );
	Void					SetParameterValue( String name, const CVector3f& data );
	Void					SetParameterValue( String name, const CVector4f& data );
	Void					SetParameterValue( String name, const CColor& data );
	Void					SetParameterValue( String name, const Int32 data );
	Void					SetParameterValue( String name, const CTexture2D& data );
	Void					SetParameterValue( String name, const CTexture3D& data );
	Void					SetParameterValue( String name, const CTextureCube& data );
	Void					SetParameterValue( String name, const CStatesSampler& data );	

    Bool                    IsOpaque() const;
    //@}
    
    /** @name Manipulator*/
    //@{
	Void	Load();
	Bool	Serialize( CPersistentArchive& ar );
    Void    RemoveAllParameters();
    //@}

	/** @name System*/
	//@{
	Void	FlushParametersValues( CShader& shader ) const;
    //@}

private:
    
	// DataType
    typedef CList< CMaterialParameter > ParameterTable;

    // Methods

    // Attributes
    ParameterTable	                    m_ParameterTable;
	CRef<CShader>						m_Shader;
    
};


}
#endif
