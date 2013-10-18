#ifndef _CORE_MATH_TUPLE_
#define _CORE_MATH_TUPLE_

#include <Sable/Core/Common/DataTypes.h>

namespace Sable
{

/** 
\ingroup CoreMath
Integer Tuple 2. 
*/
struct STuple2i
{
	Int32	x;
	Int32	y;
};

/** 
\ingroup CoreMath
Tuple 2. 
*/
struct STuple2f
{
	Float32	x;
	Float32	y;
};

/** 
\ingroup CoreMath
Tuple 3. 
*/
struct STuple3f
{
	Float32	x;
	Float32	y;
	Float32	z;
};

/** 
\ingroup CoreMath
Tuple 4. 
*/
struct STuple4f
{
	Float32	x;
	Float32	y;
	Float32	z;
	Float32	w;
};

/** 
\ingroup CoreMath
Tuple 16. 
\note The name of members _11, _12, _13 .... 
identify an element at the following position: _RC where R is the row number and C the column number.
\note The memory layout of this matrix is suited for Row major manipulation
*/
struct STuple16f
{
    union 
    {
        struct 
        {
            Float32        _11, _12, _13, _14;
            Float32        _21, _22, _23, _24;
            Float32        _31, _32, _33, _34;
            Float32        _41, _42, _43, _44;
        };
        Float32 m[4][4];
    };
};

/** 
\ingroup CoreMath
Tuple 9. 
\note The name of members _11, _12, _13 .... 
identify an element at the following position: _RC where R is the row number and C the column number.
\note The memory layout of this matrix is suited for Row major manipulation
*/
struct STuple9f
{
    union 
    {
        struct 
        {
            Float32        _11, _12, _13;
            Float32        _21, _22, _23;
            Float32        _31, _32, _33;
        };
        Float32 m[3][3];
    };
};

}

#endif


