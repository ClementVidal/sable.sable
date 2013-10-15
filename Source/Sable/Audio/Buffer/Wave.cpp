#include <Sable\Audio\Buffer\Wave.h>

#include <Sable\Core\Persistent\Archive.h>
#include <Sable\Core\File\File.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1_ALLOC( Sable, CAudioBufferWave, CAudioBuffer )

CAudioBufferWave::CAudioBufferWave( ) :
	CAudioBuffer( )
{
}


CAudioBufferWave::CAudioBufferWave( const CFilePath& m_FilePath ) :
	CAudioBuffer( )
{
	SetFilePath( m_FilePath );
	Initialize( );
}

CAudioBufferWave::~CAudioBufferWave()
{

}

Void CAudioBufferWave::SetFilePath( const CFilePath& path )
{
	m_FilePath = path;
}

Bool CAudioBufferWave::Initialize( )
{
	CFile f( m_FilePath );

	if( f.IsOpen() == FALSE )
		return FALSE;

	Char id[5]; 
	UInt32 size; 

	UInt32 length ;
	Int16 format ;
	Int16 channel ;
	UInt32 samplingRate ;
	UInt32 avgByteSec ;
	Int16 blockAlign ;
	Int16 bitsPerSample ;
	UInt32 dataSize;

	MemoryFill( id, 0, 5 );

	f.Read( id, sizeof(Byte)*4 );
	if (StringCompare( id, "RIFF" ) == 0 )
	{ 
		//we had 'RIFF' let's continue
		f.Read( &size,sizeof(UInt32) );
		//read in 32bit size value
		f.Read( id,sizeof(Byte) * 4 );
		//read in 4 byte string now
		if (StringCompare( id, "WAVE" ) == 0 )
		{ 
			//this is probably a wave file since it contained "WAVE"
			f.Read( id, sizeof(Byte)*4 ); //read in 4 bytes "fmt ";

			f.Read(&length, sizeof(UInt32) );
			f.Read(&format, sizeof(Int16) );
			if( format != 1 )
			{
				DebugLogWarning( "Wave file: \"%s\", is not using raw PCM data", m_FilePath.GetPath() );
				return FALSE;
			}

			f.Read(&channel, sizeof(Int16) );
			f.Read(&samplingRate, sizeof(UInt32) );
			f.Read(&avgByteSec, sizeof(UInt32) );
			f.Read(&blockAlign, sizeof(Int16) );
			f.Read(&bitsPerSample, sizeof(Int16) ); 

			f.Read( id, sizeof(Byte)*4 ); //read in 4 bytes "data";
			f.Read( &dataSize, sizeof(UInt32) );

			EFormat format = DeduceFormat( bitsPerSample, channel );
			if( format == nFormat_None )
			{
				DebugLogWarning( "Wave file: \"%s\", is not using a valid sound format", m_FilePath.GetPath() );
				return FALSE;
			}

			AllocatePCMBuffer( dataSize/(bitsPerSample/8), format, samplingRate );

			f.Read( m_Data.GetBuffer(),dataSize );

			BindPCMData();
		}
		else
		{
			DebugLogWarning( "Wave file: \"%s\", is a valid RIFF file but does not contain WAVE data", m_FilePath.GetPath() );
			return FALSE;
		}
	} 
	else
	{
		DebugLogWarning( "Wave file: \"%s\", failled to open file", m_FilePath.GetPath() );
		return FALSE;
	}

	return TRUE;
}

CAudioBufferWave::EFormat CAudioBufferWave::DeduceFormat( UInt32 bitPerSamples, UInt32 channel ) const
{
	if( bitPerSamples == 16 && channel == 1 )
	{
		return nFormat_Mono16;
	}
	else if( bitPerSamples == 16 && channel == 2 )
	{
		return nFormat_Stereo16;
	}
	else if( bitPerSamples == 8 && channel == 1 )
	{
		return nFormat_Mono8;
	}
	else if( bitPerSamples == 8 && channel == 2 )
	{
		return nFormat_Stereo8;
	}

	return nFormat_None;
}

Bool CAudioBufferWave::Serialize( CPersistentArchive& ar )
{
	Int16 version = 0;

	if( ar.BeginScope( WT("AudioBufferWave" ), version ) == version )
	{
		ar.Serialize(  m_FilePath, WT("FilePath") );
		return CManagedObject::Serialize( ar );
	}
	return FALSE;
}