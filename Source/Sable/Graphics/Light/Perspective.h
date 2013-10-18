#ifndef _GRAPHICS_LIGHT_PERSPECTIVE_
#define _GRAPHICS_LIGHT_PERSPECTIVE_

#include <Sable/Core/Common/DataTypes.h>

#include <Sable/Graphics/Light/Light.h>

namespace Sable
{

/** 
PerspectiveCamera. 
*/
class CLightPerspective : public CLight
{

	DEFINE_MANAGED_CLASS( CLightPerspective );

public:

	/** @name Constructor/Destructor*/
	//@{
	CLightPerspective();
	CLightPerspective( CNode& parent );
	virtual ~CLightPerspective();
	//@}

	/** @name Operator*/
	//@{
	//@}

	/** @name Accessor*/
	//@{
	Void SetOpeningAngle( const Float32 angle) { m_OpeningAngle = angle; }
	Float32 GetOpeningAngle() const { return m_OpeningAngle ; }
	//@}

	/** @name Manipulator*/
	//@{
	Bool	IsPointUnderInfluence( const CVector3f& point );
	//@}

protected:

	//Methods

	//Attributes
	Float32 m_OpeningAngle;


};

}
#endif
