#ifndef _SABLE_CORE_XML_READER_
#define _SABLE_CORE_XML_READER_

#include <Sable/Core/Common/DataTypes.h>

namespace Sable
{

class CFile;

/** 
\ingroup Xml
*/
class CXmlReader 
{

public:
    
    /** @name DataTypes*/
    //@{
    enum ENodeType
    {
        nNodeType_Text,
        nNodeType_Element,
        nNodeType_ElementEnd,
        nNodeType_Comment, 
        nNodeType_Unknown
    };

	enum EEncoding
	{
		nEncoding_Ainsi = 0,
		nEncoding_UTF8,
		nEncoding_UTF16BE,
		nEncoding_UTF16LE,
		nEncoding_Count,
		nEncoding_None = -1
	};

    struct SString
    {
        Char* Buffer;
        UInt32 Length;
    };

    struct SAttribute
    {
        SString Name;
        SString Value;
    };
    //@}

    /** @name Constructor/Destructor*/
    //@{
    CXmlReader( );
    ~CXmlReader();
    //@}

    /** @name Accessor*/
    //@{
    //@}

    /** @name Manipulator*/
    //@{
    Bool        ReadFile( CFile& file );
    Bool        ReadNode( Bool skipComment = TRUE );
    UInt32      GetAttributeCount() const;
    ENodeType   GetNodeType() const;
	Bool	    GetNodeName( Char* name, UInt32 length ) const;
    Bool        GetAttributeName( UInt32 idx, Char* name, UInt32 length ) const;
    Bool        GetAttributeValue( UInt32 idx, Char* value, UInt32 length ) const;
    Int32       GetAttributeValueAsInt( UInt32 idx ) const;
    Int32       GetAttributeValueAsInt( String name ) const;
    Float32     GetAttributeValueAsFloat( UInt32 idx ) const;
    Float32     GetAttributeValueAsFloat( String name ) const;
    //@}

private:

	// DataTypes
	typedef CArray<SAttribute> AttriuteTable;

    // Methods
    Void ParseCurrentNode();
    Bool SetText(Char* start, Char* end);
    Void ParseOpeningXMLElement();
    Void ParseClosingXMLElement();
    Void ParseComment();
    Void IgnoreDefinition();
    Void ClearAttributesTable();
    Void AddAttributes(CXmlReader::SAttribute& attr);
	Void DetectEncoding();
    SAttribute* GetAttribute( String name ) const;
    SAttribute* GetAttribute( UInt32 idx ) const;

    // Attributes
    Char*               m_TextBegin;
    Char*               m_TextData;
    Char*               m_P ;
    ENodeType           m_CurrentNodeType;
    UInt32              m_TextSize;
    AttriuteTable		m_AttributesTable;
    UInt32              m_AttributesCount;
    SString             m_NodeName;
    Bool                m_IsEmptyElement;
    CArray<Char>        m_Data;
	EEncoding			m_Encoding;
};

}

#endif