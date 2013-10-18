#include <Sable/Graphics/PostProcess/ToneMapper.h>

#include <Sable/Graphics/RenderTarget/RenderTarget.h>
#include <Sable/Graphics/Shader/Connector.h>
#include <Sable/Graphics/Common/Manager.h>
#include <Sable/Graphics/Debug/GraphicCommandGroup.h>

#define CPostProcessToneMapper_LuminancePassTextureCount 6

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1( Sable, CPostProcessToneMapper, CPostProcess );

CPostProcessToneMapper::CPostProcessToneMapper( CRenderer& renderer ) :
    CPostProcess( renderer )
{
	m_ExposureValue = 0.28f; 
}

CPostProcessToneMapper::~CPostProcessToneMapper()
{

}

const CRenderTargetTexture& CPostProcessToneMapper::GetFinalLuminanceTexture() const
{
	return * m_LuminanceRenderTargetArray[ 0 ];
}

Void CPostProcessToneMapper::SetExposureValue( const Float32 exposure )
{
	m_ExposureValue = exposure;
}

Float32	CPostProcessToneMapper::GetExposureValue( ) const
{
	return m_ExposureValue;
}

Void CPostProcessToneMapper::LoadShader( )
{
	m_Shader = NEWOBJ( CShader, ( ) );
    m_Shader->Load( CoreManager.GetFileSystem().GetFilePath( "System/Shader", "PostProcess/ToneMapper/ToneMapper.vsh" ),
                    CoreManager.GetFileSystem().GetFilePath( "System/Shader", "PostProcess/ToneMapper/ToneMapper.psh" ),
                    CFilePath() );

	m_GreyScaleDownSampleShader = NEWOBJ( CShader, ( ) );
    m_GreyScaleDownSampleShader->Load(  CoreManager.GetFileSystem().GetFilePath( "System/Shader", "PostProcess/ToneMapper/GreyScaleAndDownSample.vsh" ),
                                        CoreManager.GetFileSystem().GetFilePath( "System/Shader", "PostProcess/ToneMapper/GreyScaleAndDownSample.psh" ),
                                        CFilePath() );

	m_DownSampleShader = NEWOBJ( CShader, ( ) );
    m_DownSampleShader->Load(   CoreManager.GetFileSystem().GetFilePath( "System/Shader", "PostProcess/ToneMapper/DownSample.vsh" ),
                                CoreManager.GetFileSystem().GetFilePath( "System/Shader", "PostProcess/ToneMapper/DownSample.psh" ),
                                CFilePath() );
}

