#ifndef _SABLE_GRAPHICS_STATES_SAMPLER_
#define _SABLE_GRAPHICS_STATES_SAMPLER_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Graphics/States/States.h>
#include <Sable/Graphics/States/Impl/Header.h>

namespace Sable
{

class CRenderer;

/**  
\ingroup GraphicsStates
CStatesSampler
*/
class CStatesSampler : public CManagedObject
{

	DEFINE_MANAGED_CLASS( CStatesSampler );

public:

	/** @name Constructor/destructor */
	//@{
	CStatesSampler();
	~CStatesSampler();
	//@}

	/** @name DataTypes*/
	//@{
	struct SDesc
	{
		SDesc();
		EStateFilter	MinFilter;
		EStateFilter	MagFilter;
		EStateFilter	MipFilter;
		EStateAddress	AddressU;
		EStateAddress	AddressV;
		EStateAddress	AddressW;
		Float32			MinLOD;
		Float32			MaxLOD;
	};
	//@}

	/** @name Accessors*/
	//@{
	const CImplStatesSampler&	GetImpl() const;
	const SDesc&	GetDesc() const;
	//@}
	
	/** @name Manipulator*/
    //@{
    Void    Acquire( const SDesc& desc );
    //@}

private:

    // Friendship

    // Types

    // Methods

    // Attributes
    SDesc	m_Desc;

	CImplStatesSampler	m_Impl;

};

}

#endif
