#ifndef _SABLE_PHYSIC_COMMON_DATATYPES_
#define _SABLE_PHYSIC_COMMON_DATATYPES_

/** \file Sable\Physic\Common\DataTypes.h
Physic data types*/

namespace Sable
{

/**
Enum used to represent axis
*/
enum EPhysicAxis
{
    nPhysicAxis_X = 1 << 0,
    nPhysicAxis_Y = 1 << 1,
    nPhysicAxis_Z = 1 << 2,
};

/**
Enum used when doing raycast query over the scene to identify which kind of actors
are taken into accoutn during the query
*/
enum EPhysicActorType
{
    nPhysicActorType_Dynamic,
    nPhysicActorType_Static,
    nPhysicActorType_All
};

}


#endif