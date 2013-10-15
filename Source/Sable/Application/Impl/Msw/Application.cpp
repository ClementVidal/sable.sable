#include <Sable\Application\Impl\Msw\Application.h>

#include <locale.h>

using namespace Sable;

CImplMswApplication::CImplMswApplication() :
    CImplStubApplication()
{
}

CImplMswApplication::~CImplMswApplication()
{
}


Void CImplMswApplication::Initialize( CApplication& app )
{
	// Set locale for the application 
	//( this only affect the decimal-point character in formatted input/output operations and string formatting functions )
	setlocale(LC_NUMERIC,"C");
}
