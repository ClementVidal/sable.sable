#ifndef _GRAPHICS_LIGHT_LIGHT_
#define _GRAPHICS_LIGHT_LIGHT_

#include <Sable\Core\Common\DataTypes.h>
#include <Sable\Core\Common\Color.h>
#include <Sable\Graphics\Node\Spatial.h>
#include <Sable\Core\ManagedObject\Ref.h>

namespace Sable
{

class CTexture;

/**  
Light.
*/
class CLight : public CNodeSpatial
{

DEFINE_MANAGED_CLASS( CLight );

public:

    /** @name Constructor/Destructor*/
    //@{
	CLight( );
	CLight( CNode& parent  );
	virtual ~CLight();
    //@}

    /** @name Operator*/
    //@{
    //@}

    /** @name Accessors*/
    //@{
	const CColor&			GetDiffuseColor() const { return m_DiffuseColor; }
	const CColor&			GetAmbientColor() const { return m_AmbientColor; }
	const CColor&			GetSpecularColor() const { return m_SpecularColor; }
	Void					SetDiffuseColor( const CColor& Col) { m_DiffuseColor = Col; }
	Void					SetAmbientColor( const CColor& Col) { m_AmbientColor = Col; }
	Void					SetSpecularColor( const CColor& Col) { m_SpecularColor = Col; }
	const CTexture&			GetShadowDepthMap() const  { return *m_ShadowDepthMap; }
	Bool					HasShadowDepthMap() const { return !m_ShadowDepthMap.GetIsNull(); }
	//@}

    /** @name Mutator*/
    //@{
    //@}

	/** @name Manipulator*/
	//@{
	Void			Activate( const Bool& onoff );
	Void			Show( const Bool onoff);
	virtual Bool	IsPointUnderInfluence( const CVector3f& point );
	virtual Float32	GetIntensityAtPoint( const CVector3f& point );
	//@}

private:

	//Methods

	//Attributes
    CColor          m_DiffuseColor;
    CColor          m_AmbientColor;
    CColor          m_SpecularColor;
	CRef<CTexture>	m_ShadowDepthMap;

};

}

#endif
