#ifndef _SABLE_GUI_COMMON_NINEPATCH_
#define _SABLE_GUI_COMMON_NINEPATCH_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\File\FilePath.h>
#include <Sable\Core\Geometry\Rect2Di.h>
#include <Sable\Graphics\Texture\Texture2D.h>

namespace Sable
{

class CIODevice;

/**  
\ingroup Gui
*/
class CGuiNinePatch : public CManagedObject
{

public:

	/** @name Type*/
	//@{
	struct SHeader
	{
	public:
		SHeader();
		Bool IsValidFourCC() const;
		UInt32 GetVersion() const;

	private:
		Char	m_FourCC[4];
		UInt32	m_Version;
	};

	struct SInfo
	{
		SInfo();
		UInt32  HStretchableStart;
		UInt32  HStretchableEnd;
		UInt32  VStretchableStart;
		UInt32  VStretchableEnd;
	};

	enum EPatch
	{
		nPatch_TopLeft = 0,
		nPatch_Top,
		nPatch_TopRight,
		nPatch_Left,
		nPatch_Right,
		nPatch_BottomLeft,
		nPatch_Bottom,
		nPatch_BottomRight,
		nPatch_Count,
		nPatch_None = -1
	};
	//@}

	/** @name Constructor/Destructor*/
	//@{
	CGuiNinePatch( CMemoryHeap* heap = NULL );
	~CGuiNinePatch();
	//@}

	/** Accessors*/
	//@{    
	CTexture2D*		GetTexture() const;
	const CRect2Di& GetPatchRect( EPatch patch ) const;
	//@}

	/** Manipulator*/
	//@{
	Bool	SetRawDataFromFile( const CFilePath& path );
	Bool	SetRawData( CIODevice& device, UInt32 byteCount = 0 );
	//@}

private:

	// Types

	// Methods

	// Attributes
	CRef<CTexture2D>	m_Texture;
	CRect2Di			m_PatchesRect[nPatch_Count];

};

}

#endif
