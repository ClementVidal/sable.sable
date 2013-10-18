#include <Sable/Core/Xml/Reader.h>

#include <Sable/Core/File/File.h>
#include <Sable/Core/String/Primitives.h>

#define XMLREADER_ATTRIBUTE_BUFFER_INC 16
#define XMLREADER_ATTR_NAME_LENGTH 256

using namespace Sable;

CXmlReader::CXmlReader( )
{
	m_AttributesTable.SetItemCount( XMLREADER_ATTRIBUTE_BUFFER_INC );
}

CXmlReader::~CXmlReader()
{
}

Void CXmlReader::DetectEncoding()
{
	Int32 c0 = 0x000000ff & m_Data[0];
	Int32 c1 = 0x000000ff & m_Data[1];
	Int32 c2 = 0x000000ff & m_Data[2];

	m_Encoding = nEncoding_None;

	if( ( c0 == 0xef ) && ( c1 == 0xbb ) && ( c2 == 0xbf ) )
	{
		m_Encoding = nEncoding_UTF8;
	}
	else if( ( c0 == 0xfe ) && ( c1 == 0xff ) )
	{
		m_Encoding = nEncoding_UTF16BE;
	}
	else if( ( c0 == 0xff ) && ( c1 == 0xfe ) )
	{
		m_Encoding = nEncoding_UTF16LE;
	}
	else
	{
		m_Encoding = nEncoding_Ainsi;
	}
}

Bool CXmlReader::ReadFile( CFile& file )
{
    if( !file.IsOpen() )
        return FALSE;

	Int32 size = file.GetSize();		
	size += 1; // We need two terminating 0's at the end.
	           // For ASCII we need 1 0's, for UTF-16 2, for UTF-32 4.

    m_Data.SetItemCount( size );

	if (!file.Read(m_Data.GetBuffer(), size-1))
	{
		return FALSE;
	}

	DetectEncoding();

	if( m_Encoding != nEncoding_Ainsi )
	{
		DebugLogWarning( "CXmlReader::ReadFile - Invalid file encoding" );
		return FALSE;
	}

	// add zeros at end
	m_Data[size-1] = 0;

    // no need to convert
    m_TextBegin = m_Data.GetBuffer();
    m_TextData = m_Data.GetBuffer();
    m_TextSize = size;
    m_P = m_TextBegin;

	return true;
}

/**
Read and parse the next available node.
\param skipComment If TRUE skip all comments
\return TRUE if the node was parsed succesfully false otherwise or if it was the last node in the XML document
*/
Bool CXmlReader::ReadNode( Bool skipComment )
{
    while(CharIsWhiteSpace(*m_P) && *m_P != 0 )
        ++m_P;

	// if not end reached, parse the node
	if ( m_P && (UInt32)(m_P - m_TextBegin) < m_TextSize - 1 && *m_P != 0 )
	{
		ParseCurrentNode();
		if( skipComment && m_CurrentNodeType == nNodeType_Comment )
		{
			return ReadNode( skipComment );
		}

		return TRUE;
	}

	return FALSE;
}


// Reads the current xml node
Void CXmlReader::ParseCurrentNode()
{
	Char* start = m_P;

	// more forward until '<' found
	while(*m_P != '<' && *m_P)
		++m_P;

	if (!*m_P)
		return;

	if (m_P - start > 0)
	{
		// we found some text, store it
		if (SetText(start, m_P))
			return;
	}

	++m_P;

	// based on current token, parse and report next element
	switch(*m_P)
	{
	case '/':
		ParseClosingXMLElement(); 
		break;
	case '?':
		IgnoreDefinition();	
		break;
	case '!':
		ParseComment();	
		break;
	default:
		ParseOpeningXMLElement();
		break;
	}
}

