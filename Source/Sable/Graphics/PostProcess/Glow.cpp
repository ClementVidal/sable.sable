#include <Sable\Graphics\PostProcess\Glow.h>

#include <Sable\Core\Math\Primitives.h>

#include <Sable\Graphics\RenderTarget\Texture.h>
#include <Sable\Graphics\Shader\Shader.h>
#include <Sable\Graphics\Debug\GraphicCommandGroup.h>

using namespace Sable;


IMPLEMENT_MANAGED_CLASS1( Sable, CPostProcessGlow, CPostProcess );

CPostProcessGlow::CPostProcessGlow( CRenderer& renderer ) :
    CPostProcess( renderer )
{
	m_GlowIntensity = 1.0f;
	m_GlowWidth = 1.0f;
}

Void CPostProcessGlow::Initialize( CRenderer& renderer, CRenderTarget* outputRenderTarget )
{
    Index textureIndex;

	m_OutputPassTextureCoordinateOffset.SetItemCount( BLUR_PASS_COUNT + 1 );
	m_DownSamplePassTextureCoordinateOffset.SetItemCount( 16 );

    LoadShader();
    CreateRenderTarget( renderer );

	m_BlurPassGaussianWeight.SetItemCount( 5 );
    for( textureIndex = 0; textureIndex < BLUR_PASS_COUNT ; textureIndex++ )
    {
	    m_HBlurTextureCoordinateOffset[ textureIndex ].SetItemCount( 5 );
	    m_VBlurTextureCoordinateOffset[ textureIndex ].SetItemCount( 5 );
    }

    CPostProcess::Initialize( renderer, outputRenderTarget );
}


CPostProcessGlow::~CPostProcessGlow()
{

}

const CRenderTargetTexture& CPostProcessGlow::GetGlowTextureAtIndex( const Index index ) const
{
	return m_VBlurPassRenderTargetTable[ index ];
}

Float32 CPostProcessGlow::ComputeGaussianWeight( const Float32 x, const Float32 mean, const Float32 standardDeviation )
{
    /*    
                                                     -(x - mean)^2
                                                     -------------
                                    1.0               2*stdDev^2
        f(x,mean,stdDev) = -------------------- * e^
                            sqrt(2*pi*stdDev^2)

    */
    
    return ( 1.0f / MathSqrt( 2.0f * MathPi * standardDeviation * standardDeviation ) ) 
            * MathExponential( (-((x-mean)*(x-mean)))/(2.0f * standardDeviation * standardDeviation) );
}

Void CPostProcessGlow::ComputeTextureCoordinateOffsetAndGaussianWeight()
{
	Float32
		pixelWidth,
		pixelHeight,
		gaussianPosition;
	Int32
		offsetIndex,
		textureIndex,
		i,
		j;


	// down sample pass
	const CTextureInfo& downSamplePassTextureInfo = m_DownSamplePassRenderTarget.GetInfo().TextureInfo;

	pixelWidth = 1.0f / (Float32) downSamplePassTextureInfo.Width;
	pixelHeight = 1.0f / (Float32) downSamplePassTextureInfo.Height;

	//pixelWidth +=  pixelWidth / 2.0f;
	//pixelHeight +=  pixelHeight / 2.0f;

	offsetIndex = 0;
	for( i = -2; i < 2; i++ )
	{
		for( j = -2; j < 2; j++ )
		{
			m_DownSamplePassTextureCoordinateOffset[ offsetIndex++ ].Set( 
				( ( Float32 ) i ) * pixelWidth, 
				( ( Float32 ) j ) * pixelHeight, 
				0.0f, 
				0.0f 
				);
		}
	}

	// blur pass
	for( textureIndex = 0; textureIndex < BLUR_PASS_COUNT ; textureIndex++ )
	{
		const CTextureInfo& blurPassTextureInfo = m_HBlurPassRenderTargetTable[ textureIndex ].GetInfo().TextureInfo;

		pixelWidth = 1.0f / (Float32) blurPassTextureInfo.Width;
		pixelHeight = 1.0f / (Float32) blurPassTextureInfo.Height;

		//pixelWidth +=  pixelWidth / 2.0f;
		//pixelHeight +=  pixelHeight / 2.0f;

		for( i = 0; i < 5; i++ )
		{
			m_HBlurTextureCoordinateOffset[ textureIndex ][ i ].Set( ( ( Float32 ) i - 2.0f ) * pixelWidth, 0.0f, 0.0f, 0.0f );
			m_VBlurTextureCoordinateOffset[ textureIndex ][ i ].Set( 0.0f, ( ( Float32 ) i - 2.0f) * pixelHeight, 0.0f, 0.0f );
		}
	}

	for( i = 0; i < 5; i++ )
	{
		gaussianPosition = ( ( Float32 ) i - 2.0f ) / 2.0f;
		m_BlurPassGaussianWeight[ i ] = m_GlowIntensity * ComputeGaussianWeight( gaussianPosition, 0.0f, m_GlowWidth ) ;
	}
}

