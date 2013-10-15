#ifndef _SABLE_SCENE_SCENE_WORLD_
#define _SABLE_SCENE_SCENE_WORLD_

#include <Sable\Core\ManagedObject\Ref.h>
#include <Sable\Graphics\Node\Spatial.h>
#include <Sable\Gui\Widget\Widget.h>

namespace Sable
{

class CSceneView;
class CCamera;
class CNodeSpatial;
class CPersistentArchive;
class CRenderer;

/**  
\ingroup SceneWorld
Representation of World.
Contain references to it's Skybox and RootNode, also contain a back reference to it's attached Scene.
*/
class CSceneWorld : public CManagedObject
{

DEFINE_MANAGED_CLASS( CSceneWorld );

public:

	/** @name Constructor/Destructor*/
	//@{
	CSceneWorld( );
	virtual ~CSceneWorld();
	//@}

    /** @name Accessors*/
    //@{
	CNodeSpatial&               GetRootNode();
	const CNodeSpatial&         GetRootNode() const;
	CWidget&					GetGuiRootNode();
	const CWidget&				GetGuiRootNode() const;
    //@}

    /** @name Manipulator*/
    //@{
    virtual Void Update( );   
    virtual Void Clear();
    Bool Serialize( CPersistentArchive& ar );
    //@}

private:

	// Method
	
	//Attribute
	CNodeSpatial		m_RootNode;
	CWidget				m_GuiRootNode;

};

}

#endif
