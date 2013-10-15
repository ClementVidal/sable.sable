#include <Sable\Core\Debug\Primitives.h>

#include <Sable\Core\File\FilePath.h>

using namespace Sable;

Void Sable::DebugLogInfo( String format, ... )
{
    va_list args;
    va_start( args, format );
    CoreManager.GetLog().Log( CLogger::nLevel_Info, format, args );
    va_end( args );
}

Void Sable::DebugLogWarning( String format, ... )
{
	va_list args;
	va_start( args, format );
	CoreManager.GetLog().Log( CLogger::nLevel_Warning, format, args );
	va_end( args );
}

Void Sable::DebugLogError( String format, ... )
{
	va_list args;
	va_start( args, format );
	DebugCreateDump( );
	CoreManager.GetLog().Log( CLogger::nLevel_Error, format, args );
	va_end( args );
}

Void Sable::DebugLogCodeInformation( String file, UInt32 line, String func )
{
    CoreManager.GetLog().LogInfo( "%s()\n%s:%d", func, file, line );
}

Void Sable::DebugRaiseException()
{
#if defined( SETUP_IMPLTYPE_MSW )
#ifdef SETUP_USE_EXCEPTION
    RaiseException( 0, EXCEPTION_NONCONTINUABLE, 0, NULL );
#endif
#else

    assert( FALSE );

#endif


}

Void Sable::DebugBreakExecution()
{

#if defined( SETUP_IMPLTYPE_MSW )
    { 
        __debugbreak(); //__asm { Int32 3 } 
    }
#endif

}

String Sable::DebugGetDumpDirectory()
{
#if defined( SETUP_IMPLTYPE_MSW )

	WChar   wBuffer[512];
	Char    buffer[512];
	static Char    finalBuffer[512];

	::GetModuleFileName( NULL, wBuffer, 512 );
	WStringToString( wBuffer, buffer, 512 );

	Int32 p;
	p = StringReverseFind( buffer, '\\' );
	if( p == -1 )
		p = StringReverseFind( buffer, '/' );

	DebugAssert( p != -1 );

	StringCopySubPart( buffer, 0, p, finalBuffer, 512 );
	StringAppend( finalBuffer, "/CrashDump/", finalBuffer, 512 );

	return finalBuffer;

#else
	return "./CrashDump/";
#endif

}

Void Sable::DebugCreateDump( Void* dumpData ) 
{
  // Open the file 
#if defined( SETUP_IMPLTYPE_MSW )
	WChar buffer1[512];
	WChar buffer3[512];
    SYSTEMTIME time;
    GetLocalTime( &time );

    StringToWString( DebugGetDumpDirectory(), buffer1, 256 );
    CreateDirectory( buffer1, NULL );

#ifdef SETUP_CONFIG_RELEASE
    StringSetFormattedText( buffer3, 256, WT("%sRelease__%d_%d_%d__%d_%d.dmp"), buffer1,
        time.wDay, time.wMonth, time.wYear, time.wHour, time.wMinute );
#elif SETUP_CONFIG_DEBUG
	StringSetFormattedText( buffer3, 256, WT("%sDebug__%d_%d_%d__%d_%d.dmp"), buffer1,
		time.wDay, time.wMonth, time.wYear, time.wHour, time.wMinute );
#else
	StringSetFormattedText( buffer3, 256, WT("%sUnknown__%d_%d_%d__%d_%d.dmp"), buffer1,
		time.wDay, time.wMonth, time.wYear, time.wHour, time.wMinute );
#endif

    HANDLE hFile = CreateFile( buffer3, GENERIC_READ | GENERIC_WRITE, 
        0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL ); 

    if( ( hFile != NULL ) && ( hFile != INVALID_HANDLE_VALUE ) ) 
    {
        // Create the minidump 
        MINIDUMP_EXCEPTION_INFORMATION mdei; 

        mdei.ThreadId           = GetCurrentThreadId(); 
        mdei.ExceptionPointers  = (EXCEPTION_POINTERS*) dumpData; 
        mdei.ClientPointers     = FALSE; 

        MINIDUMP_TYPE mdt       = MiniDumpWithDataSegs; 

		BOOL rv = MiniDumpWriteDump( GetCurrentProcess(), GetCurrentProcessId(), hFile, mdt, (dumpData != NULL) ? &mdei: NULL, 0, 0 ); 

        if( !rv ) 
            CoreManager.GetLog().LogError( "Sable::DebugCreateDump - MiniDumpWriteDump failed. Error: %u ", GetLastError() );
		else
			CoreManager.GetLog().LogError( "Sable::DebugCreateDump - Dump created " );

        CloseHandle( hFile ); 

    }
    else 
    {
        CoreManager.GetLog().LogError( "Sable::DebugCreateDump - CreateFile failed. Error: %u ", GetLastError() );
    }
#endif
}
