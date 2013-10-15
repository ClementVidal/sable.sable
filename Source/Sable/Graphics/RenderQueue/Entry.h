#ifndef _GRAPHICS_RENDER_ENTRY_
#define _GRAPHICS_RENDER_ENTRY_

#include <Sable\Core\String\String.h>
#include <Sable\Core\ManagedObject\ManagedObject.h>
#include <Sable\Core\Math\Range.h>

#include <Sable\Graphics\Light\Light.h>
#include <Sable\Graphics\Node\Header.h>
#include <Sable\Graphics\Geometry\Header.h>
#include <Sable\Graphics\Node\ShaderConnector\TransformMatrix.h>

namespace Sable
{

class CGeometryMesh;
class CCamera;
class CShader;
class CShaderConnector;

/** 
Render Queue Entry .
*/
class CRenderQueueEntry : public CManagedObject
{

    DEFINE_MANAGED_CLASS( CRenderQueueEntry );

public:

    /** @name Type*/
    //@{
	typedef CMethodPointer<CManagedObject, CRenderQueueEntry& > CallBack;
    //@}

    /** @name Constructor/Destructor*/
    //@{
    CRenderQueueEntry( );
    CRenderQueueEntry( const CRenderQueueEntry& other );
    ~CRenderQueueEntry();
    //@}

    /** @name Operator*/
    //@{
    CRenderQueueEntry& operator=( const CRenderQueueEntry& other );
    Bool    operator<( const CRenderQueueEntry& other);
    //@}

    /** @name Accessors*/
    //@{
    Void                        SetPrimitiveType( EPrimitiveType type ) { m_PrimitiveType = type; }

    Void                        SetVertexBuffer( CGeometryVertexBuffer* buffer ) { m_VertexBuffer = buffer; }
	Void                        SetInstanceBuffer( CGeometryInstanceBuffer* buffer ) { m_InstanceBuffer = buffer; }
    Void                        SetVertexLayout( CGeometryVertexLayout* layout ) { m_VertexLayout = layout; }
    Void                        SetIndexBuffer( CGeometryIndexBuffer* buffer ) { m_IndexBuffer = buffer; }
    Void						SetShader( CShader* shader ) { m_Shader = shader; }
	Void						SetStatesBlend( CStatesBlend* state ) { m_StatesBlend = state; }
	Void						SetStatesDepthStencil( CStatesDepthStencil* state ) { m_StatesDepthStencil = state; }
	Void						SetStatesRasterizer( CStatesRasterizer* state ) { m_StatesRasterizer = state; }
	Void						SetPriority( UInt32 p ) { m_Priority = p; }

	Void						AddShaderConnector( CShaderConnector& connector );
    //@}

    /** @name Manipulator*/
    //@{
    Void Render( CRenderer& renderer );
    Void Clear();
	Bool IsValid() const;
    Bool Activate( CRenderer& renderer );
    //@}

    /** @name Attribute*/
    //@{
	CShaderConnectorTransformMatrix		ShaderConnectorTransformMatrix;
    //@}

private:

    // Type

    // Method
	Bool	IsOpaque() const;

    // Attribute
    EPrimitiveType              m_PrimitiveType;
    CGeometryVertexBuffer*      m_VertexBuffer;
    CGeometryIndexBuffer*       m_IndexBuffer;
	CShader*					m_Shader;
    CGeometryVertexLayout*      m_VertexLayout;
	CGeometryInstanceBuffer*	m_InstanceBuffer;
	CStatesBlend*				m_StatesBlend;
	CStatesRasterizer*			m_StatesRasterizer;
	CStatesDepthStencil*		m_StatesDepthStencil;

	CShaderConnector*			m_ConnectorTable[8];

	UInt32						m_Priority;

};


}
#endif
