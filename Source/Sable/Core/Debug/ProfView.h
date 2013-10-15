#ifndef _SABLE_CORE_DEBUG_PROFVIEW_
#define _SABLE_CORE_DEBUG_PROFVIEW_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\Debug\Prof.h>
#include <Sable\Core\Collection\Stack.h>
#include <Sable\Setup.h>

namespace Sable
{

/**
\ingroup CoreDebug
Use this class to manage the user interaction 
and display of formated profilling informations
*/
class CDebugProfView 
{

public:

	/** @Name Constructor/Destructor*/
	//@{
	CDebugProfView();
	~CDebugProfView();
	//@}

	/** @Name Accessors*/
	//@{
	String	GetBuffer() const;
	//@}

	/** @Name Manipulator*/
	//@{
	Void	Sample( );
	Void	Update();
	Void	MoveUp();
	Void	MoveDown();
	Void	MoveForward();
	Void    MoveBackward();
	//@}

private:

	// DataType
	struct SHistoryStep
	{
		SHistoryStep();
		CProfileNode*	    Node;
		Int32				SelectionMark;	
	};
	
	// Methods
	Void	Format( );

	// Attributes
	CArray<Char>			m_Buffer;
	CProfileNode*		    m_CurrentNode;
	Int32					m_SelectionMark;
	Int32					m_EntryCount;
	CStack<SHistoryStep>	m_NavigationHistory;
};


}

#endif
