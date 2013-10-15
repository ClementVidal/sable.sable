#include <Sable\Graphics\Material\Helper.h>

#include <Sable\Graphics\Material\Header.h>

using namespace Sable;


Bool CMaterialHelper::CreateFlatMaterial( CMaterial& material, CTexture2D& texture )
{
	CShader* shader = NEWOBJ( CShader, () );
	shader->Load(	CoreManager.GetFileSystem().GetFilePath( "System/Shader", "RendererPass/Default/Flat.vsh" ),
					CoreManager.GetFileSystem().GetFilePath( "System/Shader", "RendererPass/Default/Flat.psh" ),
					CFilePath() );


	CStatesSampler::SDesc desc;
	CStatesSampler* stateSampler = NEWOBJ( CStatesSampler, () );
	stateSampler->Acquire( desc );

	CMaterialParameter* param = NULL;
	material.SetShader( shader );
	material.AddParameter( "Texture" );
	material.SetParameterValue( "Texture", texture );
	material.AddParameter( "AmbientColor" );
	material.SetParameterValue( "AmbientColor", CColor::Black );
	material.AddParameter( "Sampler" );
	material.SetParameterValue( "Sampler", *stateSampler );

	return TRUE;
}