#ifndef _SABLE_GRAPHICS_STATES_BLEND_
#define _SABLE_GRAPHICS_STATES_BLEND_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Graphics/States/States.h>

#include <Sable/Graphics/States/Impl/Header.h>

namespace Sable
{

class CRenderer;

/**  
\ingroup GraphicsStates
CStatesBlend
*/
class CStatesBlend : public CManagedObject
{

	DEFINE_MANAGED_CLASS( CStatesBlend );

public:

	/** @name Constructor/destructor */
	//@{
	CStatesBlend();
	~CStatesBlend();
	//@}

	/** @name DataTypes*/
	//@{
	struct SDesc
	{
		SDesc();
		Bool	BlendEnable[8];
		UInt32	WriteMask[8];
		EStateBlend	SrcColorBlend;
		EStateBlend	DstColorBlend;
		EStateBlend	SrcAlphaBlend;
		EStateBlend	DstAlphaBlend;
		EStateBlendOp	AlphaBlendOp;
		EStateBlendOp	ColorBlendOp;
	};
	//@}

	/** @name Accessors*/
	//@{
	const SDesc&		GetDesc() const;
    CImplStatesBlend& GetImpl();
	//@}
	
	/** @name Manipulator*/
    //@{
	Bool	Serialize( CPersistentArchive& ar );
    Void    Acquire( const SDesc& desc );
    //@}

private:

    // Friendship
    friend class CRenderer;

	// Types

    // Methods
    Void Activate( CRenderer& renderer );

    // Attributes
    SDesc				m_Desc;

    CImplStatesBlend    m_Impl;

};

}

#endif
