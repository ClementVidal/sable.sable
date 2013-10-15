#ifndef _SABLE_CORE_DEBUG_PROFNODE_
#define _SABLE_CORE_DEBUG_PROFNODE_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Setup.h>

namespace Sable
{

/**
\ingroup CoreDebug
A node in the Profile Hierarchy Tree
*/
class	CProfileNode 
{

public:

	/** @Name Constructor/Destructor*/
	//@{
	CProfileNode( );
	~CProfileNode();
	//@}

	/** @Name Accessors */
	//@{
    CProfileNode*   AddChild( String name );
	CProfileNode*	GetChild( String name );
	CProfileNode*	GetChild( UInt32 index );
	CProfileNode*	GetParent()		{ return m_Parent; }
	CProfileNode*	GetSibling()		{ return m_Sibling; }
	CProfileNode*	GetChild()			{ return m_Child; }
	String			GetName()				{ return m_Name; }
	Int32			GetTotalCalls()		{ return m_TotalCalls; }
	Float32			GetTotalSamplingTime()  const;
	Float32			GetTotalPauseTime()  const;
	//@}

	/** @Name Manipulators */
	//@{
	Void			Reset();
	Void			Call();
	bool			Return();
	//@}


protected:

	// Friendship
	friend class CDebugProf;

	// Methods
	Void Initialize( String name, CProfileNode* parent );

	// Attributes
	String			m_Name;
	Int32			m_TotalCalls;
	Int64			m_TotalSamplingTime;
	Int64			m_SamplingStart;

	Int32			m_RecursionCounter;
	CProfileNode*	m_Parent;
	CProfileNode*	m_Child;
	CProfileNode*	m_Sibling;
};

}

#endif
