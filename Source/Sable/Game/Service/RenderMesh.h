#ifndef _SABLE_GAME_SERVICE_RENDERMESH_
#define _SABLE_GAME_SERVICE_RENDERMESH_

#include <Sable/Game/Service/Service.h>

namespace Sable
{

class CNodeRender;

/**  
\ingroup Game
GameObject
*/
class CServiceRenderMesh : public CGameService
{

	DEFINE_MANAGED_CLASS( CServiceRenderMesh );

public:

	/** @name Constructor/destructor */
	//@{
	CServiceRenderMesh( );
	CServiceRenderMesh( CGameObject& obj );
	~CServiceRenderMesh();
	//@}

	/** @name Accessors*/
	//@{
	CNodeRender&	GetNode() const;
	//@}

	/** @name Manipulator*/
	//@{
	//@}

private:

	// Types

	// Methods

    // Attributes
	CRef<CNodeRender>		m_RenderNode;
};

}

#endif
