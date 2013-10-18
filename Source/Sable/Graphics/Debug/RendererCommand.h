#ifndef _SABLE_GRAPHICS_DEBUG_RENDERERCOMMAND_
#define _SABLE_GRAPHICS_DEBUG_RENDERERCOMMAND_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/ManagedObject/Ref.h>

namespace Sable
{

class CRenderer;
class CGeometryMesh;

/** 
\ingroup GraphicsDebug
Base class for debug renderer command
*/
class CDebugRendererCommand
{

public:

	/** @name Constructor/destructor*/
	//@{
	CDebugRendererCommand();
	//@}

	/** @name Accessor*/
	//@{
	EStateFillMode		GetFillMode() const;
	Void				SetFillMode( EStateFillMode mode );
	Bool				GetDepthTestEnabled() const;
	Void				SetDepthTestEnabled( Bool onOff );
	Void				SetWorldViewProjectionMatrix( const CMatrix4x4f& matrix );
	const CMatrix4x4f&	GetWorldViewProjectionMatrix( )const ;
	Void				SetMesh( const CGeometryMesh& mesh ) ;
	CGeometryMesh&  	GetMesh() const ;
	Void				SetColor( const CColor& color ) ;
	const				CColor& GetColor( ) const ;
	//@}

private:

	// Attributes
	CMatrix4x4f					m_WorldViewProjectionMatrix;
	CColor						m_Color;
	CRef<CGeometryMesh>         m_Mesh;
	Bool						m_DethTestEnabled;
	EStateFillMode				m_FillMode;

};

}

#endif
