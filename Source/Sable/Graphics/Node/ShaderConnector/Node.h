#ifndef _GRAPHICS_SCENEGRAPH_SHADERCONNECTOR_SHADERCONNECTORGRAPHNODE_
#define _GRAPHICS_SCENEGRAPH_SHADERCONNECTOR_SHADERCONNECTORGRAPHNODE_

#include <Sable\Core\Collection\Array.h>
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
class CShaderConnectorGraphNode : public CShaderSystemConnector
{

	DEFINE_MANAGED_CLASS( CShaderConnectorGraphNode );

public:

	/** @name DataTypes*/
	//@{
	enum ESemantic
	{
		nSemantic_WorldMatrix = 0,
		nSemantic_WorldIMatrix,
		nSemantic_WorldITMatrix,
		nSemantic_ItUseInstancing,
		nSemantic_Count
	};
	//@}

	/** @name Constructor/Destructor*/
	//@{
	CShaderConnectorGraphNode( CNodeRender& node );
	~CShaderConnectorGraphNode();
	//@}

	/** @name Operator*/
	//@{
	//@}

	/** @name Accessors*/
	//@{
	virtual Bool GetItSupportParameter( const CShaderParameter& param )const;
	virtual Void EvaluateParameterValue( const CShaderParameter& param, CMatrix4x4f& data ) const;
	virtual Void EvaluateParameterValue( const CShaderParameter& param, Bool& data ) const;
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
	CNodeRender* m_Node;
	HashValue	m_Hashes[nSemantic_Count];

	static const char* ParametersName[];
};

}
#endif
