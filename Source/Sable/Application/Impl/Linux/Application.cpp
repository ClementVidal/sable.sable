#include <Sable/Application/Impl/Linux/Application.h>

#include <locale.h>

using namespace Sable;

CImplLinuxApplication::CImplLinuxApplication() :
    CImplStubApplication()
{
}

CImplLinuxApplication::~CImplLinuxApplication()
{
}


Void CImplLinuxApplication::Initialize( CApplication& app )
{
	// Set locale for the application 
	//( this only affect the decimal-point character in formatted input/output operations and string formatting functions )
	setlocale(LC_NUMERIC,"C");
}
