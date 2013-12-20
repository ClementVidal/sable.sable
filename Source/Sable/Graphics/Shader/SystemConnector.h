#ifndef _SABLE_GRAPHICS_SHADER_SYSTEMSHADERCONNECTOR_
#define _SABLE_GRAPHICS_SHADER_SYSTEMSHADERCONNECTOR_

#include <Sable/Graphics/Shader/Connector.h>

namespace Sable
{

class CRenderer;
class CMatrix4x4f;
class CVector3f;
class CVector4f;
class CShaderParameter;
class CTexture;
class CRenderTargetTexture;


/** 
\ingroup GraphicsShader
*/
class CShaderSystemConnector : public CShaderConnector
{

	DEFINE_MANAGED_CLASS( CShaderSystemConnector );

public:

    /** @name Constructor/Destructor*/
    //@{
    CShaderSystemConnector( );
    ~CShaderSystemConnector();
    //@}

    /** @name Operator*/
    //@{
    //@}

    /** @name Accessors*/
    //@{
	virtual Bool	GetItSupportParameter( const CShaderParameter& param )const ;
	//@}

	/** @name Manipulator*/
	//@{
	Void FlushParametersValues( CShader& program ) const;
	//@}

protected:

	// Methods
	Bool CheckHashesUniqueness( HashValue* hashes, UInt32 count )const;

	virtual Void	EvaluateParameterValue( const CShaderParameter& param, CArray<Float32>& data ) const;
	virtual Void	EvaluateParameterValue( const CShaderParameter& param, Float32& data ) const;
	virtual Void	EvaluateParameterValue( const CShaderParameter& param, Int32& data ) const;
	virtual Void	EvaluateParameterValue( const CShaderParameter& param, Bool& data ) const;
	virtual Void	EvaluateParameterValue( const CShaderParameter& param, CMatrix4x4f& data ) const;
	virtual Void	EvaluateParameterValue( const CShaderParameter& param, CRef<CTexture>& data ) const;
	virtual Void	EvaluateParameterValue( const CShaderParameter& param, CRef<CRenderTargetTexture>& data ) const;
	virtual Void	EvaluateParameterValue( const CShaderParameter& param, CVector2f& data ) const;
	virtual Void	EvaluateParameterValue( const CShaderParameter& param, CArray<CVector2f>& data ) const;
	virtual Void	EvaluateParameterValue( const CShaderParameter& param, CVector3f& data ) const;
	virtual Void	EvaluateParameterValue( const CShaderParameter& param, CArray<CVector3f>& data ) const;
	virtual Void	EvaluateParameterValue( const CShaderParameter& param, CVector4f& data ) const;
	virtual Void	EvaluateParameterValue( const CShaderParameter& param, CArray<CVector4f>& data ) const;

private: 

    //Methods
	Void FlushParametersValues( CShaderParameter& parameter ) const;

    //Attributes

};

}
#endif