Void	CPostProcessToneMapper::ProcessToneMappingPass( CRenderer& renderer )
{
/*	Bool
		itUseGlow;
	const CRenderTarget
		& rendererOutputRenderTarget = renderer.GetRenderTarget();
	CShader
		& shader = GetShader();
	CVector4f
		value;

	DebugAssert( rendererOutputRenderTarget.GetTypeInfo().IsKindOf( CRenderTargetTexture::GetStaticTypeInfo() ) );
	DebugAssert( GetShader( ).HasParameter( "Texture_OriginalScene" ) );
	DebugAssert( GetShader( ).HasParameter( "Texture_Luminance" ) );

	CShaderParameter
		& originalSceneTextureParameter = shader.GetParameter( "Texture_OriginalScene" );
	originalSceneTextureParameter.SetValue( CastReferenceToReference( rendererOutputRenderTarget , CRenderTargetTexture ) );
	
	CShaderParameter
		& tonMapperExposure = shader.GetParameter( "ToneMapper_Exposure" );
	value.Set( m_ExposureValue, 0, 0 ,0 );
	tonMapperExposure.SetValue( value );

	CShaderParameter
		& luminanceTextureParameter = shader.GetParameter( "Texture_Luminance" );
	luminanceTextureParameter.SetValue( GetFinalLuminanceTexture() );

	CShaderParameter
		& useGlow = shader.GetParameter( "ToneMapper_UseGlow" );
	useGlow.SetValue( itUseGlow );

	CShaderParameter
		& glowTexture0 = shader.GetParameter( "Texture_Glow_0" );
	CShaderParameter
		& glowTexture1 = shader.GetParameter( "Texture_Glow_1" );
	CShaderParameter
		& glowTexture2 = shader.GetParameter( "Texture_Glow_2" );
	CShaderParameter
		& glowTexture3 = shader.GetParameter( "Texture_Glow_3" );

	CMainRenderer
		& mainRenderer = CastReferenceToReference( renderer, CMainRenderer );
	const CPostProcessGlow
		& postProcessGlow = mainRenderer.GetPostProcessGlow();

	glowTexture0.SetValue( postProcessGlow.GetGlowTextureAtIndex( 0 ) );
	glowTexture1.SetValue( postProcessGlow.GetGlowTextureAtIndex( 1 ) );
	glowTexture2.SetValue( postProcessGlow.GetGlowTextureAtIndex( 2 ) );
	glowTexture3.SetValue( postProcessGlow.GetGlowTextureAtIndex( 3 ) );

	
	GetRenderTarget().Activate( TRUE , 0);

	shader.Activate( renderer );
	GraphicsManager.DrawFullScreenQuad( GetRenderTarget(), shader );
	shader.DeActivate(renderer);

	luminanceTextureParameter.SetValue( GetNullReference( CRenderTargetTexture ) );

	if( itUseGlow )
	{
		glowTexture0.SetValue( GetNullReference( CRenderTargetTexture ) );
		glowTexture1.SetValue( GetNullReference( CRenderTargetTexture )  );
		glowTexture2.SetValue( GetNullReference( CRenderTargetTexture )  );
		glowTexture3.SetValue( GetNullReference( CRenderTargetTexture )  );
	}

	originalSceneTextureParameter.SetValue( GetNullReference( CRenderTargetTexture )  );
	luminanceTextureParameter.SetValue( GetNullReference( CRenderTargetTexture )  );
    */

    DebugError( "Must be re implemented" );
    
}

Void CPostProcessToneMapper::ProcessLuminancePass( CRenderer& renderer  )
{
	DebugError("Need to be updated");
/*	Int32 textureIndex, textureCount;
	const CRenderTarget* rendererOutputRenderTarget = renderer.GetRenderTarget();

	DebugAssert( rendererOutputRenderTarget->GetTypeInfo().IsKindOf( CRenderTargetTexture::GetStaticTypeInfo() ) );

	ComputeTextureCoordinateOffset();

	textureCount = m_LuminanceRenderTargetArray.GetItemCount();
	
	m_GreyScaleDownSampleShader->GetParameter( "TextureCoordinate_Offset" )->SetValue( 
		m_TextureCoordinateOffset[ textureCount - 1 ] 
		);
	m_GreyScaleDownSampleShader->GetParameter( "Texture_Input0" )->SetValue( 
		*SafeCastRef( rendererOutputRenderTarget , CRenderTargetTexture ) 
		);

    m_LuminanceRenderTargetArray[ textureCount - 1 ]->Clear( CColor::Black );
	renderer.Activate( *m_LuminanceRenderTargetArray[ textureCount - 1 ] );
	renderer.Activate( *m_GreyScaleDownSampleShader );
	GraphicsManager.DrawFullScreenQuad(  renderer, *m_GreyScaleDownSampleShader );

	renderer.Activate( *m_DownSampleShader );
	for( textureIndex = textureCount - 2; textureIndex >= 0 ; textureIndex-- )
	{
        m_LuminanceRenderTargetArray[ textureIndex ]->Clear( CColor::Black );
		renderer.Activate( *m_LuminanceRenderTargetArray[ textureIndex ] );
		
		m_DownSampleShader->GetParameter( "TextureCoordinate_Offset" )->SetValue( 
			m_TextureCoordinateOffset[ textureIndex ] 
			);
		m_DownSampleShader->GetParameter( "Texture_Input0" )->SetValue( 
			*m_LuminanceRenderTargetArray[ textureIndex + 1  ] 
			);

		GraphicsManager.DrawFullScreenQuad( renderer, *m_DownSampleShader );

	}*/
}

