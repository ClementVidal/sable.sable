#include <Sable/Gui/Layout/VBox.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1( Sable, CLayoutVBox, CLayout );

CLayoutVBox::CLayoutVBox():
	CLayout()
{
}


CLayoutVBox::~CLayoutVBox()
{
}

Void CLayoutVBox::Apply( const CVector2i& pos, const CVector2i& size )
{
	if( GetChildCount() == 0 )
		return;

	CLayoutItem* child = GetChild();
	// Compute the amout of stretch "slot" used by all the child
	CVector2i totalStretchFactor;
	while( child )
	{
		if( child->GetVSizePolicy() == nSizePolicy_Stretchable )
			totalStretchFactor = totalStretchFactor + child->GetStretchFactor();

		child = child->GetSibling();
	}

	// Compute the amout of pixel space used by all fixedSize item
	child = GetChild();
	CVector2i totalUsedFixedSize;
	while( child )
	{
		if( child->GetVSizePolicy() == nSizePolicy_Fixed )
			totalUsedFixedSize = totalUsedFixedSize + child->GetSize();

		child = child->GetSibling();
	}

	// Special case when size of widget is null
	if( totalStretchFactor.GetY() == 0 || size.GetX() == 0 || size.GetY() == 0 )
	{
		child = GetChild();
		while( child )
		{
			child->SetPositionAndSize( pos, CVector2i(0,0) );
			child = child->GetSibling();
		}
		return;
	}

	// Compute the "step size"
	Int32 pixelUsedForStretchableArea = size.GetY()-totalUsedFixedSize.GetY();
	Int32 step = pixelUsedForStretchableArea / totalStretchFactor.GetY();
	int pixelLeft = 0;
	if( step * totalStretchFactor.GetY() )
		pixelLeft = pixelUsedForStretchableArea % ( step * totalStretchFactor.GetY() );

	CVector2i childPos = pos;

	// Assign size and pos to each child
	child = GetChild();
	while( child )
	{
		CVector2i stretchedSize( size.GetX(), step * child->GetStretchFactor().GetY() );
		CVector2i fixedSize = child->GetSize();
		CVector2i childSize;

		if( child->GetHSizePolicy() == nSizePolicy_Stretchable )
		{
			childSize.SetX( stretchedSize.GetX() );
		}
		else if( child->GetHSizePolicy() == nSizePolicy_Fixed )
		{
			childSize.SetX( fixedSize.GetX() );
		}

		if( child->GetVSizePolicy() == nSizePolicy_Stretchable )
		{
			childSize.SetY( stretchedSize.GetY() );
		}
		else if( child->GetVSizePolicy() == nSizePolicy_Fixed )
		{
			childSize.SetY( fixedSize.GetY() );
		}

		// Add remaining size to the last item
		if( !child->GetSibling() )
			childSize = childSize + CVector2i( 0, pixelLeft );

		child->SetPositionAndSize( childPos, childSize );

        childPos = childPos + CVector2i( 0, childSize.GetY() );
	
		child = child->GetSibling();
	}
}
