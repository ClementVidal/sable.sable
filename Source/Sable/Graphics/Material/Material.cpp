#include <Sable/Graphics/Material/Material.h>

#include <Sable/Core/ManagedObject/Ref.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1_ALLOC( Sable, CMaterial, CManagedObject );


CMaterial::CMaterial( )
{
}

CMaterial::~CMaterial()
{
}

Void CMaterial::SetShader( CShader* sh )
{
	m_Shader = sh;
}

CShader* CMaterial::GetShader( ) const
{
	return m_Shader;
}

/**
Thie will Remove all the parameters added to this material
*/
Void CMaterial::RemoveAllParameters()
{
    m_ParameterTable.ClearAllItems();
}

Void CMaterial::FlushParametersValues( CShader& shader ) const
{
	DebugProfile("CMaterial::FlushParametersValues");
	
	ParameterTable::Iterator it;

	ForEachItem( it, m_ParameterTable )
	{
		CShaderParameter* p = shader.GetParameter( (*it).GetName() );

		if( p )
			p->SetValue( (*it).GetShaderParameterData() );
	}
}

Bool CMaterial::IsOpaque() const
{
    if( m_Shader && m_Shader->GetBlendStates() && m_Shader->GetBlendStates()->GetDesc().BlendEnable[0] )
        return FALSE;

    return TRUE;
}

/**
Use this method to initialize all the material shader's.
The main purpose of this function, is to be called after de serialization of a material.
*/
Void CMaterial::Load()
{
	if( m_Shader )
	{
		m_Shader->Load();
	}
}

Bool CMaterial::Serialize( CPersistentArchive& ar )
{
	Int16 version = 0;
	UInt32 i, paramCount;
	CStringIdentifier name;
	ParameterTable::Iterator it;

	if( ar.BeginScope( WT("Material"), version ) == version )
	{
		paramCount = m_ParameterTable.GetItemCount();
		ar.Serialize( paramCount, WT("ParamCount") );
		if( ar.IsStoring() )
		{
			ForEachItem( it, m_ParameterTable )
			{
                if( ar.BeginScope( WT("Entry" ), version ) == version )
                {
                    ar.Serialize( (*it), WT("Param") );

                    ar.EndScope();
                }
			}
		}
		else
		{
			m_ParameterTable.ClearAllItems();
			for( i=0;i<paramCount;i++ )
			{
                if( ar.BeginScope( WT("Entry" ), version ) == version )
                {
					CMaterialParameter& p = m_ParameterTable.AddItemAtEnd();
					ar.Serialize( p, WT("Param") );
                    ar.EndScope();
                }
			}
		}

		ar.Serialize( m_Shader, WT("Shader") );
	
		ar.EndScope();

		return CManagedObject::Serialize( ar );
	}
	
	return FALSE;
}

CMaterialParameter* CMaterial::GetParameter( String name )
{
	ParameterTable::Iterator it;

	ForEachItem( it, m_ParameterTable )
	{
		if( StringCompare( (*it).GetName(), name ) == 0 )
			return &(*it);
	}

	return NULL;
}

Void CMaterial::AddParameter( String name )
{
	DebugAssert( !GetParameter(name) );

	CMaterialParameter parameter( name );
	m_ParameterTable.AddItemAtEnd( parameter );

}

Void CMaterial::SetParameterValue( String name, const CMaterialParameter& data )
{
	CMaterialParameter* p = GetParameter( name );
	if( !p )
		return;

	p->SetValue( data );
}

Void CMaterial::SetParameterValue( String name, const Float32 data )
{
	CMaterialParameter* p = GetParameter( name );
	if( !p )
		return;

	p->SetValue( data );
}

Void CMaterial::SetParameterValue( String name, const STuple2f& data )
{
	CMaterialParameter* p = GetParameter( name );
	if( !p )
		return;

	p->SetValue( data );
}

Void CMaterial::SetParameterValue( String name, const STuple3f& data )
{
	CMaterialParameter* p = GetParameter( name );
	if( !p )
		return;

	p->SetValue( data );
}

Void CMaterial::SetParameterValue( String name, const STuple4f& data )
{
	CMaterialParameter* p = GetParameter( name );
	if( !p )
		return;

	p->SetValue( data );
}

Void CMaterial::SetParameterValue( String name, const CVector2f& data )
{
	CMaterialParameter* p = GetParameter( name );
	if( !p )
		return;

	p->SetValue( data );
}

Void CMaterial::SetParameterValue( String name, const CVector3f& data )
{
	CMaterialParameter* p = GetParameter( name );
	if( !p )
		return;

	p->SetValue( data );
}

Void CMaterial::SetParameterValue( String name, const CVector4f& data )
{
	CMaterialParameter* p = GetParameter( name );
	if( !p )
		return;

	p->SetValue( data );
}

Void CMaterial::SetParameterValue( String name, const CColor& data )
{
	CMaterialParameter* p = GetParameter( name );
	if( !p )
		return;

	p->SetValue( data );
}

Void CMaterial::SetParameterValue( String name, const Int32 data )
{
	CMaterialParameter* p = GetParameter( name );
	if( !p )
		return;

	p->SetValue( data );
}

Void CMaterial::SetParameterValue( String name, const CTexture2D& data )
{
	CMaterialParameter* p = GetParameter( name );
	if( !p )
		return;

	p->SetValue( data );
}

Void CMaterial::SetParameterValue( String name, const CTexture3D& data )
{
	CMaterialParameter* p = GetParameter( name );
	if( !p )
		return;

	p->SetValue( data );
}

Void CMaterial::SetParameterValue( String name, const CTextureCube& data )
{
	CMaterialParameter* p = GetParameter( name );
	if( !p )
		return;

	p->SetValue( data );
}

Void CMaterial::SetParameterValue( String name, const CStatesSampler& data )
{
	CMaterialParameter* p = GetParameter( name );
	if( !p )
		return;

	p->SetValue( data );
}