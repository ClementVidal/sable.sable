#ifndef _SABLE_CORE_COMMON_DATATYPES_
#define _SABLE_CORE_COMMON_DATATYPES_

#include <Sable/Setup.h>

#include <stddef.h>
#include <stdint.h>

/** \file Sable\Core\Common\DataTypes.h
Define standard data types*/

/** \addtogroup DataTypes
*  DataTypes
*/
//@{
#if defined( SETUP_IMPLTYPE_MSW )
typedef  __int64        			Int64;					/**< 64 Bits signed int*/
typedef  unsigned __int64        	UInt64;					/**< 64 Bits unsigned int*/
#else
typedef long long       			Int64;
typedef unsigned long long      	UInt64;
#endif


typedef  int            Int32;					/**< 32 Bits signed int*/
typedef  short          Int16;					/**< 16 Bits signed int*/
typedef  signed char    Int8;					/**< 8 Bits signed int*/

typedef unsigned int    UInt32;					/**< 32 Bits unsigned int*/
typedef unsigned short  UInt16;					/**< 16 Bits unsigned int*/
typedef unsigned char   UInt8;					/**< 8 Bits unsigned int*/

typedef UInt16			Float16;				/**< 16 Bits float*/
typedef	float			Float32;				/**< 32 Bits float*/
typedef	double			Float64;				/**< 64 Bits float*/
typedef char			Char;					/**< 8 Bits caracter*/
typedef void			Void;					/**< Untyped*/
typedef UInt32			Bool;					/**< Boolean*/

typedef UInt16			Handle;					/**< Handle*/
typedef unsigned char   Byte;					/**< Byte*/
typedef	UInt32			Index;					/**< Index*/
typedef	UInt32			Count;					/**< Count*/
typedef	UInt32          HashValue;				/**< Count*/

typedef const Char*     String;                 /**< 8 Bits ascii CONST String*/

#ifdef SETUP_UNICODE
	#ifdef  SETUP_WCHAR_DEFINED
		typedef const wchar_t*		WString;				/**< 16 Bits unicode CONST String*/
		typedef wchar_t			WChar;					/**< 16 Bits unicode character*/
	#else
		typedef const UInt16*		WString;				/**< 16 Bits unicode CONST String*/
		typedef UInt16			WChar;					/**< 16 Bits unicode character*/
	#endif
#else
	typedef char			WChar;					/**< 16 Bits unicode character*/
	typedef const char*		WString;				/**< 16 Bits unicode CONST String*/
#endif

#if defined( SETUP_IMPLTYPE_MSW )
    typedef intptr_t     Address;                /**< Must ALWAYS be of size of the adress bus ( or of the size of a pointer )*/
    typedef size_t      SysSize;
#else
    typedef intptr_t     	Address;                /**< Must ALWAYS be of size of the adress bus ( or of the size of a pointer )*/
    typedef size_t 		SysSize;
#endif 



#define INVALID_INDEX	( 0xffff )
#define INVALID_HANDLE ( 0xffff )				/**< Invalid handle value*/

#define INT8_MIN_VAL		(-128)					/**< Int8 minimum value*/
#define INT16_MIN_VAL		(-32768)				/**< Int16 minimum value*/
#define INT32_MIN_VAL		(-2147483647)			/**< Int32 minimum value*/
#define INT8_MAX_VAL		(127)					/**< Int8 maximum value*/
#define INT16_MAX_VAL		(32767)					/**< Int16 maximum value*/
#define INT32_MAX_VAL		(2147483647)			/**< Int32 maximum value*/
#define UINT8_MAX_VAL		(255)					/**< UInt8 maximum value*/
#define UINT16_MAX_VAL	(65535)					/**< UInt16 maximum value*/
#define UINT32_MAX_VAL	(4294967295U)			/**< UInt32 maximum value*/
#define FLOAT32_MAX_VAL	((Float32)(3.4E+38))	/**< Float32 maximum value*/
#define FLOAT32_MIN_VAL	((Float32)(-3.4E+38))	/**< Float32 mimimum value*/

#define FLOAT32NAN	(0x7FFFFFFF)                /**< Float32 not a number value*/
#define FLOAT32INF	(0x7F800000)                /**< Float32 positive infinite value*/
#define FLOAT32NINF	(0xFF800000)                /**< Float32 negative infinite value*/
#define FLOAT32IND	(0xFFC00000)                /**< Float32 undefined value*/


#ifndef TRUE					
    #define TRUE		(1)						/**< Boolean true value*/
#endif

#ifndef FALSE
    #define FALSE		(0)						/**< Boolean false value*/
#endif

#ifndef PI 
	#define PI	3.1415926535f					/**< PI.*/
#endif

#ifndef NULL
    #define NULL (0)							/**< NULL pointer*/
#endif

#define FLOAT32_ERROR_THRESHOLD	(0.000001f)			/**< Display ratio*/

#ifdef SETUP_UNICODE
    #define WT( text ) L##text 
#else
    #define WT( text ) text
#endif

enum EAccesMode
{
	nAccesMode_Read = 0,
	nAccesMode_Write, 
	nAccesMode_ReadWrite,
	nAccesMode_None
};

enum EAxis
{
    nAxis_X = 0,
    nAxis_Y,
    nAxis_Z,
    nAxis_Count,
    nAxis_None = -1
};

// TEMP: MOve to an other file
#define GetNullReference( type ) ( *( ( type* )( NULL ) ) )

#define IsNullReference( ref ) ( &(ref) == NULL )

//@}<




#endif

