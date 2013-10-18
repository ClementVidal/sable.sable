#include <Sable/Physic/Common/Helper.h>

#include <Sable/Core/Common/Manager.h>
#include <Sable/Core/Math/Matrix4x4f.h>

#include <Sable/Physic/Shape/Header.h>

using namespace Sable;

//
// CPhysicHelper class
//


Void CPhysicHelper::CreateBoxRow( CPhysicWorld& world, const CVector3f& pos, const CVector3f& size, Int32 count )
{
	CVector3f posCurrent = pos;
	posCurrent.SetX( pos.GetX() - size.GetX() * ( count / 2 ));

	for( Int32 i = 0; i < count; i++ )
	{
		CreateBox( world, posCurrent, size, CVector3f( 0.0f, 1.0f, 0.0f ) );
		posCurrent.SetX( posCurrent.GetX() + size.GetX() );
	}
}

Void CPhysicHelper::CreateBoxWall( CPhysicWorld& world, const CVector3f& pos, const CVector3f& size, Int32 nbWidth, Int32 nbHeight )
{
	CVector3f posCurrent = pos;
	for( Int32 i = 0; i < nbHeight; i++ )
	{
		CVector3f vecDec = CVector3f( (float)(i%2)* size.GetX() / 2.f, 0.f, 0.f );
		CreateBoxRow( world, posCurrent + vecDec, size, nbWidth );
		posCurrent.SetY( posCurrent.GetY() + size.GetY()); 
	}
}

CPhysicActor* CPhysicHelper::CreateCapsule( CPhysicWorld& world, const CVector3f& pos, Float32 height, Float32 radius, Int32 group )
{
	CMatrix4x4f m;
	CPhysicActorDesc actorDesc;
	CPhysicShapeCapsule capsule;
	CPhysicBodyDesc rigidBody;
	CPhysicActor* actor;

	m.SetFromTranslation( pos );
	capsule.SetHeight( height );
	capsule.SetRadius( radius );
	capsule.NXShapeDesc.group = group;
	actorDesc.AddShape( capsule );
	actorDesc.SetWorldTransformation( m );
	actorDesc.SetRigidBody( rigidBody );

	actor = world.AddActor( actorDesc );
	return actor;
}

CPhysicActor* CPhysicHelper::CreateSphere( CPhysicWorld& world, const CMatrix4x4f& orientation, Bool isStatic, Float32 radius, Int32 group )
{
	CPhysicActorDesc actorDesc;
	CPhysicShapeSphere sphere;
	CPhysicBodyDesc rigidBody;
	CPhysicActor* actor;

	sphere.SetRadius( radius );
	sphere.NXShapeDesc.group = group;
	actorDesc.AddShape( sphere );
	actorDesc.SetWorldTransformation( orientation );
	actorDesc.SetDensity( 0.2f );

	if( !isStatic )
		actorDesc.SetRigidBody( rigidBody );

	actor = world.AddActor( actorDesc );

	actor->NXActor->setGroup( group );
	return actor;
}

CPhysicActor* CPhysicHelper::CreateBox( CPhysicWorld& world, const CVector3f& pos, const CVector3f& size, const CVector3f& axis, Bool isStatic, Float32 ang, Float32 density , Int32 group  )
{
	CMatrix4x4f m;
	CPhysicActorDesc actorDesc;
	CPhysicShapeBox box;
	CPhysicBodyDesc rigidBody;

	CPhysicActor *actor;

	m.SetFromTranslation( pos );
	box.SetSize( size / 2.f );
	box.NXShapeDesc.group = group;

	CMatrix4x4f mat;
	mat.SetFromAxisAndAngle( axis, ang );
	box.SetLocalMatrix( mat );

	actorDesc.AddShape( box );
	actorDesc.SetWorldTransformation( m );
	if( !isStatic )
		actorDesc.SetRigidBody( rigidBody );
	actorDesc.SetDensity( density );

	actor = world.AddActor( actorDesc );
	if( !isStatic )
		actor->NXActor->setSolverIterationCount( 10 );

	return actor;
}

NxVec3 CPhysicHelper::ConvertVector( const CVector3f& in )
{
    NxVec3 out;
    ConvertVector( in, out );
    return out;
}

Void CPhysicHelper::ConvertVector( const CVector3f& in, NxVec3& out )
{
    out.x = in.GetX();
    out.y = in.GetY();
    out.z = in.GetZ();
}

CVector3f CPhysicHelper::ConvertVector( const NxVec3& in )
{
    CVector3f out;
    out = CVector3f( in.x, in.y, in.z );

    return out;
}

NxMat34 CPhysicHelper::ConvertMatrix( const CMatrix4x4f& m )
{
    NxMat34 outM;

    outM.setColumnMajor44( m.m );
    outM.t.x = m._41;
    outM.t.y = m._42;
    outM.t.z = m._43;
    return outM;
}

