#ifndef _SABLE_GRAPHICS_STATES_IMPL_GLES_BLEND_
#define _SABLE_GRAPHICS_STATES_IMPL_GLES_BLEND_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Graphics\States\Impl\Stub\Blend.h>

#include <GLES2\gl2.h>

namespace Sable
{

/** 

*/
class CImplGLESStatesBlend : public CImplStubStatesBlend
{

public:

    /** @name Constructor/Destructor*/
    //@{
    CImplGLESStatesBlend( CStatesBlend& publicImpl );
    ~CImplGLESStatesBlend();
    //@}

    /** @name Accessors*/
    //@{
    Void Acquire();
    Void Activate();
    //@}

protected:

    // Methods
    UInt32                  TranslateWriteMask( UInt32 mode );
	GLenum          		TranslateBlendOp( EStateBlendOp mode );
	GLenum             		TranslateBlend( EStateBlend mode );

    // Attributes

};

}

#endif
