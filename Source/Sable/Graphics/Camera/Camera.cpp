#include <Sable\Graphics\Camera\Camera.h>
#include <Sable\Graphics\Common\Manager.h>
#include <Sable\Core\Persistent\Archive.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1( Sable, CCamera, CNodeSpatial );

CCamera::CCamera():
	CNodeSpatial(),
	m_ShaderConnector( *this )
{
	m_WorldUp = CVector3f::Axis[ nAxis_Y ];
	m_ViewMatrix.SetFromIdentity();
	m_ProjectionMatrix.SetFromIdentity();
	m_ViewProjectionMatrix.SetFromIdentity();
	m_ViewMatrix.SetFromIdentity();
	m_InverseViewMatrix.SetFromIdentity();
}

CCamera::CCamera(CNode&  parent ):
	CNodeSpatial( parent ),
	m_ShaderConnector( *this )
{
}

CCamera& CCamera::operator=( const CCamera& other )
{
	DebugError( "Not Implemented" );
    return *this;
}

CCamera::~CCamera()
{
}

CShaderConnectorCamera&	CCamera::GetShaderConnector()
{
	return m_ShaderConnector;
}

Bool CCamera::Update( )
{
	CNodeSpatial::Update();

	//Mettre a jour cette matrice seulement si la matrice world a été modifié
	if(GetIsWorldMatrixNew())
	{
		EvaluateCameraMatrix();
	}

	return TRUE;
}

Float32 CCamera::ComputeFitDistance( const CSphere& sphere )
{
	return 0.0f;
}

Void CCamera::EvaluateCameraMatrix()
{
	//La matrice camera est l'inverse de la matrice mondes
	m_ViewMatrix = GetInverseWorldMatrix();

	//Sauve l'inverse de la matrice View
	m_InverseViewMatrix = GetWorldMatrix();

	//La matrice de ViewProj est l'inverse de notre matrice monde, 
	//multiplié par la matrice de projection
	m_ViewProjectionMatrix = m_ViewMatrix * m_ProjectionMatrix;

	m_Frustum.ExtractFrom( m_ViewProjectionMatrix );
}

const CVector3f  CCamera::GetCameraDirection() const
{
	return GetWorldMatrix().GetZComponent();
}

/**
Compute and return a ray starting from the current camera position, and pointing toward 
a point specified on a virtual view plane .<br>
This point is specified using the following coordinate:<br>
X: [-1 <- | ->  1]
Y: [ 1 <- | -> -1]
*/
CRay CCamera::GetRayFrom2DPos( const CVector2f& viewPlanePoint ) const
{
	DebugError("Not implemented");
    return CRay();
}

CVector3f CCamera::Get3DPointFrom2DPos( const CVector2f& viewPlanePoint, Float32 viewPlaneDist) const
{
    CVector3f v;
	DebugError("Not implemented");
    return v;
}

CVector2f CCamera::GetFrustumSizeAtDist( Float32 dist ) const
{
    CVector2f v;
    DebugError("Not implemented");
    return v;
}