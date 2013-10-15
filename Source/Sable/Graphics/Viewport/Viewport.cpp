#include <Sable\Graphics\Viewport\Viewport.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1( Sable, CViewport, CManagedObject );

CViewport::CViewport( ) :
    m_Impl( *this ),
	m_ShaderConnector( *this )
{
	m_IsDirty = TRUE;
    Set( 0,0,0,0,0.0f, 0.0f );
}

CViewport::~CViewport()
{
}

const CVector2i& CViewport::GetSize() const
{
	return m_Size;
}

const CVector2i& CViewport::GetPosition() const
{
	return m_Position;
}

const CShaderConnectorViewport& CViewport::GetShaderConnector() const
{
	return m_ShaderConnector;
}

Void CViewport::Activate()
{
    DebugGraphicCommandGroup("CViewport::Activate");
	if( m_IsDirty )
		m_Impl.Activate();

	m_IsDirty = FALSE;
}

Void CViewport::Set( Int32 topLeftX, Int32 topLeftY, UInt32 width, UInt32 height, Float32 minZ, Float32 maxZ )
{
	if( m_Position.GetX() != topLeftX || m_Position.GetY() != topLeftY || 
		m_Size.GetX() != width || m_Size.GetY() != height ||
		m_MaxDepth != maxZ || m_MinDepth != minZ )
	{
		m_IsDirty = TRUE;
	}

    m_Position.Set( topLeftX, topLeftY );
    m_Size.Set( width, height );
    m_MaxDepth = maxZ;
    m_MinDepth = minZ;
}

/**
Convert normalized coordinate ranging from X:[-1 1] Y:[-1 1] to viewport coord X:[0,Width] X:[0,Height] 
*/
CVector2i CViewport::NormalizedCoordToViewportCoord( const CVector2f& p ) const
{
	CVector2f p1 = ( p + 1.0f ) / 2.0f;
	p1 *= CVector2f( (Float32)m_Size.GetX(), (Float32)m_Size.GetY() );

	return p1;
}

Void CViewport::Resize( const CVector2i& s )
{
	if( m_Size != s )
		m_IsDirty = TRUE;

	m_Size = s;
}

Int32 CViewport::GetTopLeftX() const
{
    return m_Position.GetX();
}

Int32 CViewport::GetTopLeftY() const
{
    return m_Position.GetY();
}

UInt32 CViewport::GetWidth() const
{
    return m_Size.GetX();
}

UInt32 CViewport::GetHeight() const
{
    return m_Size.GetY();
}

Float32 CViewport::GetMinDepth() const
{
    return m_MinDepth;
}

Float32 CViewport::GetMaxDepth() const
{
    return m_MaxDepth;
}