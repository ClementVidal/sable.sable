#ifndef _SABLE_GRAPHICS_VIEWPORT_
#define _SABLE_GRAPHICS_VIEWPORT_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\ManagedObject\ManagedObject.h>
#include <Sable\Core\Math\Vector2i.h>

#include <Sable\Graphics\Viewport\Impl\Header.h>
#include <Sable\Graphics\Viewport\ShaderConnector\Viewport.h>

namespace Sable
{

/** 
Viewport
*/
class CViewport : public CManagedObject
{

	DEFINE_MANAGED_CLASS( CViewport );

public:

    /** @name DataType*/
    //@{
    //@}

    /** @name Constructor/Destructor*/
    //@{
    CViewport();
    ~CViewport();
    //@}

	/** @name Accessors*/
	//@{
	const CShaderConnectorViewport& GetShaderConnector() const;
	const CVector2i&	GetSize() const;
	const CVector2i&	GetPosition() const;
    Int32				GetTopLeftX() const;
    Int32				GetTopLeftY() const;
    UInt32				GetWidth() const;
    UInt32				GetHeight() const;
    Float32				GetMinDepth() const;
    Float32				GetMaxDepth() const;

    Void Set( Int32 topLeftX, Int32 topLeftY, UInt32 width, UInt32 height, Float32 minDepth, Float32 maxDepth );
	//@}

	/** @name Manipulator*/
	//@{
	CVector2i NormalizedCoordToViewportCoord( const CVector2f& p ) const;
    Void	Activate();
	Void	Resize( const CVector2i& s );
	//@}

private:

	//Methods

	//Attributes
    CVector2i					m_Position;
    CVector2i					m_Size;
    Float32						m_MaxDepth;
    Float32						m_MinDepth;
	Bool						m_IsDirty;
	CShaderConnectorViewport	m_ShaderConnector;
    CImplViewport				m_Impl;

};


}

#endif
