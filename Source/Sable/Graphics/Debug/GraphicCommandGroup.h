#ifndef _SABLE_GRAPHICS_DEBUG_GRAPHICCOMMANDGROUP_
#define _SABLE_GRAPHICS_DEBUG_GRAPHICCOMMANDGROUP_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Setup.h>

#ifdef SETUP_CONFIG_DEBUG

#define DebugGraphicCommandGroup( name ) \
	Sable::CDebugGraphicCommandGroup __graphicCommand( name ); 

#else

#define DebugGraphicCommandGroup( name )

#endif 

namespace Sable
{

/** 
\ingroup GraphicsDebug
Performances analyzer.
Actually provide only a bridge between the system and PIX Methods
*/
class CDebugGraphicCommandGroup
{

public:

	/** @name Constructor/destructor*/
	//@{
	CDebugGraphicCommandGroup( String name );
	~CDebugGraphicCommandGroup();
	//@}

	/** @name Static Manipulator*/
	//@{

	//@}

private:	

	// Type

	// Method
	Void BeginRenderSequence( String name );
	Void EndRenderSequence( );

	// Attribute

};

}

#endif
