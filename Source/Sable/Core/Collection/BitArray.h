#ifndef _SABLE_CORE_COLLECTION_BITFLAGS_
#define _SABLE_CORE_COLLECTION_BITFLAGS_

#include <Sable\Core\Common\DataTypes.h>

namespace Sable
{

class CPersistentArchive;

/**
\ingroup CoreCollection
Bit array. 
Care must be taken to only use a multiple of 8 as BitCount !!!
*/
template< UInt32 BitCount >
class CBitArray
{

public:

	/** @name Constructor/Destructor*/
    //@{
	CBitArray();
	CBitArray( const CBitArray& other );
	~CBitArray();
    //@}

	/** @name Operator*/
    //@{
	Bool		 operator ==( const CBitArray& other );
    CBitArray&   operator =( const CBitArray& other );
    //@}

	/** @name Accessors*/
    //@{
    //@}

	/** @name Mutator*/
    //@{
	Void	SetBit( UInt32 bit, Bool value );
	Void	SetBit( UInt32 bit );
	Void	ClearBit( UInt32 bit );
	Bool	GetBit( UInt32 bit ) const ;
    //@}

    /** @name Manipulator*/
    //@{
    Void	Clear();
	Bool	Serialize( CPersistentArchive& ar );
    //@}

private:

	// DataType
	enum 
	{
		ByteCount = BitCount/8
	};

    //Attributes
	UInt8 m_Value[ByteCount];

};

#include <Sable\Core\Collection\BitArray.hpp>

typedef CBitArray<16>		CBitArray16;
typedef CBitArray<32>		CBitArray32;
typedef CBitArray<64>		CBitArray64;
typedef CBitArray<128>		CBitArray128;

}

#endif
