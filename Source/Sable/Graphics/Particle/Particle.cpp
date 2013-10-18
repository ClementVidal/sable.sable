#include <Sable/Graphics/Particle/Particle.h>

using namespace Sable;

CParticle::CParticle()
{
	Reset();
}

CParticle&	CParticle::operator=( const CParticle& other )
{
	Age = other.Age;
	Position = other.Position;
	Velocity = other.Velocity;
	Color = other.Color;
	Size = other.Size;

	return *this;
}


Void CParticle::Reset()
{
	Age = -1.0f;
}
