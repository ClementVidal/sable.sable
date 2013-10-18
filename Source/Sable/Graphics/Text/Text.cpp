#include <Sable/Graphics/Text/Text.h>

#include <Sable/Graphics/Text/Font.h>

IMPLEMENT_MANAGED_CLASS1_ALLOC( Sable, CText, CManagedObject );

CText::CText( const CTextFont& font, UInt32 capacity )
{
    m_Size = CVector2i( 0, 0 );
    m_FontSize = 1.0f;
    m_Font = (CTextFont*) &font;
    m_Color = CColor::White;
	m_Capacity = 0;
	SetCapacity( capacity );
    m_Text[0] = 0;
	m_TextLength = 0;
	m_CtrlCharCount = 0;
	m_State.SetBit( nState_RecreateBuffer );
}

CText::CText( )
{
	m_Size = CVector2i( 0, 0 );
	m_FontSize = 1.0f;
	m_Color = CColor::White;
	m_Capacity = 0;
	SetCapacity( 128 );
	m_Text[0] = 0;
	m_TextLength = 0;
	m_CtrlCharCount = 0;
	m_State.SetBit( nState_RecreateBuffer );

	m_Font = &GraphicsManager.GetDefaultFont();
}

CText::~CText()
{

}

Void CText::SetCapacity( UInt32 c )
{
	if( m_Capacity != c )
	{
		m_Capacity = c;
		m_Text.SetItemCount( m_Capacity );
		if( m_TextLength <= m_Capacity && m_Capacity > 0 )
		{
			m_Text[m_Capacity-1] = 0;
		}
		m_State.SetBit( nState_RecreateBuffer );
	}
}

Void CText::SetFontSize( Float32 size )
{
    m_FontSize = size;
	ProcessText();
}

Void CText::SetColor( const CColor& color )
{
    m_Color = color;
}

Void CText::SetPosition( const CVector2f& pos )
{
    m_Position.SetX( pos.GetX() );
    m_Position.SetY( pos.GetY() );
}

Void CText::SetPosition( const CVector3f& pos )
{
    m_Position = pos;
}

CVector2f CText::Get2DPosition() const
{
    CVector2f v( m_Position.GetX(), m_Position.GetY() );
    return v;
}

CVector3f CText::Get3DPosition() const
{
    return m_Position;
}

const CVector3f& CText::GetPosition() const
{
    return m_Position;
}


Void CText::CreateBuffer( )
{
	m_VertexBuffer.UnLoad();

	m_VertexLayout.AddElement( nVertexComponent_Position, nVertexComponentType_Float2 );
	m_VertexLayout.AddElement( nVertexComponent_TexCoord0, nVertexComponentType_Float2 );
	m_VertexLayout.Initialize();

	m_VertexBuffer.SetRawData( m_Capacity * 6, sizeof( SVertex ) );
	m_VertexBuffer.SetAttribute( CGeometryVertexBuffer::nFlag_Dynamic );

    m_VertexBuffer.Load( );

	m_State.ClearBit( nState_RecreateBuffer );
}

Void CText::UpdateBuffer( const UInt32 offset, const UInt32 count )
{
	if( m_State.GetBit( nState_UpdateBuffer ) == FALSE || m_Font == NULL )
		return;

	if( m_State.GetBit( nState_RecreateBuffer ) )
	{
		CreateBuffer();
	}
	
    UInt32 index, i;
    Int32 x = 0, y=0;
    Float32 textureWidth = (Float32)m_Font->GetTextureWidth();
    Float32 textureHeight = (Float32)m_Font->GetTextureHeight();

    SVertex* buffer = (SVertex*)m_VertexBuffer.Lock(0 * 6, 0 *6);

    x= 0;
	i = 0;
	m_CtrlCharCount = 0;
	CRect2Di globalBBox( CVector2i::Zero, CVector2i::Zero );
    for(index = 0; index<count; index++)
    {
        const CTextFont::SChar &c = m_Font->GetChar(m_Text[index]);

		if( m_Text[index] == '\n' )
		{
			x = 0;
			y -= m_Font->GetLineSpacing();
			m_CtrlCharCount ++;
		}
		else
		{
			Float32 s = m_FontSize;

			// If we are not on the first char, re adjust x so that it start not at the beginning of it's bounding rect,
			// but at the beginning of it's glyph pos
			if( x > 0 )
				x -= c.OffsetX;

			buffer[i*6 + 0].Position = CVector2f( (Float32)x,					(Float32)y-c.OffsetY );
			buffer[i*6 + 1].Position = CVector2f( (Float32)x+c.BoundWidth*s,	(Float32)y-c.OffsetY );
			buffer[i*6 + 2].Position = CVector2f( (Float32)x,					(Float32)y-c.OffsetY-c.BoundHeight*s );
			buffer[i*6 + 5].Position = CVector2f( (Float32)x+c.BoundWidth*s,	(Float32)y-c.OffsetY-c.BoundHeight*s );

			buffer[i*6 + 0].TexCoord0 = CVector2f( (Float32)c.BoundX,					(Float32)c.BoundY);
			buffer[i*6 + 1].TexCoord0 = CVector2f( (Float32)c.BoundX + c.BoundWidth,	(Float32)c.BoundY);
			buffer[i*6 + 2].TexCoord0 = CVector2f( (Float32)c.BoundX,					(Float32)c.BoundY + c.BoundHeight);
			buffer[i*6 + 5].TexCoord0 = CVector2f( (Float32)c.BoundX + c.BoundWidth,	(Float32)c.BoundY + c.BoundHeight);

			buffer[i*6 + 3] = buffer[i*6 + 2];
			buffer[i*6 + 4] = buffer[i*6 + 1];

			Int32 width = (Int32)((c.CharWidth+c.OffsetX)*s);
			Int32 height = (Int32)(c.OffsetY+c.BoundHeight*s);

			globalBBox.Add( CRect2Di( x, y, c.BoundWidth*s, c.BoundHeight*s ) );
			x += width;
			i++;
		}
    }

    m_Size = globalBBox.GetSize();

    m_VertexBuffer.UnLock();

	m_State.ClearBit( nState_UpdateBuffer );
}

