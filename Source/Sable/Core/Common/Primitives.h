#ifndef _CORE_COMMON_PRIMITIVES_
#define _CORE_COMMON_PRIMITIVES_

#include <Sable\Core\Common\DataTypes.h>

/** 
@file Primitives.h
Basic math primitives
*/

namespace Sable
{

#define ForEachItem( iterator, collection ) \
	for( (collection).StartIteration( (iterator) ); (iterator).GetIsValid(); (iterator).Iterate() )\

#define MegaBytesToBytes( n ) ( (UInt32) (((Float32)n) * 1024.0f * 1024.0f ) )
#define KiloBytesToBytes( n ) ( (UInt32) (((Float32)n) * 1024.0f ) )

}

#endif