Void CPostProcessGlow::ProcessBluringPasses( CRenderer& renderer )
{
	DebugGraphicCommandGroup( "CPostProcessGlow::ProcessBluringPasses" );

	Index textureIndex;
	CRenderTargetTexture* inputTextureHPass = &m_DownSamplePassRenderTarget;
	CRenderTargetTexture* inputTextureVPass = &m_HBlurPassRenderTargetTable[ 0 ];

	for( textureIndex = 0; textureIndex < BLUR_PASS_COUNT; textureIndex++ )
	{
		char tmp[256];
		StringSetFormattedText( tmp, 256, "CPostProcessGlow::ProcessDownSamplePasses - Pass %d", textureIndex );
		DebugGraphicCommandGroup( tmp );
		{
			DebugGraphicCommandGroup( "CPostProcessGlow::ProcessDownSamplePasses - HPass" );

			// Horizontal first blur pass
			m_BlurPassShader.GetParameter( "InputTexture" )->SetValue( 
				*inputTextureHPass 
				);
			m_BlurPassShader.GetParameter( "TextureCoordinateOffset" )->SetValue( 
				m_HBlurTextureCoordinateOffset[ textureIndex ]
			);
			m_BlurPassShader.GetParameter( "GaussianWeight" )->SetValue( 
				m_BlurPassGaussianWeight
				);

            m_HBlurPassRenderTargetTable[ textureIndex ].Clear( CColor::Black );
			renderer.Activate( m_HBlurPassRenderTargetTable[ textureIndex ] );
			GraphicsManager.DrawFullScreenQuad( renderer, m_BlurPassShader );
		}

		{
			DebugGraphicCommandGroup( "CPostProcessGlow::ProcessDownSamplePasses - VPass" );

			// Vertical first blur pass
			m_BlurPassShader.GetParameter( "InputTexture" )->SetValue( 
				*inputTextureVPass
				);
			m_BlurPassShader.GetParameter( "TextureCoordinateOffset" )->SetValue( 
				m_VBlurTextureCoordinateOffset[ textureIndex ]
			);
			m_BlurPassShader.GetParameter( "GaussianWeight" )->SetValue( 
				m_BlurPassGaussianWeight
				);

            m_VBlurPassRenderTargetTable[ textureIndex ].Clear( CColor::Black );
			renderer.Activate( m_VBlurPassRenderTargetTable[ textureIndex ] );
			GraphicsManager.DrawFullScreenQuad( renderer, m_BlurPassShader );	
		}

		if( textureIndex + 1 < BLUR_PASS_COUNT )
		{
			inputTextureHPass = &m_VBlurPassRenderTargetTable[ textureIndex ];
			inputTextureVPass = &m_HBlurPassRenderTargetTable[ textureIndex + 1];
		}
	}
}

Void CPostProcessGlow::OutputRenderTarget( CRenderer& renderer )
{
	DebugGraphicCommandGroup( "CPostProcessGlow::OutputRenderTarget" );

    GetRenderTarget()->Clear( CColor::Black );
	renderer.Activate( *GetRenderTarget() );

	Char semantic[64];
	UInt32 i;
	for( i=0;i<BLUR_PASS_COUNT;i++)
	{
		StringSetFormattedText( semantic, 64, "Texture_Glow_%d", i );
		CShaderParameter* glowTexture = m_OutputPass.GetParameter( semantic );
		glowTexture->SetValue( GetGlowTextureAtIndex( i ) );
	}

	CShaderParameter& particleTextureParameter = *m_OutputPass.GetParameter( "Texture_OriginalScene" );
	particleTextureParameter.SetValue( *SafeCastRef( m_Source, CRenderTargetTexture ) );

	m_OutputPass.GetParameter( "TextureCoordinateOffset" )->SetValue( 
		m_OutputPassTextureCoordinateOffset
		);
	GraphicsManager.DrawFullScreenQuad( renderer, m_OutputPass );
}

Void CPostProcessGlow::ProcessDownSamplePasses( CRenderer& renderer )
{
	DebugGraphicCommandGroup( "CPostProcessGlow::ProcessDownSamplePasses" );

	m_DownSamplePassShader.GetParameter( "TextureCoordinateOffset" )->SetValue( 
		m_DownSamplePassTextureCoordinateOffset
		);
	m_DownSamplePassShader.GetParameter( "InputTexture" )->SetValue( 
		* SafeCastRef( m_Source , CRenderTargetTexture ) 
		);

    m_DownSamplePassRenderTarget.Clear( CColor::Black );
	renderer.Activate( m_DownSamplePassRenderTarget );
	GraphicsManager.DrawFullScreenQuad( renderer, m_DownSamplePassShader );
}

