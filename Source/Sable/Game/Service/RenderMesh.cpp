#include <Sable/Game/Service/RenderMesh.h>

#include <Sable/Game/Object/Object.h>
#include <Sable/Graphics/Node/Render.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1_ALLOC( Sable, CServiceRenderMesh, CGameService );

CServiceRenderMesh::CServiceRenderMesh(  ) :
	CGameService( )
{
	m_RenderNode = NEWOBJ( CNodeRender, () );
}

CServiceRenderMesh::CServiceRenderMesh( CGameObject& obj ) :
	CGameService( obj )
{
	m_RenderNode = NEWOBJ( CNodeRender, () );
}

CServiceRenderMesh::~CServiceRenderMesh()
{
}

CNodeRender& CServiceRenderMesh::GetNode() const
{
	return *m_RenderNode;
}
