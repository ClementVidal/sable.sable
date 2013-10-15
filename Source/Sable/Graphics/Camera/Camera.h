#ifndef _SABLE_GRAPHICS_CAMERA_CAMERA_
#define _SABLE_GRAPHICS_CAMERA_CAMERA_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Graphics\Node\Spatial.h>
#include <Sable\Core\ManagedObject\Macro.h>
#include <Sable\Core\Geometry\Frustum.h>
#include <Sable\Core\Geometry\Ray.h>
#include <Sable\Graphics\Camera\ShaderConnector\Camera.h>

namespace Sable
{

/**
\ingroup GraphicsCamera
Base Class for camera
*/
class CCamera : public CNodeSpatial
{

	DEFINE_MANAGED_CLASS( CCamera );

public:

    /** @name Constructor/Destructor*/
    //@{
	CCamera();
	CCamera( CNode& parent );
	virtual ~CCamera();
    //@}

	/** @name Operator*/
	//@{
    CCamera& operator=( const CCamera& other );
	//@}

    /** @name Accessors*/
    //@{
	CShaderConnectorCamera&	GetShaderConnector();
	Void					SetCameraPosition( const CVector3f& Pos);
	Void					SetWorldUp( const CVector3f& Up);
	const CVector3f&		GetCameraPosition() const;
	const CVector3f&		GetTargetPosition() const;
	const CVector3f&		GetWorldUp() const;
	const CVector3f			GetCameraDirection() const;
	const CFrustum&			GetFrustum( ) const { return m_Frustum; }

	const CMatrix4x4f&		GetProjectionMatrix() const ;	
	const CMatrix4x4f&		GetViewMatrix()	const;			
	const CMatrix4x4f&		GetInverseViewMatrix() const ;
	const CMatrix4x4f&		GetViewProjectionMatrix() const	;
    //@}

    /** @name Manipulator*/
    //@{
	virtual Float32			ComputeFitDistance( const CSphere& sphere );
	virtual Bool			Update( );
	virtual CRay			GetRayFrom2DPos( const CVector2f& viewPlanePoint ) const;
	virtual CVector3f		Get3DPointFrom2DPos( const CVector2f& viewPlanePoint, Float32 viewPlaneDist = 1.0f) const;
    virtual CVector2f		GetFrustumSizeAtDist( Float32 dist ) const;
    //@}

protected:

	//Attributes
	CShaderConnectorCamera	m_ShaderConnector;
	CMatrix4x4f				m_ViewMatrix;	
	CMatrix4x4f				m_InverseViewMatrix;
    CMatrix4x4f				m_ProjectionMatrix;		
	CMatrix4x4f				m_ViewProjectionMatrix;
	CFrustum				m_Frustum;
    CVector3f				m_WorldUp;

	// Methods
	Void EvaluateCameraMatrix();

private:

	//Methods
    
};

Inline
const CMatrix4x4f& CCamera::GetProjectionMatrix() const 	
{
	return m_ProjectionMatrix; 
}

Inline
const CMatrix4x4f& CCamera::GetViewMatrix()	const			
{ 
	return m_ViewMatrix; 
}

Inline
const CMatrix4x4f& CCamera::GetInverseViewMatrix() const	
{ 
	return m_InverseViewMatrix; 
}

Inline
const CMatrix4x4f& CCamera::GetViewProjectionMatrix() const	
{ 
	return m_ViewProjectionMatrix;
}

Inline
Void CCamera::SetCameraPosition( const CVector3f& Pos)
{
	GetLocalMatrix().SetTranslationComponent(Pos);
}

Inline
Void CCamera::SetWorldUp( const CVector3f& Up)
{
	DebugError( "Not Implemented" );
}

Inline
const CVector3f& CCamera::GetCameraPosition() const 
{
	return GetWorldMatrix().GetTranslationComponent();
}

Inline
const CVector3f& CCamera::GetWorldUp() const
{
	DebugError( "Not Implemented" );
	return m_WorldUp;
}

}

#endif