Void CPhysicHelper::ConvertMatrix( const NxMat34& m, CMatrix4x4f& out )
{
	CVector3f t;
    out.SetFromIdentity();
    out.SetTranslationComponent( ConvertVector( m.t ) );
    out.SetXComponent( ConvertVector( m.M.getColumn( 0 ) ) );
    out.SetYComponent( ConvertVector( m.M.getColumn( 1 ) ) );
    out.SetZComponent( ConvertVector( m.M.getColumn( 2 ) )  );
}

NxRay CPhysicHelper::ConvertRay( const CRay& ray )
{
    NxRay r;

    r.orig = CPhysicHelper::ConvertVector( ray.Origin );
    r.dir = CPhysicHelper::ConvertVector( ray.Direction );
    r.dir.normalize();

    return r;
}

//
// CPhysicAllocator class
//

void * CPhysicAllocator::malloc(size_t size)
{
	return ::malloc(size);
}

void * CPhysicAllocator::mallocDEBUG(size_t size,const char *fileName, Int32 line)
{
	return ::_malloc_dbg(size,_NORMAL_BLOCK, fileName, line);
}

void * CPhysicAllocator::realloc(void * memory, size_t size)
{
	return ::realloc(memory,size);
}

void CPhysicAllocator::free(void * memory)
{
	::free(memory);
}

//
// CPhysicUSerOutputStream class
//

CPhysicUSerOutputStream::CPhysicUSerOutputStream()
{

}

CPhysicUSerOutputStream::~CPhysicUSerOutputStream ()
{

}

void CPhysicUSerOutputStream::reportError(NxErrorCode code, const char *message, const char *file, Int32 line)
{
	CoreManager.GetLog().LogError( (String) message );
}

NxAssertResponse CPhysicUSerOutputStream::reportAssertViolation (const char *message, const char *file, Int32 line)
{
	CoreManager.GetLog().LogError( (String) message );
	return NX_AR_BREAKPOINT ;
}

void  CPhysicUSerOutputStream::print(const char *message)
{
	CoreManager.GetLog().LogError( (String) message );
}

//
// CPhysicFileStream class
//

CPhysicFileStream::CPhysicFileStream(const char* filename, bool load) : 
	fp(NULL)
{
	fp = fopen(filename, load ? "rb" : "wb");
}

CPhysicFileStream::~CPhysicFileStream()
{
	if(fp)  
		fclose(fp);
}

NxU8 CPhysicFileStream::readByte() const
{
	NxU8 b;
	size_t r = fread(&b, sizeof(NxU8), 1, fp);
	NX_ASSERT(r);
	return b;
}

NxU16 CPhysicFileStream::readWord() const
{
	NxU16 b;
	size_t r = fread(&b, sizeof(NxU16), 1, fp);
	NX_ASSERT(r);
	return b;
}

NxU32 CPhysicFileStream::readDword() const
{
	NxU32 b;
	size_t r = fread(&b, sizeof(NxU32), 1, fp);
	NX_ASSERT(r);
	return b;
}

float CPhysicFileStream::readFloat() const
{
	float b;
	size_t r = fread(&b, sizeof(float), 1, fp);
	NX_ASSERT(r);
	return b;
}

double CPhysicFileStream::readDouble() const
{
	double b;
	size_t r = fread(&b, sizeof(double), 1, fp);
	NX_ASSERT(r);
	return b;
}

void CPhysicFileStream::readBuffer(void* buffer, NxU32 size)   const
{
	size_t w = fread(buffer, size, 1, fp);
	NX_ASSERT(w);
}

NxStream& CPhysicFileStream::storeByte(NxU8 b)
{
	size_t w = fwrite(&b, sizeof(NxU8), 1, fp);
	NX_ASSERT(w);
	return *this;
}

NxStream& CPhysicFileStream::storeWord(NxU16 w)
{
	size_t ww = fwrite(&w, sizeof(NxU16), 1, fp);
	NX_ASSERT(ww);
	return *this;
}

NxStream& CPhysicFileStream::storeDword(NxU32 w)
{
	size_t ww = fwrite(&w, sizeof(NxU32), 1, fp);
	NX_ASSERT(ww);
	return *this;
}

NxStream& CPhysicFileStream::storeFloat(NxReal w)
{
	size_t ww = fwrite(&w, sizeof(NxReal), 1, fp);
	NX_ASSERT(ww);
	return *this;
}

NxStream& CPhysicFileStream::storeDouble(NxF64 w)
{
	size_t ww = fwrite(&w, sizeof(NxF64), 1, fp);
	NX_ASSERT(ww);
	return *this;
}

NxStream& CPhysicFileStream::storeBuffer(const void* buffer, NxU32 size)
{
	size_t w = fwrite(buffer, size, 1, fp);
	NX_ASSERT(w);
	return *this;
}

NxShapesType CPhysicHelper::ConvertActorType( EPhysicActorType t )
{
	if( t == nPhysicActorType_Dynamic )
		return NX_DYNAMIC_SHAPES;

	if( t == nPhysicActorType_Static )
		return NX_STATIC_SHAPES;

	return NX_ALL_SHAPES;
}