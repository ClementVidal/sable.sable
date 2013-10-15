#ifndef _SABLE_GAME_PARAMETER_PROPERTY_
#define _SABLE_GAME_PARAMETER_PROPERTY_

#include <Sable\Core\Common\DataTypes.h>

namespace Sable
{

/**  
\ingroup Game
GameObject
*/
class CGameProperty 
{

public:

	/** @name DataTypes */
	//@{
	enum EType
	{
		nType_Int = 0,
		nType_Float,
		nType_Bool,
		nType_Tuple2f,
		nType_Tuple3f,
		nType_Tuple4f,
		nType_Count,
		nType_None = -1
	};
	//@}

	/** @name Constructor/destructor */
	//@{
	CGameProperty();
	CGameProperty( EType type );
	~CGameProperty();
	//@}

	/** @name Accessors*/
	//@{
	Void				SetAsFloat( Float32 d );
	Void				SetAsInt( Int32 d );
	Void				SetAsBool( Bool d );
	Void				SetAsVector2( const CVector2f& d);
	Void				SetAsVector3( const CVector3f& d);
	Void				SetAsVector4( const CVector4f& d);

	Float32				GetAsFloat() const;
	Int32				GetAsInt() const;
	Bool				GetAsBool() const;
	const CVector2f&	GetAsVector2() const;
	const CVector3f&	GetAsVector3() const;
	const CVector4f&	GetAsVector4() const;
	//@}

	/** @name Manipulator*/
	//@{
	//@}

private:

	// Types
	union
	{
		Int32		m_IntValue;
		Float32		m_FloatValue;
		STuple4f	m_Tuple4fValue;
		STuple3f	m_Tuple3fValue;
		STuple2f	m_Tuple2fValue;
		Bool		m_BoolValue;
	};
	EType	m_Type;

    // Methods

    // Attributes

};

}

#endif
