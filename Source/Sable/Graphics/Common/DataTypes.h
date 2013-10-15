#ifndef _CORE_GRAPHICS_DATATYPES_
#define _CORE_GRAPHICS_DATATYPES_

/** \file Sable\Graphics\Common\DataTypes.h
Graphics data types*/


/**
Shader program type 
*/
enum EShaderProgramType
{
    nShaderProgramType_Vertex = 0,
    nShaderProgramType_Pixel,
    nShaderProgramType_Geometry,
    nShaderProgramType_Count,
    nShaderProgramType_None = -1
};

/**
Shader parameter type 
*/
enum EShaderParameterType
{
	nShaderParameterType_Float32 = 0,
	nShaderParameterType_Float32Array,
	nShaderParameterType_Int32,
	nShaderParameterType_Matrix4x4,
	nShaderParameterType_Vector2,
	nShaderParameterType_Vector2Array,
	nShaderParameterType_Vector3,
	nShaderParameterType_Vector3Array,
	nShaderParameterType_Vector4,
	nShaderParameterType_Vector4Array,
	nShaderParameterType_Bool,
	nShaderParameterType_Texture1d,
	nShaderParameterType_Texture2d,
	nShaderParameterType_Texture3d,
	nShaderParameterType_TextureCube,
	nShaderParameterType_Sampler,
	nShaderParameterType_RenderTargetTexture, 
	nShaderParameterType_Count,
	nShaderParameterType_None = -1
};

enum ELightType
{
	nLightType_PointLight = 0,
	nLightType_PerspectiveLight,
	nLightType_OrthographicLight,
	nLightType_Count,
	nLightType_None = -1

};

/**
Valid back buffer format
*/
enum EBackBufferFormat
{	
	nBackBufferFormat_R5G6B5 = 0,
	nBackBufferFormat_X8R8G8B8,		
	nBackBufferFormat_Count,
	nBackBufferFormat_None = -1
};

/**
Texture type 
*/
enum ETextureType
{
	nTextureType_1D = 1,
	nTextureType_2D,
	nTextureType_3D,
	nTextureType_Cube,
	nTextureType_Count,
	nTextureType_None = -1
};

/**
Valid texture format
*/
enum ETextureFormat
{
	nTextureFormat_A8			= 0,
	nTextureFormat_L8,
	nTextureFormat_R5G6B5,		
    nTextureFormat_R8G8B8,
	nTextureFormat_R8G8B8A8,		
	nTextureFormat_X8R8G8B8,		
	nTextureFormat_A2R10G10B10,
	nTextureFormat_D24S8,			
	nTextureFormat_R16F,
	nTextureFormat_A16B16G16R16F, 
	nTextureFormat_G16R16F,

	nTextureFormat_DXT1, // Everything above that are compressed format 
	nTextureFormat_DXT2,
	nTextureFormat_DXT3,
	nTextureFormat_DXT4,
	nTextureFormat_DXT5,
	nTextureFormat_ETC, //Ericsson Texture Compression
	nTextureFormat_ATC, //AMD Texture Compression
	nTextureFormat_3DC, //ATI2 Texture Compression
	nTextureFormat_PVRTC, //Power vr Texture Compression
	nTextureFormat_Count,
	nTextureFormat_None = -1

};

enum EMultiSamplingQuality
{
    nMultiSamplingQuality_1=0,		
    nMultiSamplingQuality_2,
    nMultiSamplingQuality_3,
    nMultiSamplingQuality_4,
    nMultiSamplingQuality_Count,
    nMultiSamplingQuality_None = -1
};

enum EBufferAcces
{
	nBufferAcces_Read=0,		
	nBufferAcces_Write,		
	nBufferAcces_ReadWrite, 
	nBufferAcces_ReadAppend,
	nBufferAcces_Append,
	nBufferAcces_Count,
	nBufferAcces_None = -1
};


/**  
\ingroup GraphicsStates
Rasterizer states
*/
enum EStateCullMode
{
	nStateCullMode_CW = 0,
	nStateCullMode_CCW,
    nStateCullMode_Disabled,
	nStateCullMode_Count,
	nStateCullMode_None = -1
};

