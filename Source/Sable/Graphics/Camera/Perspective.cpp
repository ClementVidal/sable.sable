#include <Sable/Graphics/Camera/Perspective.h>

#include <Sable/Core/Geometry/Ray.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1( Sable, CCameraPerspective, CCamera );

CCameraPerspective::CCameraPerspective():
CCamera()
{
	SetProjectionMatrix( MathPi / 2.2f, 3/4.0f, 1.0f, 100.0f );
}

CCameraPerspective::CCameraPerspective( CNode& parent ):
CCamera( parent )
{
	SetProjectionMatrix( MathPi / 2.2f, 3/4.0f, 1.0f, 100.0f );
}

CCameraPerspective::~CCameraPerspective()
{
}

/**
Compute the optimal distance between a sphere and the camera in order for the camera to encompass the sphere
\return return the distance between the new camera position and the center of the sphere
*/
Float32 CCameraPerspective::ComputeFitDistance( const CSphere& sphere )
{
	// compute the distance between the camera and the center of the sphere using the camera FieldOfView
	Float32 dist = sphere.GetRadius() / MathTan( GetFieldOfView() / 2.0f );

	return dist;
}

Void CCameraPerspective::GetLocalBoundingBox( CAABox& box ) const
{
	box.SetEmpty();
	CVector3f camPos = GetLocalMatrix().GetTranslationComponent();

	box.Expand( CVector3f( 1.0f, 1.0f, 1.0f ) );
}

Void CCameraPerspective::SetProjectionMatrix( const Float32 FOV, const Float32 Aspect, const Float32 NearPlane, const Float32 FarPlane )
{
	//Parametrage des attributs
	m_FOV        = FOV;
	m_Aspect     = Aspect;
	m_NearPlane  = NearPlane;
	m_FarPlane   = FarPlane;

	//Configuration de la matrice de projection
	m_ProjectionMatrix.SetFromLHPerspProjectionValues( m_FOV, m_Aspect, m_NearPlane,m_FarPlane);

	EvaluateCameraMatrix();
}

/**
Compute and return a ray starting from the current camera position, and pointing toward 
a point specified on a virtual view plane .<br>
This point is specified using the following coordinate:<br>
X: [0 <- | ->  1]
Y: [0 <- | ->  1]
*/
CRay CCameraPerspective::GetRayFrom2DPos( const CVector2f& viewPlanePoint ) const
{
    CRay ray;
	Float32 viewPlaneDist = 1.0f;
	Float32 oppositeSide;
	CVector2f transformedPoint;

	// Transform point from [0 +1] to [-1 +1]
	transformedPoint.SetX( (viewPlanePoint.GetX() * 2.0f) - 1.0f );
	transformedPoint.SetY( ( ( 1.0f - viewPlanePoint.GetY() ) * 2.0f) - 1.0f );

    // Calcul de la longeur du coté opposé évalue a la distance viewPlaneDist
	oppositeSide = MathTan(m_FOV/2.0f) * viewPlaneDist;

	ray.Direction.SetX( transformedPoint.GetX() * oppositeSide / m_Aspect );
	ray.Direction.SetY( transformedPoint.GetY() * oppositeSide );
	ray.Direction.SetZ( viewPlaneDist );
	ray.Direction.Normalize();

	ray.Direction.Transform(GetWorldMatrix());
	ray.Origin = GetWorldPosition();

    return ray;
}

/**
Compute and return a 3d point, based on a 2d position projected on the view plane at 
a distance specified byviewPlaneDist .<br>
This 2d position is specified using the following coordinate:<br>
X: [0 <- | ->  1]
Y: [0 <- | ->  1]
*/
CVector3f CCameraPerspective::Get3DPointFrom2DPos( const CVector2f& viewPlanePoint, const Float32 viewPlaneDist ) const
{
    CVector3f point;
	Float32 oppositeSide;
	CVector2f transformedPoint;

	// Transform point from [0 +1] to [-1 +1]
	transformedPoint.SetX( (viewPlanePoint.GetX() * 2.0f) - 1.0f );
	transformedPoint.SetY( (viewPlanePoint.GetY() * 2.0f) - 1.0f );

	oppositeSide = MathTan(m_FOV/2.0f) * viewPlaneDist;

	point.SetX( transformedPoint.GetX() * oppositeSide / m_Aspect );
	// Y must be negated because the range [-1 0] in screen space correspond to the positive half Y value in view space
	// and [0 1] in the screen space correspond to the negative half Y value in view space
	point.SetY( - transformedPoint.GetY() * oppositeSide );
	point.SetZ( viewPlaneDist );

	point.TransformPosition(GetWorldMatrix());

    return point;

}

/**
Compute and return the width and height of the camera frustum at a specified distance from the camera position.
*/
CVector2f CCameraPerspective::GetFrustumSizeAtDist( Float32 dist ) const
{
	CVector2f size;
    
    size.SetY( MathTan(m_FOV/2.0f) * dist * 2.0f );
    size.SetX( MathTan(m_FOV/2.0f) * dist / m_Aspect * 2.0f );

    return size;
}