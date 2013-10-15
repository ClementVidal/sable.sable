#ifndef _SABLE_CORE_BUILDFILEHEADER_
#define _SABLE_CORE_BUILDFILEHEADER_

#include <Sable\Setup.h>

#include <Sable\Core\Debug\Primitives.h>

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <wchar.h>
#include <string.h>
#include <assert.h>

#ifdef SETUP_IMPLTYPE_ANDROID

#include <Android\Log.h>

#endif

#ifdef SETUP_IMPLTYPE_MSW

#include <vadefs.h>
#include <windows.h>
#include <Dbghelp.h>

#endif

#endif
