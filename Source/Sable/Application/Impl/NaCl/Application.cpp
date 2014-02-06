#include <Sable/Application/Impl/NaCl/Application.h>

#include <locale.h>

using namespace Sable;

CImplNaClApplication::CImplNaClApplication() :
    CImplStubApplication()
{
}

CImplNaClApplication::~CImplNaClApplication()
{
}


Void CImplNaClApplication::Initialize( CApplication& app )
{
	// Set locale for the application 
	//( this only affect the decimal-point character in formatted input/output operations and string formatting functions )
	setlocale(LC_NUMERIC,"C");
}