//! sets the state that text was found. Returns true if set should be set
Bool CXmlReader::SetText(Char* start, Char* end)
{
	// check if text is more than 2 characters, and if not, check if there is 
	// only white space, so that this text won't be reported
	if (end - start < 3)
	{
		Char* p = start;
		for(; p != end; ++p)
			if (!CharIsWhiteSpace(*p))
				break;

		if (p == end)
			return FALSE;
	}

	// set current text to the parsed text, and replace xml special characters
	m_NodeName.Buffer = start;
    m_NodeName.Length = (UInt32)(end - start);

	// current XML node type is text
	m_CurrentNodeType = nNodeType_Text;

	return true;
}

Void CXmlReader::ClearAttributesTable()
{
    m_AttributesCount = 0;
    m_AttributesTable.ClearAllItems();
}

Void CXmlReader::AddAttributes(CXmlReader::SAttribute& attr)
{
    if( m_AttributesCount+1 >= m_AttributesTable.GetItemCount() )
    {
		AttriuteTable tmp = m_AttributesTable;
        m_AttributesTable.SetItemCount( m_AttributesTable.GetItemCount() + XMLREADER_ATTRIBUTE_BUFFER_INC );
		for( UInt32 i=0;i<tmp.GetItemCount(); i++ )
		{
			m_AttributesTable[i] = tmp[i];
		}
    }

    m_AttributesTable[m_AttributesCount] = attr;

    m_AttributesCount++;
    
}

Void CXmlReader::ParseOpeningXMLElement()
{
	m_CurrentNodeType = nNodeType_Element;
	m_IsEmptyElement = false;
	ClearAttributesTable();

	// find name
	Char* startName = m_P;

	// find end of element
	while(*m_P != '>' && !CharIsWhiteSpace(*m_P))
		++m_P;

	Char* endName = m_P;

	// find Attributes
	while(*m_P != '>')
	{
		if (CharIsWhiteSpace(*m_P))
			++m_P;
		else
		{
			if (*m_P != '/')
			{
				// we've got an attribute

				// read the attribute names
				Char* attributeNameBegin = m_P;

				while(!CharIsWhiteSpace(*m_P) && *m_P != '=')
					++m_P;

				Char* attributeNameEnd = m_P;
				++m_P;

				// read the attribute value
				// check for quotes and single quotes, thx to murphy
				while( (*m_P != '\"') && (*m_P != '\'') && *m_P) 
					++m_P;

				if (!*m_P) // malformatted xml file
					return;

				Char attributeQuoteChar = *m_P;

				++m_P;
				Char* attributeValueBegin = m_P;
				
				while(*m_P != attributeQuoteChar && *m_P)
					++m_P;

				if (!*m_P) // malformatted xml file
					return;

				Char* attributeValueEnd = m_P;
				++m_P;

				SAttribute attr;
				attr.Name.Buffer = attributeNameBegin;
				attr.Name.Length = (UInt32)(attributeNameEnd - attributeNameBegin);
                DebugAssertMsg( attr.Name.Length < XMLREADER_ATTR_NAME_LENGTH, "Name too long" );
				
                attr.Value.Buffer = attributeValueBegin;
				attr.Value.Length = (UInt32)(attributeValueEnd - attributeValueBegin);

                AddAttributes(attr);
			}
			else
			{
				// tag is closed directly
				++m_P;
				m_IsEmptyElement = TRUE;
				break;
			}
		}
	}

	// check if this tag is closing directly
	if (endName > startName && *(endName-1) == '/')
	{
		// directly closing tag
		m_IsEmptyElement = TRUE;
		endName--;
	}
	
	m_NodeName.Buffer = startName;
    m_NodeName.Length = (UInt32)(endName - startName);

	++m_P;
}

Void CXmlReader::ParseClosingXMLElement()
{
	m_CurrentNodeType = nNodeType_ElementEnd;
	m_IsEmptyElement = false;
	ClearAttributesTable();

	++m_P;
	Char* beginClose = m_P;

	while(*m_P != '>')
		++m_P;

	m_NodeName.Buffer = beginClose ;
    m_NodeName.Length = (UInt32)(m_P - beginClose );
	++m_P;

	// Read next node
	ReadNode();
}

