#include <Sable\Physic\Node\RenderPhysic.h>

#include <Sable\Physic\Actor\Header.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1( Sable, CNodeRenderPhysic, CNodeRender ) ;

CNodeRenderPhysic::CNodeRenderPhysic( ):
	CNodeRender()
{
	SetAttribute( nAttribute_InheritAll, FALSE );
	SetAttribute( nAttribute_InheritPosition, FALSE );
	SetAttribute( nAttribute_InheritRotatationAndTranslation, FALSE );

	m_Scale = CVector3f( 1, 1, 1 ) ;
}

CNodeRenderPhysic::CNodeRenderPhysic( CNode&  parent ):
	CNodeRender( parent )
{
	SetAttribute( nAttribute_InheritAll, FALSE );
	SetAttribute( nAttribute_InheritPosition, FALSE );
	SetAttribute( nAttribute_InheritRotatationAndTranslation, FALSE );
	
	m_Scale = CVector3f( 1.0f, 1.0f, 1.0f );
}

CNodeRenderPhysic::~CNodeRenderPhysic()
{
}

Void CNodeRenderPhysic::SetScale( const CVector3f& scale )
{
	m_Scale = scale;
}

const CVector3f&	CNodeRenderPhysic::GetScale( ) const
{
	return m_Scale;
}

Void CNodeRenderPhysic::SetAttribute( EAttribute attrib, Bool onOff )
{
	if( attrib == nAttribute_InheritAll || attrib == nAttribute_InheritPosition || attrib == nAttribute_InheritRotatationAndTranslation )
	{
		CNodeRender::SetAttribute( attrib, FALSE );
	}

	CNodeRender::SetAttribute( attrib, onOff );
}

Bool CNodeRenderPhysic::Update()
{	
	//SetState( const EState state );

	if( m_PhysicActor )
	{
		CMatrix4x4f m;
		m_PhysicActor->GetWorldMatrix( m );
		SetLocalMatrix( m );
	}

	return CNodeRender::Update();
}

Void CNodeRenderPhysic::SetActor( CPhysicActor* actor )
{
	m_PhysicActor = actor;
}

Void CNodeRenderPhysic::SetLocalMatrix(const CMatrix4x4f& matrix)
{
	if( m_PhysicActor )
	{
		m_PhysicActor->SetWorldMatrix( matrix );
	}
	CMatrix4x4f m;
	m.SetFromScale(m_Scale);
	m = m * matrix;
	CNodeRender::SetLocalMatrix( m );
}

CPhysicActor*	CNodeRenderPhysic::GetActor() const
{
	return m_PhysicActor;
}
