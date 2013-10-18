#include <Sable/Graphics/Node/Spatial.h>

#include <Sable/Core/Persistent/Archive.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1_ALLOC( Sable, CNodeSpatial, CNode ) ;

CNodeSpatial::CNodeSpatial():
CNode()
{
	SetAttribute( nAttribute_InheritAll, TRUE );
	SetState( nState_NewLocalMatrix, TRUE );

	m_InverseWorldMatrix.SetFromIdentity();
	m_LocalMatrix.SetFromIdentity();
	m_WorldMatrix.SetFromIdentity();
}

CNodeSpatial::CNodeSpatial( CNode& parent ):
CNode( parent )
{
	SetAttribute( nAttribute_InheritAll, TRUE );
	SetState( nState_NewLocalMatrix, TRUE );

	m_InverseWorldMatrix.SetFromIdentity();
	m_LocalMatrix.SetFromIdentity();
	m_WorldMatrix.SetFromIdentity();
}

CNodeSpatial::~CNodeSpatial()
{			
}

Bool CNodeSpatial::IsVisible( const CCamera& camera ) const
{
	return TRUE;
}

Void CNodeSpatial::EvaluateWorldMatrix( )
{
	Bool parentMoved	=	GetParent() && SafeCastRef( GetParent(), CNodeSpatial )->GetIsWorldMatrixNew();
	Bool weMoved		= GetState( nState_NewLocalMatrix );

	// update only if we or our parent have moved
	if ( weMoved || parentMoved )
	{
		if( GetParent() )
		{		
			if( GetAttribute( nAttribute_InheritAll ) )
			{
				m_WorldMatrix = ( CMatrix4x4f&) m_LocalMatrix * SafeCastRef( GetParent(), CNodeSpatial )->GetWorldMatrix() ;
			}
			else if( GetAttribute( nAttribute_InheritPosition ) )
			{
				const CMatrix4x4f& parentWorldMatrix = SafeCastRef( GetParent(), CNodeSpatial )->GetWorldMatrix();
				CMatrix4x4f parentMatrix;

				parentMatrix.SetFromTranslation( parentWorldMatrix.GetTranslationComponent() );

				m_WorldMatrix = m_LocalMatrix * parentMatrix;

			}
			else if( GetAttribute( nAttribute_InheritRotatationAndTranslation ) )
			{
				CMatrix4x4f s, p = SafeCastRef( GetParent(), CNodeSpatial )->GetWorldMatrix();
                CVector3f l;
                l.SetX( 1.0f/p.GetXComponent().GetLength() );
                l.SetY( 1.0f/p.GetYComponent().GetLength() );
                l.SetZ( 1.0f/p.GetZComponent().GetLength() );

                s.SetFromScale( l );
                p.SetFromMultiplication( s, p );
                m_WorldMatrix = m_LocalMatrix * p;
			}
			else
			{
				m_WorldMatrix = m_LocalMatrix;
			}
		
		}
		else
		{
			m_WorldMatrix = m_LocalMatrix;
		}

		// notify that world matrix has been updated	
		SetState( nState_NewWorldMatrix, TRUE );

		m_InverseWorldMatrix = m_WorldMatrix;
		m_InverseWorldMatrix.Invert();
	}
}

Bool CNodeSpatial::Update( )
{
	EvaluateWorldMatrix( );
	return CNode::Update( );
}

Void CNodeSpatial::PrepareForNextUpdate()
{
	SetState( nState_NewLocalMatrix, FALSE  );
	SetState( nState_NewWorldMatrix, FALSE );

	return CNode::PrepareForNextUpdate();
}

Void CNodeSpatial::SetLocalMatrix(const CMatrix4x4f& matrix)
{
	SetState( nState_NewLocalMatrix, TRUE );
	m_LocalMatrix = matrix;
}

Void CNodeSpatial::SetLocalTranslation( const CVector3f& t)
{
	SetState( nState_NewLocalMatrix, TRUE );
	m_LocalMatrix.SetTranslationComponent( t );
}

Void CNodeSpatial::SetParent( CNode* pParent)
{
	//on ajuste la matrice locale pour quelle soit relative a celle de son parent
	//Comme on aura au préalable appelé DetachFromParet(), m_LocalMatrix, sera egale a m_WorldMatrix
	//Donc en prenant l'inverse de la matrice Monde du pere et en la multipliant avec la matrice Locale 
	//(qui est donc egale a l'ancienne matrice monde)
	//on "soustrait" le repere monde de l'objet a celui de son pere, et on obtient donc le deplacement "local"
	//de ce meme objet !

	CNodeSpatial* spatialNodeParent = (CNodeSpatial*)pParent;

    if( spatialNodeParent )
    {
	    const CMatrix4x4f & InvertedParentMatrix = spatialNodeParent->GetInverseWorldMatrix();
	    m_LocalMatrix = m_LocalMatrix * InvertedParentMatrix;
	    SetState( nState_NewLocalMatrix, TRUE );
    }

	CNode::SetParent( pParent );
}

Bool CNodeSpatial::Serialize( CPersistentArchive& ar )
{
	Int16 version = 0;

	if( ar.BeginScope( WT("NodeSpatial"), version ) == version )
	{
		ar.Serialize( m_LocalMatrix, WT("LocalTransform") );
		ar.Serialize( m_WorldMatrix, WT("WorldTransform") );
		ar.Serialize( m_InverseWorldMatrix, WT("InverseWorldTransform") );

		ar.EndScope();
	}
	else
	{
		return FALSE;
	}

	return CNode::Serialize( ar );
}