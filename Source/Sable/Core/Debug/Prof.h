#ifndef _SABLE_CORE_DEBUG_PROF_
#define _SABLE_CORE_DEBUG_PROF_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\Time\Timer.h>
#include <Sable\Core\Debug\ProfNode.h>
#include <Sable\Setup.h>

#ifdef SETUP_USE_PROF
	#define	DebugProfile( name )			Sable::CProfileSample profileSample( name )
#else
	#define	DebugProfile( name )
#endif

namespace Sable
{

/**
\ingroup CoreDebug
The Manager for the Profile system
*/
class CDebugProf 
{

public:

	/** @Name DataTypes*/
	//@{
	enum EState
	{
		nState_DoSampling = 1,
		nState_AskEnableSampling,
		nState_AskDisableSampling,
		nState_AskReset
	};

	//@}

	/** @Name Constructor/Destructor*/
	//@{
	CDebugProf();
	~CDebugProf();
	//@}

    /** @Name Accessors*/
    //@{
    CProfileNode* GetRootNode() const;
    //@}

	/** @Name Manipulator*/
	//@{
	Void						StartFrame();
	Void						EndFrame();
	Void						EnableSampling( Bool onOff );
	Void						StartProfile( String name );
	Void						StopProfile();
	Void						Reset();
	Float32						GetTimeSinceReset();
	UInt32						GetSampledFrameCount() const;
	//@}

private:

	// friendship
	friend class CProfileNode;
	
	// Methods
	Int64						GetTicks();
	Int64						GetTicksFreq();
	CProfileNode*				RequestNode( String name, CProfileNode* parent );

	// Attributes
	CProfileNode*			m_Root;
	CProfileNode*			m_CurrentNode;
	Int64					m_ResetTime;
	CTimer					m_Timer;
	CArray<CProfileNode>	m_NodePool;
	UInt32					m_NodeCount;
	CBitArray32				m_States;
	UInt32					m_FrameCount;
};


/**
\ingroup CoreDebug
ProfileSampleClass is a simple way to profile a function's scope
Use the PROFILE macro at the start of scope to time
*/
class	CProfileSample 
{

public:
	
	/** @Name Constructor/Destructor*/
	//@{
	CProfileSample( String name );
	~CProfileSample();					
	//@}

};

}

#endif
