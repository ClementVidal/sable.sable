#ifndef _USERINTERFACE_CURSOR_CURSOR_
#define _USERINTERFACE_CURSOR_CURSOR_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\ManagedObject\ManagedObject.h>
#include <Sable\Graphics\Geometry\Header.h>
#include <Sable\Graphics\Texture\Header.h>
#include <Sable\Graphics\Shader\Header.h>
#include <Sable\Graphics\States\Header.h>

namespace Sable
{

/**  
\ingroup UserInterface
Cursor class.
*/
class CCursor : public CManagedObject
{

	DEFINE_MANAGED_CLASS( CCursor );

public:

	/** @name Constructor/destructor */
	//@{
	CCursor();
	~CCursor();
	//@}

	/** @name Operator*/
	//@{
	//@}

	/** @name Accessors*/
	//@{
	Void SetPosition( const CVector2f& pos );
	//@}

	/** @name Manipulator*/
    //@{
	Void Render(CRenderer& renderer);
	//@}

private:

	// Types
	struct SVertex
	{
		CVector3f	Position;
		CVector2f	TexCoord0;
	};

    // Methods
	Void InitVertexBuffer();
	Void Activate(CRenderer& renderer);

    // Attributes
	CTexture2D					m_Texture;
	CShader			            m_Shader;
	CGeometryVertexBuffer		m_VertexBuffer;
	CGeometryVertexLayout		m_VertexLayout;
	CVector2f					m_Position;
    CStatesBlend                m_BlendStates;
    CStatesDepthStencil         m_DepthStates;
	CStatesSampler				m_SamplerStates;
};

}

#endif
