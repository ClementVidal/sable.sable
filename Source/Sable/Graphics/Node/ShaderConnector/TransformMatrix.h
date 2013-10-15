#ifndef _GRAPHICS_SCENEGRAPH_SHADERCONNECTOR_TRANSFORMMATRIX_
#define _GRAPHICS_SCENEGRAPH_SHADERCONNECTOR_TRANSFORMMATRIX_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\String\String.h>
#include <Sable\Graphics\Shader\SystemConnector.h>

namespace Sable
{

class CNodeRender;

/** 
\ingroup GraphicsShader
Store data to be transfered to the Shader
*/
class CShaderConnectorTransformMatrix : public CShaderSystemConnector
{

	DEFINE_MANAGED_CLASS( CShaderConnectorTransformMatrix );

public:

	/** @name DataTypes*/
	//@{
	enum ESemantic
	{
		nSemantic_WorldViewProjectionMatrix = 0,
		nSemantic_WorldViewITMatrix,
		nSemantic_Count
	};
	//@}

	/** @name Constructor/Destructor*/
	//@{
	CShaderConnectorTransformMatrix( CNodeSpatial& node, CCamera& camera );
	CShaderConnectorTransformMatrix( );
	~CShaderConnectorTransformMatrix();
	//@}

	/** @name Operator*/
	//@{
	//@}

	/** @name Accessors*/
	//@{
	Void Set( CNodeSpatial& node, CCamera& camera );
	virtual Bool GetItSupportParameter( const CShaderParameter& param )const;
	virtual Void EvaluateParameterValue( const CShaderParameter& param, CMatrix4x4f& data ) const;
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
	CNodeSpatial*	m_Node;
	CCamera*		m_Camera;

	HashValue	m_Hashes[nSemantic_Count];

	static const char* ParametersName[];
};

}
#endif