/**
Return the size in pixel of the bounding box of the current text
*/
const CVector2i& CText::GetSize() const
{
    return m_Size;
}

Void CText::SetFont( const CTextFont& font )
{
	m_Font = & font;
	ProcessText();
}

const CGeometryVertexBuffer& CText::GetVertexBuffer() const
{
	return m_VertexBuffer;
}

CTextFont& CText::GetFont() const
{
	return *m_Font;
}

Void CText::UpdateBuffer( )
{
	UpdateBuffer( 0, MathMin( m_Capacity, m_TextLength ) );
}

Void CText::Render(CRenderer& renderer)
{
	Int32 length = m_TextLength - m_CtrlCharCount;
	Float32 x, y;
	CVector2f reso = renderer.GetCurrentViewport()->GetSize();

    if( length <= 0 || m_Font == NULL  )
        return ;

	CShader& shader = m_Font->GetShader();


    if(length <= m_Capacity)
    {
		UpdateBuffer( 0, length);

		renderer.Activate( m_VertexBuffer, 0 );
		renderer.Activate( m_VertexLayout );

        x = (Float32) ( GetPosition().GetX() );
        y = (Float32) ( 1.0f - GetPosition().GetY() );

        CVector3f snapedPos( (Float32)x, (Float32)y , 0.0f );

        shader.GetParameter("Position")->SetValue( snapedPos );
        shader.GetParameter("Resolution")->SetValue( reso );
        shader.GetParameter("InputTexture")->SetValue( m_Font->GetTexture() );

        CVector2f textureSize( (Float32)m_Font->GetTextureWidth(), (Float32)m_Font->GetTextureHeight() );
        shader.GetParameter("Color")->SetValue( m_Color );

        renderer.Activate( shader );

		renderer.Draw( nPrimitiveType_TriangleList, length * 6, 0 );

    }
    else
    {
        Int32 offset = 0;
        Int32 count = m_Capacity;

        while(offset < length)
        {
            UpdateBuffer( offset, count);
            offset += count;

            count = length - offset;
            if(count > m_Capacity)
                count = m_Capacity;
        }
    }

}

Void CText::ProcessText()
{
	Int32 l = StringGetLength( m_Text.GetBuffer() );
	if( l <= m_Capacity)
	{
		m_TextLength = l;
		m_State.SetBit( nState_UpdateBuffer );
	}
}

Void CText::SetText( String string )
{
	if( StringCompare( string, m_Text.GetBuffer() ) == 0 )
		return;

	StringCopy( string, m_Text.GetBuffer(), m_Capacity );
	ProcessText();
}

Void CText::WriteFormattedText( String format, ... )
{
    va_list args;
    va_start( args, format );

    StringSetFormattedTextVaList( m_Text.GetBuffer(), m_Text.GetItemCount(), format, args ); 

	ProcessText();

    va_end( args );
}

Bool CText::Serialize( CPersistentArchive& ar )
{
	Int16 version = 0;

	if( ar.BeginScope( WT("Text"), version ) == 0 )
	{
		ar.Serialize( m_Font, WT("Font") );
		ar.Serialize( m_Capacity, WT("Capacity") );

		ar.Serialize( m_Color, WT("Color") );
		ar.Serialize( m_Position, WT("Position") );
		ar.Serialize( m_FontSize, WT("FontSize") );
		ar.Serialize( m_TextLength, WT("TextLen") );

		if( ar.IsLoading() )
		{
			SetCapacity( m_Capacity );
			m_State.SetBit( nState_UpdateBuffer );
			m_State.SetBit( nState_RecreateBuffer );
		}

		ar.Serialize( m_Text.GetBuffer(), m_Capacity, WT("Text") );

		ar.EndScope();
	}
	return CManagedObject::Serialize( ar );
}