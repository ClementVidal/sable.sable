#ifndef _SABLE_CORE_COMMON_CRC32_
#define _SABLE_CORE_COMMON_CRC32_

#include <Sable\Core\Common\DataTypes.h>

namespace Sable
{

/** 
\ingroup CoreCommon
32 bytes checksum

This code come from 
http://www.codeproject.com/KB/recipes/checksum.aspx
*/
class CCrc32
{

public:

    /** @name Constructor/Destructor*/
    //@{
    CCrc32();
    CCrc32( const Byte* b, UInt32 len );
    ~CCrc32();
    //@}

    /** @name Operator*/
    //@{
    Bool operator==( const CCrc32& other );
    Bool operator!=( const CCrc32& other );
    //@}

    /** @name Accessors*/
    //@{
    UInt32  Get() const;
    //@}

    /** @name Manipulator*/
    //@{
    Void    Compute( const Byte* b, UInt32 len );
    //@}

private:

    // Methods
	static Void GeneratePolynomialTable();

    // Attributes
	static UInt32	m_PolynomialTable[256];
	static Bool		m_PolynomialTableGenerated;
    
    UInt32 m_Sum;

};



}
#endif
