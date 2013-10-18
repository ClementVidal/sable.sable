#ifndef _SABLE_PHYSIC_COMMON_HELPER_
#define _SABLE_PHYSIC_COMMON_HELPER_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Core/Geometry/Ray.h>
#include <Sable/Physic/Common/DataTypes.h>

#include <nxvec3.h>
#include <nxmat34.h>
#include <NxRay.h> 
#include <NxUserAllocator.h> 
#include <NxUserOutputStream.h> 
#include <NxUserRaycastReport.h> 
#include <NxStream.h> 
#include <crtdbg.h> 
#include <stdio.h>

namespace Sable
{

class CPhysicActor;
class CPhysicWorld;

/** 
Helper class for Physics package
*/
class CPhysicHelper 
{

public:
	
	/** @name Methos*/
	//@{
	static NxShapesType ConvertActorType( EPhysicActorType t );
    static NxRay    ConvertRay( const CRay& ray );
    static NxVec3   ConvertVector( const CVector3f& in );
    static CVector3f ConvertVector( const NxVec3& in );
    static Void     ConvertVector( const CVector3f& in, NxVec3& out );
    static NxMat34  ConvertMatrix( const CMatrix4x4f& m );
    static Void     ConvertMatrix( const NxMat34& m, CMatrix4x4f& out );

	static CPhysicActor*	CreateBox( CPhysicWorld& world, const CVector3f& pos, const CVector3f& size, const CVector3f& axis, Bool isStatic = FALSE, Float32 ang = 0.0f, Float32 density = 1.0f , Int32 group = 0 );
	static CPhysicActor*	CreateSphere( CPhysicWorld& world, const CMatrix4x4f& orientation, Bool isStatic = FALSE, Float32 radius = 1.0f, Int32 group = 0 );
	static CPhysicActor*	CreateCapsule( CPhysicWorld& world, const CVector3f& pos, Float32 height = 2.0f, Float32 radius = 1.0f, Int32 group = 0 );
	static Void CreateBoxRow( CPhysicWorld& world, const CVector3f& pos, const CVector3f& size, Int32 count );
	static Void CreateBoxWall( CPhysicWorld& world, const CVector3f& pos, const CVector3f& size, Int32 nbWidth, Int32 nbHeight );
	//@}

};

/** 
Custom implementation of physx memory allocator
*/
class CPhysicAllocator : public NxUserAllocator
{
public:

	void * malloc(size_t size);
	void * mallocDEBUG(size_t size,const char *fileName, int line);
	void * realloc(void * memory, size_t size);
	void free(void * memory);

};

/** 
Custom implementation of physx output stream
*/
class CPhysicUSerOutputStream : public NxUserOutputStream 
{

public:

	CPhysicUSerOutputStream();
	virtual  ~CPhysicUSerOutputStream ();

	void  reportError(NxErrorCode code, const char *message, const char *file, int line);
	NxAssertResponse  reportAssertViolation (const char *message, const char *file, int line);
	void  print (const char *message);
};

/** 
Custom implementation of physx file streams
*/
class CPhysicFileStream : public NxStream
{
public:
	CPhysicFileStream(const char* filename, bool load);
	virtual ~CPhysicFileStream();

	virtual     NxU8            readByte()                              const;
	virtual     NxU16           readWord()                              const;
	virtual     NxU32           readDword()                             const;
	virtual     float           readFloat()                             const;
	virtual     double          readDouble()                            const;
	virtual     void            readBuffer(void* buffer, NxU32 size)    const;

	virtual     NxStream&       storeByte(NxU8 b);
	virtual     NxStream&       storeWord(NxU16 w);
	virtual     NxStream&       storeDword(NxU32 d);
	virtual     NxStream&       storeFloat(NxReal f);
	virtual     NxStream&       storeDouble(NxF64 f);
	virtual     NxStream&       storeBuffer(const void* buffer, NxU32 size);

	FILE*           fp;
};


}

#endif