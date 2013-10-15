#ifndef _SABLE_GRAPHICS_COMMON_SCREENQUAD_
#define _SABLE_GRAPHICS_COMMON_SCREENQUAD_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\ManagedObject\ManagedObject.h>
#include <Sable\Graphics\Geometry\IndexBuffer.h>
#include <Sable\Graphics\Geometry\VertexBuffer.h>
#include <Sable\Graphics\Geometry\VertexLayout.h>
#include <Sable\Core\Math\Vector3f.h>
#include <Sable\Core\Math\Vector2f.h>
#include <Sable\Core\Math\Vector4f.h>
#include <Sable\Core\Common\Color.h>

namespace Sable
{ 

class CShader;
class CRenderer;

/** 
Screen aligned quad
*/
class CScreenQuad : public CManagedObject
{

public:

    /** @name Constructor/Destructor*/
    //@{
    CScreenQuad();
    virtual ~CScreenQuad();
    //@}

    /** @name Accessors*/
    //@{
    Void SetColor( const CColor& col1, const CColor& col2, const CColor& col3, const CColor& col4 );
	Void SetColor( const CColor& col );
	//@}

    /** @name Manipulator*/
    //@{
    Void	Render( CRenderer& renderer, const CVector2f& pos, const CVector2f& size, CShader& shader );
    Void	Initialize();
	Void	Initialize( const CColor& col );
	Void	Initialize( const CColor& col1, const CColor& col2, const CColor& col3, const CColor& col4 );
	Void    UnInitialize();
	//@}

private:

    // Data types
    struct SVertex
    {
        CVector2f Position;
        CVector2f TexCoord0;
		CColor Color;
    };

    // Attributes

    // Method
    CGeometryVertexBuffer		m_VertexBuffer;
    CGeometryIndexBuffer		m_IndexBuffer;
	CGeometryVertexLayout		m_VertexLayout;
};

}
#endif
