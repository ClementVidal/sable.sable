#ifndef _SABLE_SCENE_VIEW_VIEW_
#define _SABLE_SCENE_VIEW_VIEW_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\Memory\Header.h>
#include <Sable\Core\ManagedObject\Ref.h>
#include <Sable\Graphics\Shader\Header.h>

namespace Sable
{

class CApplicationWindow;
class CSceneWorld;
class CRenderer;
class CCamera;
class CScreenQuad;

/**  
\ingroup SceneView
Hight level container for a scene.
Contain references to the renderer used to render this scene, to the world actually renderer, 
and to the camera used to visualize the scene.
*/
class CSceneView : public CManagedObject
{

    DEFINE_MANAGED_CLASS( CSceneView );

public:

	/** @name Constructor/Destructor*/
	//@{
	CSceneView( );
	~CSceneView();
	//@}

    /** @name Accessors*/
    //@{
	CCamera*	        GetCamera() const;
	Void		        SetCamera( CCamera* camera );
	CSceneWorld*		GetWorld() const;
	virtual Void	    SetWorld( CSceneWorld* world );
    //@}

	/** @name Manipulator*/
	//@{
    virtual Bool    Update();
	virtual Void    Initialize( );
	//@}

private:

	// Method
	
	//Attribute
    CRef<CSceneWorld>		m_World;
    CRef<CCamera>			m_Camera;
	CRef<CScreenQuad>		m_Background;
	CRef<CShader>			m_BackgroundShader;
};


}

#endif
