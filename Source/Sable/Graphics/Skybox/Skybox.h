#ifndef _SABLE_SCENE_WORLD_SKYBOX_
#define _SABLE_SCENE_WORLD_SKYBOX_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Graphics/Shader/Header.h>
#include <Sable/Graphics/Camera/Camera.h>
#include <Sable/Core/ManagedObject/Ref.h>
#include <Sable/Graphics/States/Header.h>

namespace Sable
{

class CSceneWorld;
class CRenderer;

/**  
\ingroup SceneWorld
SkyBox
*/
class CSkybox : public CManagedObject
{

	DEFINE_MANAGED_CLASS( CSkybox );

public:

	/** @name Constructor/Destructor*/
	//@{
	CSkybox();
	CSkybox( CSceneWorld& world );
	~CSkybox();
	//@}

	/** @name Accessors*/
	//@{
	Void SetTexture( CTextureCube& texture );
	CTextureCube& GetTexture() const;
	//@}

	/** @name Manipulator*/
	//@{
	Void Initialize( );
	Void UnInitialize( );
	Void Render( CRenderer& renderer );
	//@}


private:

	// Data types
	struct SVertex
	{
		CVector3f Position;
	};

	// Method
	Void BuildMesh();

	//Attribute
	CRef<CTextureCube>      m_DiffuseTexture;
    CGeometryMesh			m_Mesh;
	CShader					m_Shader;
	CGeometryVertexBuffer	m_VertexBuffer;
	CGeometryIndexBuffer	m_IndexBuffer;
	CGeometryVertexLayout	m_VertexLayout;
	CStatesSampler			m_SamplerStates;

	CSceneWorld*				    m_World;

};

}

#endif
