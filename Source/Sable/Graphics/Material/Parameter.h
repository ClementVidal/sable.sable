#ifndef _GRAPHICS_MATERIAL_DATA_
#define _GRAPHICS_MATERIAL_DATA_

#include <Sable/Core/Common/DataTypes.h>
#include <Sable/Graphics/Common/DataTypes.h>
#include <Sable/Graphics/Shader/ParameterData.h>
#include <Sable/Core/ManagedObject/Ref.h>
#include <Sable/Core/String/StaticString.h>

namespace Sable
{

class CVector3f;
class CVector4f;
class CMatrix4x4f;
class CTexture2D;
class CTextureCube;
class CTexture;
class CStatesSampler;

/** 
\ingroup GraphicsMaterial
Provide a way to store heterogeneous type of data.
CMaterialParameter is build on top of CShaderParameterData to provide an easy interaction with the 
Shader Sub-System.

\note
Because CShaderParameterData DOES NOT store a copy of the data, but just a pointer to it, 
it's CMaterialParameter which own this copy.
*/
class CMaterialParameter
{

public:

    /** @name Constructor/Destructor*/
	//@{
    struct SNumericalData
    {
        union
        {
	        Float32		Float32Data;
			STuple2f	Vector2Data;
	        STuple3f	Vector3Data;
	        STuple4f	Vector4Data;
	        Int32		Int32Data;
        };
    };
    //@}

	/** @name Constructor/Destructor*/
	//@{
	CMaterialParameter( );
	CMaterialParameter( String name );
	~CMaterialParameter( );
	//@}

	/** @name Accessors*/
	//@{
	String							GetName() const;
	const CShaderParameterData&		GetShaderParameterData( ) const;
	const Float32&					GetFloat32() const ;
	const CVector3f&				GetVector3() const ;
	const CVector4f&				GetVector4() const ;
	const CVector2f&				GetVector2() const ;
	const Int32&					GetInt32() const ;
	const CColor&					GetColor() const ;
	CRef<CTexture>					GetTexture() const ;
	CRef<CStatesSampler>			GetSampler() const ;

	Void							SetValue( const CMaterialParameter& data );
	Void							SetValue( const Float32 data );
	Void							SetValue( const STuple2f& data );
	Void							SetValue( const STuple3f& data );
	Void							SetValue( const STuple4f& data );
	Void							SetValue( const CVector2f& data );
	Void							SetValue( const CVector3f& data );
	Void							SetValue( const CVector4f& data );
	Void							SetValue( const CColor& data );
	Void							SetValue( const Int32 data );
	Void							SetValue( const CTexture2D& data );
	Void							SetValue( const CTexture3D& data );
	Void							SetValue( const CTextureCube& data );
	Void							SetValue( const CStatesSampler& data );	
	//@}

	/** @name Accessors*/
	//@{
	Bool							Serialize( CPersistentArchive& ar );
	//@}

private:

	// Methods
	Void BindShaderParameterFromType( EShaderParameterType type );

	// Attribute	
    SNumericalData          m_NumericalData;
    CRef<CManagedObject>	m_ObjectData;
	CShaderParameterData    m_Parameter;
	CStringIdentifier		m_Name;

};

Inline
const CShaderParameterData&	CMaterialParameter::GetShaderParameterData( ) const
{
	return m_Parameter;
}

Inline
const Float32& CMaterialParameter::GetFloat32() const 
{
	return m_NumericalData.Float32Data;
}

Inline
const CVector3f& CMaterialParameter::GetVector3() const 
{
	return ( const CVector3f& ) m_NumericalData.Vector3Data;
}

Inline
const CVector2f&	CMaterialParameter::GetVector2() const 
{
	return ( const CVector2f& ) m_NumericalData.Vector2Data;
}

Inline
const CVector4f&	CMaterialParameter::GetVector4() const 
{
	return ( const CVector4f& ) m_NumericalData.Vector4Data;
}

Inline
	const Int32& CMaterialParameter::GetInt32() const 
{
	return m_NumericalData.Int32Data;
}

Inline
CRef<CTexture> CMaterialParameter::GetTexture() const
{
	return &((CTexture&)*m_ObjectData);
}

Inline
CRef<CStatesSampler> CMaterialParameter::GetSampler() const
{
	return &((CStatesSampler&)*m_ObjectData);
}

}

#endif
