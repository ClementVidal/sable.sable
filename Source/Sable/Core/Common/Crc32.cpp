#include <Sable\Core\Common\Crc32.h>

using namespace Sable;

UInt32 CCrc32::m_PolynomialTable[256];
Bool CCrc32::m_PolynomialTableGenerated = FALSE;


CCrc32::CCrc32()
{
	GeneratePolynomialTable();

    m_Sum = 0;
}

CCrc32::CCrc32( const Byte* b, UInt32 len )
{
	GeneratePolynomialTable();

	m_Sum = 0;

	Compute( b, len );
}

CCrc32::~CCrc32()
{
}

Void CCrc32::GeneratePolynomialTable() 
{
	if( m_PolynomialTableGenerated )
		return;

	m_PolynomialTableGenerated = TRUE;

	UInt32 crc, poly;
	Int32 i, j;

	poly = 0xEDB88320L;
	for (i = 0; i < 256; i++)
	{
		crc = i;
		for (j = 8; j > 0; j--)
		{
			if (crc & 1)
			{
				crc = (crc >> 1) ^ poly;
			}
			else
			{
				crc >>= 1;
			}
		}
		m_PolynomialTable[i] = crc;
	}

}

UInt32 CCrc32::Get() const
{
    return m_Sum;
}

Bool CCrc32::operator==( const CCrc32& other )
{
    return m_Sum == other.m_Sum;
}

Bool CCrc32::operator!=( const CCrc32& other )
{
    return m_Sum != other.m_Sum;
}

Void CCrc32::Compute( const Byte* b, UInt32 len )
{
	m_Sum = 0xFFFFFFFF;
    for(UInt32 i = 0; i < len; i++)
	{
		m_Sum = ((m_Sum >> 8) & 0x00FFFFFF) ^ m_PolynomialTable[(m_Sum ^ *b++ ) & 0xFF];
	}
	m_Sum = (m_Sum ^ 0xFFFFFFFF);
}