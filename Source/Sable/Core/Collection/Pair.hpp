template <class First, class Second>
CPair<First,Second>::CPair()
{
}

template <class First, class Second>
CPair<First,Second>::CPair( const First& first, const Second& second )
{
	m_First = first;
	m_Second = second;
}

template <class First, class Second>
Bool CPair<First,Second>::operator==( const CPair<First,Second>& other ) const
{
	if( m_First == other.m_First && m_Second == other.m_Second )
		return TRUE;

	return FALSE;
}

template <class First, class Second>
CPair<First,Second>::~CPair()
{
}

template <class First, class Second>
First& CPair<First,Second>::GetFirst()
{
    return m_First;
}

template <class First, class Second>
const First& CPair<First,Second>::GetFirst() const
{
	return m_First;
}

template <class First, class Second>
Second& CPair<First,Second>::GetSecond()
{
	return m_Second;
}

template <class First, class Second>
const Second& CPair<First,Second>::GetSecond() const
{
	return m_Second;
}

template <class First, class Second>
Void CPair<First,Second>::Set( const First& first, const Second& second )
{
	m_First = first;
	m_Second = second;
}

template <class First, class Second>
Void CPair<First,Second>::SetFirst( const First& first )
{
	m_First = first;
}

template <class First, class Second>
Void CPair<First,Second>::SetSecond( const Second& second )
{
	m_Second = second;
}
