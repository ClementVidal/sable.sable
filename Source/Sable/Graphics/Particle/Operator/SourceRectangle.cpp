#include <Sable/Graphics/Particle/Operator/SourceRectangle.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1_ALLOC( Sable, CParticleOpSourceRectangle, CParticleOpSource );

CParticleOpSourceRectangle::CParticleOpSourceRectangle()
{
	m_XSize = 1.0f;
	m_YSize = 1.0f;
	m_ZSize = 1.0f;

	m_Origin = CVector3f::Zero;
}

CParticleOpSourceRectangle::~CParticleOpSourceRectangle()
{
}

Void CParticleOpSourceRectangle::ConfigureNewParticle( CParticleGroup& sim, CParticle& particle )
{
	CParticleOpSource::ConfigureNewParticle( sim, particle );

	CVector3f off;

	off.SetX( m_XSize * m_Random.GetRandomNumber(-1.0f,1.0f) );
	off.SetY( m_YSize * m_Random.GetRandomNumber(-1.0f,1.0f) );
	off.SetZ( m_ZSize * m_Random.GetRandomNumber(-1.0f,1.0f) );

	particle.Position = sim.GetOrigin() + m_Origin + off;
	particle.Velocity = sim.GetDirection();
	
}

Void	CParticleOpSourceRectangle::SetXSize( Float32 f )
{
	m_XSize = f;
}

Float32 CParticleOpSourceRectangle::GetXSize() const
{
	return m_XSize;
}

Void	CParticleOpSourceRectangle::SetYSize( Float32 f )
{
	m_YSize = f;
}

Float32 CParticleOpSourceRectangle::GetYSize() const
{
	return m_YSize;
}

Void	CParticleOpSourceRectangle::SetZSize( Float32 f )
{
	m_ZSize = f;
}

Float32 CParticleOpSourceRectangle::GetZSize() const
{
	return m_ZSize;
}

Void CParticleOpSourceRectangle::SetOrigin( const CVector3f& dir )
{
	m_Origin = dir;
}

const CVector3f& CParticleOpSourceRectangle::GetOrigin( )
{
	return m_Origin;
}

Bool CParticleOpSourceRectangle::Serialize( CPersistentArchive& ar )
{
	Int16 version = 0;

	if( ar.BeginScope( WT("OpSourceRectangle"), version ) == 0 )
	{
		ar.Serialize( m_Origin, WT("Origin") );
		ar.Serialize( m_XSize, WT("XSize") );
		ar.Serialize( m_YSize, WT("YSize") );
		ar.Serialize( m_ZSize, WT("ZSize") );

		ar.EndScope();
	}
	else
	{
		return FALSE;
	}

	return CParticleOpSource::Serialize( ar );
}