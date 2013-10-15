#ifndef _GRAPHICS_PARTICLE_PARTICLE_
#define _GRAPHICS_PARTICLE_PARTICLE_

namespace Sable
{

/** 
\ingroup GraphicsParticle
Represent a single in a particle group
*/
class CParticle 
{
	
public:

	/** @name Constructor/Destructor*/
	//@{
	CParticle();
	//@}

	//**@name operator*/
	//@{
	CParticle&	operator=( const CParticle& other );
	//@}

	//**@name Manipulator*/
	//@{
	Void Reset();
	//@}

	//**@name Attributes*/
	//@{
	CVector3f	Position;
	CVector3f	Velocity;
    CColor		Color;
   	Float32 	Size;
	Float32		Age;
	//@}

private:

	// Methods

	// Attributes
	
};

}

#endif


