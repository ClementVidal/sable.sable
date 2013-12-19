#ifndef _SABLE_GRAPHICS_SHADER_SHADERCONNECTOR_
#define _SABLE_GRAPHICS_SHADER_SHADERCONNECTOR_

#include <Sable/Core/Collection/Array.h>
#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/String/String.h>
#include <Sable/Core/ManagedObject/ManagedObject.h>
#include <Sable/Graphics/Shader/Shader.h>
#include <Sable/Core/ManagedObject/Ref.h>


namespace Sable
{

class CRenderer;
class CMatrix4x4f;
class CVector3f;
class CVector4f;
class CShaderParameter;
class CTexture;
class CRenderTargetTexture;
    class CShader;

/** 
\ingroup GraphicsShader
*/
class CShaderConnector : public CManagedObject
{

    DEFINE_MANAGED_CLASS( CShaderConnector );

public:

    /** @name Constructor/Destructor*/
    //@{
    typedef CList< CRef<CShaderConnector> > List;
    //@}

    /** @name Constructor/Destructor*/
    //@{
    CShaderConnector( );
    ~CShaderConnector();
    //@}

    /** @name Operator*/
    //@{
    //@}

    /** @name Accessors*/
    //@{
    //@}
    
    /** @name Manipulator*/
    //@{
    virtual Void FlushParametersValues( CShader& program ) const = 0;
    //@}
    
private: 

    //Methods

    //Attributes

};

}
#endif
