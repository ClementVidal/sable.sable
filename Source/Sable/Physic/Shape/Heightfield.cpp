#include <Sable\Physic\Shape\Heightfield.h>

#include <Sable\Physic\Common\Manager.h>

#include "NxHeightField.h"
#include "NxHeightFieldDesc.h"
#include "NxHeightFieldShapeDesc.h"

using namespace Sable;

CPhysicShapeHeightfield::CPhysicShapeHeightfield( const CVector3f& size, UInt32 nbColumns, UInt32 nbRows, UInt16* buffer )
{
    NXCreate( size, nbColumns, nbRows, buffer );
}

CPhysicShapeHeightfield::~CPhysicShapeHeightfield()
{
}

NxShapeDesc& CPhysicShapeHeightfield::GetNxShapeDesc() 
{
    return NXShapeDesc;
}

Void CPhysicShapeHeightfield::NXCreate( const CVector3f& size, UInt32 nbColumns, UInt32 nbRows, UInt16* buffer )
{
    CArrayUInt32 sampleTable;

    NxHeightFieldDesc heightFieldDesc;
    heightFieldDesc.nbColumns		= nbColumns;
    heightFieldDesc.nbRows			= nbRows;
    heightFieldDesc.convexEdgeThreshold = 0;

    // allocate storage for samples
    sampleTable.SetItemCount( nbColumns*nbRows );
    heightFieldDesc.samples			= sampleTable.GetBuffer();
    heightFieldDesc.sampleStride	= sizeof(UInt32);

    // Fill samples
    NxHeightFieldSample* currentSample;
    UInt32 x,y;
    Byte* currentByte = (Byte*)heightFieldDesc.samples;
    for ( y = 0; y < nbRows; y++)
    {
        for ( x= 0; x < nbColumns; x++)
        {
            currentSample = (NxHeightFieldSample*)&currentByte[ ( y* nbColumns + x ) * heightFieldDesc.sampleStride ];

            if( buffer )
                currentSample->height = buffer[ y*nbColumns + x ];
            else
                currentSample->height = 0;

            // Cross pattern
            //currentSample->tessFlag = x&1 ? ( y & 1 ) : !( y & 1 );

            // regular patern
            currentSample->tessFlag = 0;

            currentSample->materialIndex0 = 1;
            currentSample->materialIndex1 = 1;

            //currentByte += heightFieldDesc.sampleStride;
        }
    }

    NxHeightField* heightField = PhysicManager.NXSdk->createHeightField(heightFieldDesc);

    NXShapeDesc.heightField	= heightField;
    NXShapeDesc.shapeFlags		= NX_SF_FEATURE_INDICES | NX_SF_VISUALIZATION;
    NXShapeDesc.heightScale	= size.GetY();
    NXShapeDesc.rowScale		= size.GetX() / NxReal(nbRows-1);
    NXShapeDesc.columnScale	= size.GetZ() / NxReal(nbColumns-1);
    NXShapeDesc.materialIndexHighBits = 0;
    NXShapeDesc.holeMaterial = 2;


}