Void CXmlReader::ParseComment()
{
	m_CurrentNodeType = nNodeType_Comment;
	m_P += 1;

	Char* commentBegin = m_P;

	int count = 1;

	// move until end of comment reached
	while(count)
	{
		if (*m_P == '>')
			--count;
		else
		if (*m_P == '<')
			++count;

		++m_P;
	}

	m_P -= 3;
	m_NodeName.Buffer = commentBegin+2;
    m_NodeName.Length = (UInt32)(m_P - commentBegin-2);
	m_P += 3;
}

Void CXmlReader::IgnoreDefinition()
{
	m_CurrentNodeType = nNodeType_Unknown;

	// move until end marked with '>' reached
	while(*m_P != '>')
		++m_P;

	++m_P;
}

CXmlReader::SAttribute* CXmlReader::GetAttribute( String name ) const
{
    UInt32 i;
    Char buffer[XMLREADER_ATTR_NAME_LENGTH];

	for (i=0; i<m_AttributesCount; ++i) 
    {
        SAttribute& attr = m_AttributesTable[i];
        MemoryCopy( attr.Name.Buffer, buffer, attr.Name.Length );

		if (CharArrayCompare( buffer, attr.Name.Length, name, StringGetLength( name ) ) == 0 )
			return &attr;
    }
	return NULL;
}

CXmlReader::SAttribute* CXmlReader::GetAttribute( UInt32 idx ) const
{
    if ( idx >= m_AttributesTable.GetItemCount() )
        return NULL;

    return &m_AttributesTable[idx];
}

Bool CXmlReader::GetNodeName( Char* name, UInt32 length ) const
{
	UInt32 l = m_NodeName.Length < length-1 ? m_NodeName.Length : length-1;

	MemoryCopy( m_NodeName.Buffer, name, l );
	name[l] = 0;

	return m_NodeName.Length < length-1;
}

Bool CXmlReader::GetAttributeName( UInt32 idx, Char* name, UInt32 length ) const
{
    SAttribute& attr = m_AttributesTable[idx];
    UInt32 l = attr.Name.Length < length-1 ? attr.Name.Length : length-1;

    MemoryCopy( attr.Name.Buffer, name, l );
    name[l] = 0;

    return attr.Name.Length < length-1;
}

Bool CXmlReader::GetAttributeValue( UInt32 idx, Char* value, UInt32 length ) const
{
    SAttribute& attr = m_AttributesTable[idx];
    UInt32 l = attr.Value.Length < length-1 ? attr.Value.Length : length-1;

    MemoryCopy( attr.Value.Buffer, value, l );
    value[l] = 0;

    return attr.Value.Length < length-1;
}

CXmlReader::ENodeType CXmlReader::GetNodeType() const
{
	return m_CurrentNodeType;
}

UInt32 CXmlReader::GetAttributeCount() const
{
	return m_AttributesCount;
}

Int32 CXmlReader::GetAttributeValueAsInt( String name ) const
{
	return (Int32)GetAttributeValueAsFloat(name);
}

Int32 CXmlReader::GetAttributeValueAsInt( UInt32 idx ) const
{
	return (Int32)GetAttributeValueAsFloat( idx );
}

Float32 CXmlReader::GetAttributeValueAsFloat( String name ) const
{
    SAttribute* attr = GetAttribute(name);
    if (!attr)
        return 0.0f;

    return CharArrayToFloat32( attr->Value.Buffer, attr->Value.Length );
}

Float32 CXmlReader::GetAttributeValueAsFloat( UInt32 idx) const
{
    SAttribute* attr = GetAttribute(idx);
    if (!attr)
        return 0.0f;

    return CharArrayToFloat32( attr->Value.Buffer, attr->Value.Length );
}
