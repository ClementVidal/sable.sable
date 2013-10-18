#ifndef _SABLE_GRAPHICS_PARTICLE_SYSTEM_
#define _SABLE_GRAPHICS_PARTICLE_SYSTEM_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/Math/Random.h>
#include <Sable/Graphics/Node/Render.h>
#include <Sable/Graphics/Geometry/Header.h>
#include <Sable/Graphics/States/Header.h>

namespace Sable
{

class CMaterial;
class CParticleGroup;

/** 
\ingroup GraphicsParticle
Particle System
*/
class CParticleSystem : public CNodeRender
{

	DEFINE_MANAGED_CLASS( CParticleSystem );

public:

	/** @name Constructor/Destructor*/
	//@{
	CParticleSystem( );
	CParticleSystem( CNodeSpatial& parent, CParticleGroup& sim, CMaterial& material );
	~CParticleSystem();
	//@}

	/** @name Operator*/
	//@{
	//@}

	/** @name Accessors*/
	//@{
	CStatesBlend&		GetBlendStates();
	CParticleGroup&		GetGroup();
	Void				SetGroup(CParticleGroup& simulator);
	Void				SetMaterial( CMaterial* material );
	CMaterial&			GetParticleMaterial( ) const;
	//@}

	/** @name Manipulator*/
	//@{
	Bool			Serialize( CPersistentArchive& ar );
	Void			Initialize( CNodeSpatial& parent, CParticleGroup& sim, CMaterial& material );
	Void			Initialize( );
	Bool			Update( );
	//@}

private:

	// Data type
	struct SVertex
	{
		CVector3f Position;
		CVector2f TexCoord0;
		CColor Color;
	};

	// Methods
	Void			InitializeIndexData( CArrayUInt32& data, UInt32 particleCapacity  );
	Void			InitializeStreamData( CArray<SVertex>& data, UInt32 particleCapacity  );
	Void			RebuildBuffer( const CCamera& cam );

	// Attributes
	CRef<CMaterial>				m_Material;
	CRef<CParticleGroup>		m_Group;
	CRandom						m_Random;
	CRef<CStatesBlend>			m_BlendStates;
	CRef<CStatesDepthStencil>	m_DepthStencilStates;

	CGeometryModel				m_Model;
	CGeometryMesh				m_Mesh;
	CGeometryVertexBuffer		m_VertexBuffer;
	CGeometryIndexBuffer		m_IndexBuffer;
	CGeometryVertexLayout		m_VertexLayout;

};

Inline
CParticleGroup& CParticleSystem::GetGroup()
{
	return *m_Group;
}

}

#endif