Void CPostProcessGlow::Render( CRenderer& renderer )
{
	DebugGraphicCommandGroup( "CPostProcessGlow::Render" );

	ComputeTextureCoordinateOffsetAndGaussianWeight();
	ProcessDownSamplePasses( renderer );
	ProcessBluringPasses( renderer );

	OutputRenderTarget(renderer);
}

Void CPostProcessGlow::LoadShader( )
{
	m_DownSamplePassShader.Load(    CoreManager.GetFileSystem().GetFilePath( "System/Shader", "PostProcess/Glow/DownSamplePass.vsh" ),
                                    CoreManager.GetFileSystem().GetFilePath( "System/Shader", "PostProcess/Glow/DownSamplePass.psh" ),
                                    CFilePath() );

    m_BlurPassShader.Load(  CoreManager.GetFileSystem().GetFilePath( "System/Shader", "PostProcess/Glow/BlurPass.vsh" ),
                            CoreManager.GetFileSystem().GetFilePath( "System/Shader", "PostProcess/Glow/BlurPass.psh" ),
                            CFilePath() );

    m_OutputPass.Load(  CoreManager.GetFileSystem().GetFilePath( "System/Shader", "PostProcess/Glow/OutputPass.vsh" ),
                        CoreManager.GetFileSystem().GetFilePath( "System/Shader", "PostProcess/Glow/OutputPass.psh" ),
                        CFilePath() );

	CStatesDepthStencil::SDesc dsDesc;
	dsDesc.DepthTestEnable = FALSE;
	dsDesc.DepthWriteEnable = FALSE;
	m_DepthStencilStates.Acquire( dsDesc );

	CStatesBlend::SDesc blendDesc;
	blendDesc.BlendEnable[0] = TRUE;
	blendDesc.SrcColorBlend = nStateBlend_SrcAlpha;
	blendDesc.DstColorBlend = nStateBlend_InvSrcAlpha;
	m_BlendStates.Acquire( blendDesc );

	{
		m_DownSamplePassShader.SetDepthStencilStates( &m_DepthStencilStates );
		m_BlurPassShader.SetDepthStencilStates( &m_DepthStencilStates );
		m_OutputPass.SetDepthStencilStates( &m_DepthStencilStates );

		m_DownSamplePassShader.SetBlendStates( &m_BlendStates );
		m_BlurPassShader.SetBlendStates( &m_BlendStates );
		m_OutputPass.SetBlendStates( &m_BlendStates );
	}
}

Void CPostProcessGlow::CreateRenderTarget( const CRenderer& renderer )
{
	Index
		renderTargetIndex;
	UInt32
		renderTargetWidth,
		renderTargetHeight;

	DebugAssert("Render target size must be set with a valid size");

	renderTargetWidth = 0;//renderer.GetRenderTarget()->GetWidth();
	renderTargetHeight = 0;//renderer.GetRenderTarget()->GetHeight();

	m_OutputPassTextureCoordinateOffset[ 0 ].Set( 1.0f/renderTargetWidth, 1.0f/renderTargetHeight, 0.0f, 0.0f );

	renderTargetWidth /= 2;
	renderTargetHeight /= 2;

	m_DownSamplePassRenderTarget.Create( CRenderTargetInfo( renderTargetWidth, renderTargetHeight, nTextureFormat_R8G8B8A8, nMultiSamplingQuality_None ) );
	m_DownSamplePassRenderTarget.SetMagFilterMode( nStateFilter_Linear );
	m_DownSamplePassRenderTarget.SetMinFilterMode( nStateFilter_Linear );

	for( renderTargetIndex = 0; renderTargetIndex < BLUR_PASS_COUNT; renderTargetIndex ++ )
	{
		m_HBlurPassRenderTargetTable[ renderTargetIndex ].Create( CRenderTargetInfo( renderTargetWidth, renderTargetHeight, nTextureFormat_R8G8B8A8, nMultiSamplingQuality_None  ) );
		m_HBlurPassRenderTargetTable[ renderTargetIndex ].SetMagFilterMode( nStateFilter_Linear );
		m_HBlurPassRenderTargetTable[ renderTargetIndex ].SetMinFilterMode( nStateFilter_Linear );

		m_VBlurPassRenderTargetTable[ renderTargetIndex ].Create( CRenderTargetInfo( renderTargetWidth, renderTargetHeight, nTextureFormat_R8G8B8A8, nMultiSamplingQuality_None  ) );
		m_VBlurPassRenderTargetTable[ renderTargetIndex ].SetMagFilterMode( nStateFilter_Linear );
		m_VBlurPassRenderTargetTable[ renderTargetIndex ].SetMinFilterMode( nStateFilter_Linear );

		m_OutputPassTextureCoordinateOffset[ renderTargetIndex + 1].Set( 1.0f/renderTargetWidth, 1.0f/renderTargetHeight, 0.0f, 0.0f );
	
		renderTargetWidth /= 2;
		renderTargetHeight /= 2;
	}
}
