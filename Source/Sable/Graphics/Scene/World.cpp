#include <Sable/Graphics/Scene/World.h>

#include <Sable/Graphics/Skybox/Skybox.h>
#include <Sable/Graphics/LensFlare/RenderPass.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1_ALLOC( Sable, CSceneWorld, CManagedObject )

CSceneWorld::CSceneWorld(  )
{
}

CSceneWorld::~CSceneWorld()
{
    Clear();
}

/**
Cleanup method used to free any resources, data attached to the world
*/
Void CSceneWorld::Clear()
{
	m_RootNode.RemoveAllChilds();
	m_GuiRootNode.RemoveAllChilds();
}

CNodeSpatial& CSceneWorld::GetRootNode() 
{
	return m_RootNode;
}

const CNodeSpatial& CSceneWorld::GetRootNode() const 
{
	return m_RootNode;
}

CWidget& CSceneWorld::GetGuiRootNode()
{
	return m_GuiRootNode;
}

const CWidget& CSceneWorld::GetGuiRootNode() const
{
	return m_GuiRootNode;
}

Void CSceneWorld::Update( )
{
	m_RootNode.RecursiveUpdate( );
	m_GuiRootNode.RecursiveUpdate();
}

Bool CSceneWorld::Serialize( CPersistentArchive& ar )
{
    Int16 version = 0;

    if( ar.BeginScope( WT("World"), version ) == version )
    {
		ar.Serialize( m_RootNode, WT("Root") );
		ar.Serialize( m_GuiRootNode, WT("GuiRootNode") );
        ar.EndScope();
    }
    else
    {
        return FALSE;
    }

    return TRUE;
}
