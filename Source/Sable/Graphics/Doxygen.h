/**
@defgroup Graphics Graphics
*/

// -------------------------------- //

/**
@defgroup GraphicsMaterial Graphics.Material
\ingroup Graphics
*/

/**
@defgroup GraphicsStates Graphics.States
\ingroup Graphics
*/

/**
@defgroup GraphicsShader Graphics.Shader
\ingroup Graphics
*/

/**
@defgroup GraphicsGeometry Graphics.Geometry
\ingroup Graphics
*/

/**
@defgroup GraphicsCommon Graphics.Common
\ingroup Graphics
*/

/**
@defgroup GraphicsText Graphics.Text
\ingroup Graphics
*/

/**
@defgroup GraphicsDebug Graphics.Debug
\ingroup Graphics
*/

/**
@defgroup GraphicsCamera Graphics.Camera
\ingroup Graphics
*/

/**
@defgroup GraphicsParticle Graphics.Particle
\ingroup Graphics
*/

/**
@defgroup GraphicsRenderer Graphics.Renderer
\ingroup Graphics
*/

/**
@defgroup GraphicsSceneGraph Graphics.Node
\ingroup Graphics
*/

/**
@defgroup GraphicsResource Graphics.Resource
\ingroup Graphics
*/

// -------------------------------- //

/**
@defgroup A Introduction.
\ingroup GraphicsShader

Here is an overview about how to use shader within the system.
\n This subsystem is mainly composed by 3 classes:
\t\n CShader
\t\n CShaderParameter
\t\n CShaderConnector
\n\n
CShaderConnector define a bridge to link the engine data to a particular CShaderParameter.
\n You can use CShaderConnector in two slightly diferents way:

<b>1. Automatic method</b>
\n First derive a class from CShaderConnector, then register a particular instance of your connector
using CGraphicsManager::RegisterShaderConnector.
\code 
GraphicsManager.RegisterShaderConnector( *myConnector );
\endcode
\n After that, each new loaded shader parse all the registered connector and bind it's parameter to the compliant connector.
\n This way, you do not have to care about explicitly bind conector to CShaderParameters, everything is done automaticly.

<b>2. Manual Method</b>
\n First derive a class from CShaderConnector, then use the method:
CShader::BindConnectors in order to bind the connector to every compliant parameters:
\code
	CMyConnector_Ptr
		myConnector = new CMyConnector;

	myShader->BindConnectors( *myConnector );
\endcode

*/

/**
@defgroup B Shader server
\ingroup GraphicsShader

Because each shader can only be used with a specific RendererPass 
( Mainly due to the type of data that the RendererPass can provide to the shader ),
it's necessary to find a way to 'specialize' each shader.
\n The Shader Server class is a member of each CRenderPass and is used to determine if a 
particular shader can be used with this CRenderPass.
\code
if( RendererPass->GetShaderServer().HasShader( shaderName ) )
{
	shader = RendererPass->GetShaderServer().CreateShader( shaderName );
	material.AddShader( *shader );
}
\endcode
*/

