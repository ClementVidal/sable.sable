#ifndef _SABLE_CORE_COLLECTION_PAIR_
#define _SABLE_CORE_COLLECTION_PAIR_

#include <Sable/Core/Common/DataTypes.h>

namespace Sable
{

/** 
\ingroup CoreCollection
Pair class
*/
template <class First, class Second>
class CPair
{

public:

	/** @name Constructor/Destructor*/
    //@{
	CPair();
	CPair( const First& first, const Second& second );
	~CPair();
    //@}

	/** @name Operator*/
	//@{
	Bool operator==( const CPair<First,Second>& other ) const;
	//@}

    /** @name Accessors*/
    //@{
	First&			GetFirst();
	const First&	GetFirst() const;
	Second&			GetSecond();
	const Second&	GetSecond() const;

	Void			Set( const First& first, const Second& second );
	Void			SetFirst( const First& first );
	Void			SetSecond( const Second& second );
    //@}

	/** @name Manipulator*/
    //@{
    //@}

private:

	// Types

    //Attributes
	First		m_First;
	Second		m_Second;

};

#include <Sable/Core/Collection/Pair.hpp>

}
#endif
