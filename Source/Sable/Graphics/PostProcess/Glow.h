#ifndef _GRAPHICS_POSTPROCESS_GLOW_
#define _GRAPHICS_POSTPROCESS_GLOW_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/ManagedObject/Macro.h>
#include <Sable/Core/ManagedObject/ManagedObject.h>
#include <Sable/Graphics/PostProcess/PostProcess.h>
#include <Sable/Core/String/StaticString.h>
#include <Sable/Graphics/States/Header.h>

#define BLUR_PASS_COUNT 2
#define BLUR_KERNEL_WIDTH 5

namespace Sable
{

class CRenderer;
class CShader;
class CRenderTarget;
class CRenderTargetTexture;

/** 
Render Pipeline.
*/
class CPostProcessGlow : public CPostProcess
{

	DEFINE_MANAGED_CLASS( CPostProcessGlow );

public:

	/** @name Constructor Destructor*/
	//@{
	CPostProcessGlow( CRenderer& renderer );
	~CPostProcessGlow();
	//@}
	
	/** @name Operator*/
    //@{
    //@}

	/** @name Accessors*/
	//@{
	Float32	GetGlowWidth( ) const ;
	Void	SetGlowWidth( const Float32 width );
	Float32 GetGlowIntensity() const;
	Void	SetGlowIntensity( const Float32 intensity );

	const CRenderTargetTexture& GetGlowTextureAtIndex( const Index index ) const;

	Void	SetSource(const CRenderTarget& target);
	CRenderTarget&	GetSource();
	//@}

	/** @name Manipulator*/
    //@{
	Void Initialize( CRenderer& renderer, CRenderTarget* outputRenderTarget = NULL );
	virtual Void Render( CRenderer& renderer );
	//@}
	
private:	

	// Type
	
	// Method
	Void CreateRenderTarget( const CRenderer& renderer );
	Void LoadShader();
	Void ComputeTextureCoordinateOffsetAndGaussianWeight();

	Void ProcessBluringPasses( CRenderer& renderer );
	Void ProcessDownSamplePasses( CRenderer& renderer );
	Float32 ComputeGaussianWeight( const Float32 x, const Float32 mean, const Float32 standardDeviation );
	Void OutputRenderTarget( CRenderer& renderer );
	
	//Attribute
	CShader								m_DownSamplePassShader;
	CShader								m_OutputPass;
	CShader								m_BlurPassShader;
	CStatesDepthStencil					m_DepthStencilStates;
	CStatesBlend						m_BlendStates;

	CRenderTargetTexture				m_DownSamplePassRenderTarget;
	CArray<CVector4f>                    m_DownSamplePassTextureCoordinateOffset;


	CRenderTargetTexture					m_HBlurPassRenderTargetTable[BLUR_PASS_COUNT];
	CRenderTargetTexture					m_VBlurPassRenderTargetTable[BLUR_PASS_COUNT];
	CArray<CVector4f>						m_HBlurTextureCoordinateOffset[BLUR_PASS_COUNT];
	CArray<CVector4f>						m_VBlurTextureCoordinateOffset[BLUR_PASS_COUNT];
	CArray<Float32>							m_BlurPassGaussianWeight;
	Float32									m_GlowIntensity;
	Float32									m_GlowWidth;

	CArray<CVector4f>						m_OutputPassTextureCoordinateOffset;


	CRef<CRenderTarget>                 m_Source;

};

Inline
Float32 CPostProcessGlow::GetGlowIntensity() const
{
	return m_GlowIntensity;
}

Inline
Void	CPostProcessGlow::SetGlowIntensity( const Float32 intensity )
{
	m_GlowIntensity = intensity;
}

Inline
Float32	CPostProcessGlow::GetGlowWidth( ) const 
{
	return m_GlowWidth;
}

Inline
Void CPostProcessGlow::SetGlowWidth( const Float32 width )
{
	m_GlowWidth = width; 
}

Inline
Void CPostProcessGlow::SetSource(const CRenderTarget& target)
{
	m_Source = &target;
}

Inline
CRenderTarget& CPostProcessGlow::GetSource()
{
	return *m_Source;
}

}

#endif