/**  
\ingroup GraphicsStates
Rasterizer states
*/
enum EStateFillMode
{
	nStateFillMode_Point = 1,
	nStateFillMode_WireFrame = 1,
	nStateFillMode_Solid,
	nStateFillMode_Count,
	nStateFillMode_None = -1
};

/**  
\ingroup GraphicsStates
Sampler states
*/
enum EStateFilter
{
	nStateFilter_Point = 1,
	nStateFilter_Linear ,
	nStateFilter_Anisotropic ,
	nStateFilter_Count,
	nStateFilter_None = -1
};

/**  
\ingroup GraphicsStates
Sampler states
*/
enum EStateAddress
{
	nStateAddress_Wrap = 1,
	nStateAddress_Mirror ,
	nStateAddress_Clamp ,
	nStateAddress_Count,
	nStateAddress_None = -1
};

/**  
\ingroup GraphicsStates
Blend states
*/
enum EStateBlendOp
{
	nStateBlendOp_Add = 1,
	nStateBlendOp_Substract,
	nStateBlendOp_RevSubstract,
	nStateBlendOp_Min,
	nStateBlendOp_Max,
	nStateBlendOp_Count,
	nStateBlendOp_None = -1
};

/**  
\ingroup GraphicsStates
Blend states
*/
enum EStateBlend
{
	nStateBlend_Zero = 1,
	nStateBlend_One ,
	nStateBlend_SrcColor ,
	nStateBlend_InvSrcColor ,
	nStateBlend_SrcAlpha ,
	nStateBlend_InvSrcAlpha ,
	nStateBlend_DestAlpha ,
	nStateBlend_InvDestAlpha ,
	nStateBlend_DestColor ,
	nStateBlend_InvDestColor ,
	nStateBlend_Count,
	nStateBlend_None = -1
};

/**  
\ingroup GraphicsStates
Blend states
*/
enum EStateWriteMask
{
	nStateWriteMask_Red = ( 1 << 0 ),
	nStateWriteMask_Green = ( 1 << 1 ),
	nStateWriteMask_Blue = ( 1 << 2 ),
	nStateWriteMask_Alpha = ( 1 << 3 ),
};

/**  
\ingroup GraphicsStates
DepthStencil states
*/
enum EStateDepthFunc
{
    nStateDepthFunc_Never,
    nStateDepthFunc_Less,
    nStateDepthFunc_Equal,
    nStateDepthFunc_LessEqual,
    nStateDepthFunc_Greater,
    nStateDepthFunc_Count,
    nStateDepthFunc_None = 1,
};

enum EPrimitiveType
{
	nPrimitiveType_TriangleList = 0,
	nPrimitiveType_TriangleStrip,
	nPrimitiveType_LineStrip,
    nPrimitiveType_LineList,
    nPrimitiveType_PointList,
    nPrimitiveType_Count,
    nPrimitiveType_None = -1
};


/** 
\ingroup GraphicsGeometry
Element semantic used to build a vertexStream
*/
enum EVertexComponent
{
	nVertexComponent_Position = 0,
	nVertexComponent_TexCoord0,
	nVertexComponent_TexCoord1,
	nVertexComponent_TexCoord2,
	nVertexComponent_TexCoord3,
	nVertexComponent_TexCoord4,
	nVertexComponent_TexCoord5,
	nVertexComponent_TexCoord6,
	nVertexComponent_TexCoord7,
	nVertexComponent_Color0,
	nVertexComponent_Color1,
	nVertexComponent_Normal,
	nVertexComponent_Tangent,
	nVertexComponent_BiNormal,
	nVertexComponent_Count,
	nVertexComponent_None = -1
};

/** 
\ingroup GraphicsGeometry
Element type used to build a vertex stream
*/
enum EVertexComponentType
{
	nVertexComponentType_Float2 = 0,
	nVertexComponentType_Float3,
	nVertexComponentType_Float4,
	nVertexComponentType_Count,
	nVertexComponentType_None = -1
};

#endif

