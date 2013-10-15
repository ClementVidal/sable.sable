#ifndef _GRAPHICS_CAMERA_PERSPECTIVE_
#define _GRAPHICS_CAMERA_PERSPECTIVE_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Graphics\Camera\Camera.h>

namespace Sable
{

/** 
\ingroup GraphicsCamera
Perspective Camera. 
*/
class CCameraPerspective : public CCamera
{

	DEFINE_MANAGED_CLASS( CCameraPerspective );

public:

	/** @name Constructor/Destructor*/
    //@{
	CCameraPerspective();
	CCameraPerspective( CNode& parent );
	virtual ~CCameraPerspective();
    //@}

	/** @name Operator*/
    //@{
    //@}

	/** @name Accessor*/
	//@{
	Float32	    GetFieldOfView() const;
	Float32	    GetAspect() const;
	Float32	    GetNearPlane() const;
	Float32	    GetFarPlane() const;
	Void	    SetFOV( const Float32 value );
	Void	    SetAspect( const Float32 value );
	Void	    SetNearPlane( const Float32 value );
	Void	    SetFarPlane( const Float32 value );
	Void		GetLocalBoundingBox( CAABox& box ) const;
	//@}

	/** @name Mutator*/
    //@{
    //@}

	/** @name Manipulator*/
	//@{
	Float32		ComputeFitDistance( const CSphere& sphere );
	Void        SetProjectionMatrix( const Float32 FOV, const Float32 Aspect, const Float32 NearPlane, const Float32 FarPlane );
	CRay        GetRayFrom2DPos( const CVector2f& viewPlanePoint ) const;
	CVector3f   Get3DPointFrom2DPos( const CVector2f& viewPlanePoint, Float32 viewPlaneDist = 1.0f) const;
    CVector2f   GetFrustumSizeAtDist( Float32 dist ) const;
	//@}

private:

	//Mathods

	//Attrivutes
	Float32			m_FOV;        
	Float32			m_Aspect;
	Float32			m_NearPlane;
	Float32			m_FarPlane;

};

Inline
Float32	CCameraPerspective::GetFieldOfView() const
{
	return m_FOV;
}

Inline
Float32	CCameraPerspective::GetAspect() const
{
	return m_Aspect;
}

Inline
Float32	CCameraPerspective::GetNearPlane() const
{
	return m_NearPlane;
}

Inline
Float32	CCameraPerspective::GetFarPlane() const
{
	return m_FarPlane;
}

Inline
Void CCameraPerspective::SetFOV( const Float32 value )
{
	if( value <= 0.0f || value >= MathPi )
		return;

	m_FOV = value;
	m_ProjectionMatrix.SetFromLHPerspProjectionValues( m_FOV, m_Aspect, m_NearPlane,m_FarPlane);
}

Inline
Void CCameraPerspective::SetAspect( const Float32 value )
{
	m_Aspect = value;
	m_ProjectionMatrix.SetFromLHPerspProjectionValues( m_FOV, m_Aspect, m_NearPlane,m_FarPlane);
}

Inline
Void CCameraPerspective::SetNearPlane( const Float32 value )
{
	if( value < 0.0f || value >= m_FarPlane )
		return;

	m_NearPlane = value;
	m_ProjectionMatrix.SetFromLHPerspProjectionValues( m_FOV, m_Aspect, m_NearPlane,m_FarPlane);
}

Inline
Void CCameraPerspective::SetFarPlane( const Float32 value )
{
	if( value <= m_NearPlane )
		return;

	m_FarPlane = value;
	m_ProjectionMatrix.SetFromLHPerspProjectionValues( m_FOV, m_Aspect, m_NearPlane,m_FarPlane);
}

}
#endif
