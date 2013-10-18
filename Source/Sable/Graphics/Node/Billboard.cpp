#include <Sable/Graphics/Node/Billboard.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1( Sable, CNodeBillboard, CNodeRender )

CNodeBillboard::CNodeBillboard( )
{
}

CNodeBillboard::CNodeBillboard( CNode& parent ) :
	CNodeRender( parent )
{
}

CNodeBillboard::~CNodeBillboard( )
{

}

Bool CNodeBillboard::Update()
{
	DebugError("Need to be updated");
	/*CMatrix3x3f r;
	r.SetFromLookAt( GetWorldPosition(), renderer.GetCurrentCamera()->GetWorldPosition(), CVector3f::YAxis );

	GetLocalMatrix().SetRotationComponent( r );*/

	return CNodeRender::Update( );
}