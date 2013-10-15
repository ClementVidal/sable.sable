#ifndef _GRAPHICS_TEXTURE_TEXTURE_
#define _GRAPHICS_TEXTURE_TEXTURE_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\Collection\BitArray.h>
#include <Sable\Graphics\Texture\TextureInfo.h>
#include <Sable\Core\Persistent\Archive.h>
#include <Sable\Core\ManagedObject\ManagedObject.h>

namespace Sable
{

/** 
Texture. 
*/
class CTexture : public CManagedObject
{

    DEFINE_MANAGED_CLASS( CTexture );

public:

	/** @name Constructor/Destructor*/
    //@{
	CTexture( );
	CTexture( const CTexture& other );
	virtual ~CTexture();
    //@}

    /** @name Operator*/
    //@{
    CTexture& operator=( const CTexture& other );
    //@}

	/** @name Accessors*/
	//@{
	Void		            SetTextureInfo( const CTextureInfo& info );
	const CTextureInfo&		GetTextureInfo()const;
	EStateFilter          GetMagFilterMode( ) const ;
	EStateFilter          GetMinFilterMode( ) const ;     
	EStateAddress         GetAdressMode( ) const ; 
	Void					SetMagFilterMode( const EStateFilter state );
	Void					SetMinFilterMode( const EStateFilter state );   
	Void					SetAdressMode( const EStateAddress state ); 
	//@}

	/** @name Manipulator*/
	//@{
	//@}

private:

	// Method

	// Attribute
    EStateFilter          m_MinFilteringMode;
    EStateFilter          m_MagFilteringMode;
    EStateAddress         m_AdressMode;
	CTextureInfo			m_TextureInfo;
};  

}
#endif
