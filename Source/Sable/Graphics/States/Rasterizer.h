#ifndef _SABLE_GRAPHICS_STATES_RASTERIZER_
#define _SABLE_GRAPHICS_STATES_RASTERIZER_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Graphics\States\States.h>
#include <Sable\Graphics\States\Impl\Header.h>

namespace Sable
{

/**  
\ingroup GraphicsStates
CStatesRasterizer
*/
class CStatesRasterizer : public CManagedObject
{

	DEFINE_MANAGED_CLASS( CStatesRasterizer );

public:

	/** @name DataTypes */
	//@{
	struct SDesc
	{
		SDesc();
		EStateFillMode	FillMode;
		EStateCullMode	CullMode;
		Bool			MultiSamplingEnabled;
		Bool			ScissorRectEnabled;
		Float32			DepthBias;			
	};
	//@}

	/** @name Constructor/destructor */
	//@{
	CStatesRasterizer();
	~CStatesRasterizer();
	//@}

	/** @name Accessors*/
	//@{
	const SDesc&	GetDesc() const;
    CImplStatesRasterizer& GetImpl();
	//@}
	
	/** @name Manipulator*/
    //@{
    Void    Acquire( const SDesc& desc );
    //@}

private:

    // Friendship
    friend class CRenderer;

	// Types

    // Methods
    Void Activate( CRenderer& renderer );
	Bool Serialize( CPersistentArchive& ar );

    // Attributes
    SDesc					m_Desc;
    CImplStatesRasterizer   m_Impl;

};

}

#endif
