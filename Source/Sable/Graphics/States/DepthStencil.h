#ifndef _SABLE_GRAPHICS_STATES_DEPTHSTENCIL_
#define _SABLE_GRAPHICS_STATES_DEPTHSTENCIL_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Graphics\States\States.h>
#include <Sable\Graphics\States\Impl\Header.h>

namespace Sable
{

/**  
\ingroup GraphicsStates
CStatesDepthStencil
*/
class CStatesDepthStencil : public CManagedObject
{

	DEFINE_MANAGED_CLASS( CStatesDepthStencil );

public:

	/** @name Constructor/destructor */
	//@{
	CStatesDepthStencil();
	virtual ~CStatesDepthStencil();
	//@}

	/** @name DataTypes*/
	//@{
	struct SDesc
	{
		SDesc();
		Bool	DepthTestEnable;
		Bool	DepthWriteEnable;
		EStateDepthFunc	DepthFunc;
	};
	//@}

	/** @name Accessors*/
	//@{
	const SDesc&	GetDesc() const;
    CImplStatesDepthStencil& GetImpl();
	//@}
	
	/** @name Manipulator*/
    //@{
    Void    Acquire( const SDesc& desc );
	Bool	Serialize( CPersistentArchive& ar );
	//@}

private:

    // Friendship
    friend class CRenderer;

	// Types

    // Methods
    Void Activate( CRenderer& renderer );

    // Attributes
	SDesc					m_Desc;
    CImplStatesDepthStencil m_Impl;

};

}

#endif
