#ifndef _SABLE_GRAPHICS_SHADER_CONNECTOR_VIEWPORT_
#define _SABLE_GRAPHICS_SHADER_CONNECTOR_VIEWPORT_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Graphics/Shader/SystemConnector.h>

namespace Sable
{

class CViewport;

/** 
\ingroup GraphicsShader
Shader Connector used to retrieve time information.
\n\n
<B>Supported Parameters:</B>
\n	float System_Time : Return the current system time in second.
*/
class CShaderConnectorViewport : public CShaderSystemConnector
{

	DEFINE_MANAGED_CLASS( CShaderConnectorViewport );

public:

	/** @name DataTypes*/
	//@{
	enum ESemantic
	{
		nSemantic_ViewportInfo = 0,
		nSemantic_Count
	};
	//@}

	/** @name Constructor/Destructor*/
	//@{
	CShaderConnectorViewport( CViewport& vp );
	~CShaderConnectorViewport();
	//@}

	/** @name Operator*/
	//@{
	//@}

	/** @name Accessors*/
	//@{
	Bool	GetItSupportParameter( const CShaderParameter& param )const;
	Void	EvaluateParameterValue( const CShaderParameter& param, CVector4f& data ) const;
	//@}

	/** @name Manipulator*/
	//@{
	//@}

private: 

	//Methods
	
	//Attributes
	HashValue	m_Hashes[nSemantic_Count];
	CViewport*	m_Viewport;

	static String ParametersName[];
};

}
#endif
