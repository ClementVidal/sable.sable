#ifndef _SABLE_GRAPHICS_CAMERA_SHADERCONNECTOR_CAMERA_
#define _SABLE_GRAPHICS_CAMERA_SHADERCONNECTOR_CAMERA_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Graphics/Shader/SystemConnector.h>

namespace Sable
{

/** 
\ingroup GraphicsShader
Shader Connector used to retrieve camera informations


<B>Supported Parameters:</B>
- float3 Camera_Position : 
Position of the camera

-float4 Camera_Direction : 
Direction of the camera
*/
class CShaderConnectorCamera : public CShaderSystemConnector
{

	DEFINE_MANAGED_CLASS( CShaderConnectorCamera );

public:

	/** @name DataType*/
	//@{
	enum ESemantic
	{
		nSemantic_Position = 0,
		nSemantic_Direction,
		nSemantic_ViewProjectionMatrix,
		nSemantic_ViewMatrix,
		nSemantic_ViewITMatrix,
		nSemantic_Count
	};
	//@}

	/** @name Constructor/Destructor*/
	//@{
	CShaderConnectorCamera( CCamera& camera );
 	CShaderConnectorCamera( );
	~CShaderConnectorCamera();
    //@}

    /** @name Operator*/
    //@{
    //@}

    /** @name Accessors*/
    //@{
	Bool	GetItSupportParameter( const CShaderParameter& param )const;
	Void	EvaluateParameterValue( const CShaderParameter& param, CVector3f& data ) const;
	Void	EvaluateParameterValue( const CShaderParameter& param, CMatrix4x4f& data ) const;
	//@}

	/** @name Mutator*/
	//@{
	//@}

	/** @name Manipulator*/
	//@{
	//@}

private: 

    //Methods

    //Attributes
	CCamera*	m_Camera;
	HashValue	m_Hashes[nSemantic_Count];
};

}
#endif
