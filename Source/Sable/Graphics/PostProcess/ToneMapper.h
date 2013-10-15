#ifndef _GRAPHICS_POSTPROCESS_TONEMAPPER_
#define _GRAPHICS_POSTPROCESS_TONEMAPPER_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\ManagedObject\Macro.h>
#include <Sable\Core\ManagedObject\ManagedObject.h>
#include <Sable\Core\Collection\Array.h>

#include <Sable\Graphics\PostProcess\PostProcess.h>
#include <Sable\Core\ManagedObject\Ref.h>

namespace Sable
{

class CRenderer;

/** 
Render Pipeline.
*/
class CPostProcessToneMapper : public CPostProcess
{

	DEFINE_MANAGED_CLASS( CPostProcessToneMapper );

public:

	/** @name Constructor Destructor*/
	//@{
	CPostProcessToneMapper( CRenderer& renderer );
	virtual ~CPostProcessToneMapper();
	//@}
	
	/** @name Operator*/
    //@{
    //@}

	/** @name Accessor*/
	//@{
	CShader&					GetShader() const { return *m_Shader; }
	Void						SetShader( const CShader& shader ) { m_Shader = &shader; }
	const CRenderTargetTexture& GetFinalLuminanceTexture() const;
	Void						SetExposureValue( const Float32 exposure );
	Float32						GetExposureValue( ) const;
	//@}

	/** @name Manipulator*/
    //@{
	virtual Void Execute( CRenderer& renderer );
	virtual Void Initialize( CRenderer& renderer, CRenderTarget* outputRenderTarget = NULL );
	virtual Void UnInitialize();
	//@}
	
private:	

	// Type
	
	// Method
	Void	LoadShader();
	Void	CreateLuminanceRenderTarget( const UInt32 renderTargetCount );
	Void	ProcessLuminancePass( CRenderer& renderer );
	Void	ProcessToneMappingPass( CRenderer& renderer );
	Void	ComputeTextureCoordinateOffset( );
	
	//Attribute
	CArray< CRef<CRenderTargetTexture> >	m_LuminanceRenderTargetArray;
	CRef<CShader>							m_GreyScaleDownSampleShader;
	CRef<CShader>							m_DownSampleShader;
	CRef<CShader>							m_Shader;
	CArray< CArray< CVector4f > >		m_TextureCoordinateOffset;
	Float32								m_ExposureValue;

};


}

#endif