Void CPostProcessToneMapper::Initialize( CRenderer& renderer, CRenderTarget* outputRenderTarget  )
{
	Int32
		textureIndex;
	Count
		textureCount;

	textureCount = CPostProcessToneMapper_LuminancePassTextureCount;

	m_TextureCoordinateOffset.SetItemCount( CPostProcessToneMapper_LuminancePassTextureCount );

	m_TextureCoordinateOffset[ textureCount - 1 ].SetItemCount( 4 );
	for( textureIndex = textureCount - 2; textureIndex >= 0 ; textureIndex-- )
	{
		m_TextureCoordinateOffset[ textureIndex ].SetItemCount( 9 );
	}

	LoadShader();
	CreateLuminanceRenderTarget( CPostProcessToneMapper_LuminancePassTextureCount );

	CPostProcess::Initialize( renderer, outputRenderTarget );
}

Void CPostProcessToneMapper::UnInitialize()
{
}

Void CPostProcessToneMapper::Execute( CRenderer& renderer )
{	
	DebugGraphicCommandGroup( "PostProcessToneMapper" );

	ProcessLuminancePass( renderer );

	ProcessToneMappingPass( renderer );

}

Void CPostProcessToneMapper::ComputeTextureCoordinateOffset( )
{
	Float32
		pixelWidth,
		pixelHeight;
	Int32
		xIndex,
		yIndex,
		currentOffset,
		textureIndex;
	Count
		textureCount;

	textureCount = m_LuminanceRenderTargetArray.GetItemCount();

	const CTextureInfo& textureInfo = m_LuminanceRenderTargetArray[ textureCount - 1 ]->GetInfo().TextureInfo;
	
	pixelWidth = 1.0f / (Float32) textureInfo.Width;
	pixelHeight = 1.0f / (Float32) textureInfo.Height;

	m_TextureCoordinateOffset[ textureCount - 1 ][ 0 ].Set( -0.5f * pixelWidth,  0.5f * pixelHeight, 0.0f, 0.0f );
	m_TextureCoordinateOffset[ textureCount - 1 ][ 1 ].Set(  0.5f * pixelWidth,  0.5f * pixelHeight, 0.0f, 0.0f );
	m_TextureCoordinateOffset[ textureCount - 1 ][ 2 ].Set( -0.5f * pixelWidth, -0.5f * pixelHeight, 0.0f, 0.0f );
	m_TextureCoordinateOffset[ textureCount - 1 ][ 3 ].Set(  0.5f * pixelWidth, -0.5f * pixelHeight, 0.0f, 0.0f );
 
	for( textureIndex = textureCount - 2; textureIndex >= 0 ; textureIndex-- )
	{
		const CTextureInfo& textureInfo = m_LuminanceRenderTargetArray[ textureIndex + 1 ]->GetInfo().TextureInfo;

		pixelWidth = 1.0f / (Float32) textureInfo.Width;
		pixelHeight = 1.0f / (Float32) textureInfo.Height;

		currentOffset = 0;
		for( xIndex = -1; xIndex < 2; xIndex++ )
		{
			for( yIndex = -1; yIndex < 2; yIndex++ )
			{
				m_TextureCoordinateOffset[ textureIndex ][ currentOffset++ ].Set(
					(Float32) xIndex * (Float32) pixelWidth ,
					(Float32) yIndex * (Float32) pixelHeight ,
					0.0f,   
					0.0f    
					);
			}
		}
	}


}

Void CPostProcessToneMapper::CreateLuminanceRenderTarget( const UInt32 renderTargetCount )
{
	UInt32
		textureIndex,
		renderTargetSize;

	m_LuminanceRenderTargetArray.SetItemCount( renderTargetCount );

	renderTargetSize = 1;

	for( textureIndex = 0; textureIndex < renderTargetCount; textureIndex++ )
	{
		m_LuminanceRenderTargetArray[ textureIndex ] = NEWOBJ( CRenderTargetTexture, ( ) );
		m_LuminanceRenderTargetArray[ textureIndex ]->Create( CRenderTargetInfo( renderTargetSize, renderTargetSize, nTextureFormat_G16R16F, nMultiSamplingQuality_None ) );
		m_LuminanceRenderTargetArray[ textureIndex ]->SetMagFilterMode( nStateFilter_Linear );
		m_LuminanceRenderTargetArray[ textureIndex ]->SetMinFilterMode( nStateFilter_Linear );

		renderTargetSize =  renderTargetSize * 3;
	}

}
