#include <Sable\Graphics\Debug\RendererCommand.h>

using namespace Sable;

CDebugRendererCommand::CDebugRendererCommand()
{
	m_Mesh = NULL;
	m_DethTestEnabled = TRUE;
	m_FillMode = nStateFillMode_WireFrame;
}

Bool CDebugRendererCommand::GetDepthTestEnabled() const
{
	return m_DethTestEnabled;
}

Void CDebugRendererCommand::SetFillMode( EStateFillMode mode )
{
	m_FillMode = mode;
}

EStateFillMode CDebugRendererCommand::GetFillMode() const
{
	return m_FillMode;
}

Void CDebugRendererCommand::SetDepthTestEnabled( Bool onOff )
{
	m_DethTestEnabled = onOff;
}

Void CDebugRendererCommand::SetWorldViewProjectionMatrix( const CMatrix4x4f& matrix )
{
	m_WorldViewProjectionMatrix = matrix;
}

const CMatrix4x4f& CDebugRendererCommand::GetWorldViewProjectionMatrix( )const 
{
	return m_WorldViewProjectionMatrix;
}

Void CDebugRendererCommand::SetMesh( const CGeometryMesh& mesh )
{
	m_Mesh = &mesh;
}

CGeometryMesh& CDebugRendererCommand::GetMesh() const
{
	return *m_Mesh;
}

Void CDebugRendererCommand::SetColor( const CColor& color )
{
	m_Color = color;
}

const CColor& CDebugRendererCommand::GetColor( ) const 
{
	return m_Color;
}
