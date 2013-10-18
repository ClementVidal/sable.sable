#include <Sable/Gui/Layout/HBox.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1( Sable, CLayoutHBox, CLayout );

CLayoutHBox::CLayoutHBox( ) :
	CLayout( )
{
}

CLayoutHBox::~CLayoutHBox()
{
}

Void CLayoutHBox::Apply( const CVector2i& pos, const CVector2i& size )
{
	if( GetChildCount() == 0 )
		return;

	CLayoutItem* child = GetChild();
	// Compute he amout of stretch "slot" used by all the child
	CVector2i totalStretchFactor;
	while( child )
	{
		totalStretchFactor = totalStretchFactor + child->GetStretchFactor();
		child = child->GetSibling();
	}

	// Special case whensize of widget is null
	if( totalStretchFactor.GetX() == 0 || size.GetX() == 0 || size.GetY() == 0 )
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
	Int32 step = size.GetX() / totalStretchFactor.GetX();
	int pixelLeft = 0;
	if( step * totalStretchFactor.GetX() )
		pixelLeft = size.GetX() % ( step * totalStretchFactor.GetX() );

	CVector2i childPos = pos;

	// Assign size and pos to each child
	child = GetChild();
	while( child )
	{
		CVector2i childSize( step * child->GetStretchFactor().GetX(), size.GetY()  );
		if( !child->GetSibling() )
			childSize = childSize + CVector2i( pixelLeft, 0 );

		child->SetPositionAndSize( childPos, childSize );

		childPos = childPos + CVector2i( step * child->GetStretchFactor().GetX(), 0 );

		child = child->GetSibling();
	}
}


