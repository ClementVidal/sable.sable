#include <Sable/Graphics/States/Sampler.h>

#include <Sable/Core/Collection/Heap.h>

using namespace Sable;

IMPLEMENT_MANAGED_CLASS1_ALLOC( Sable, CStatesSampler, CManagedObject );

CStatesSampler::SDesc::SDesc()
{
	MinFilter = nStateFilter_Linear;
	MagFilter = nStateFilter_Linear;
	MipFilter = nStateFilter_Linear;

	AddressU = nStateAddress_Wrap;
	AddressV = nStateAddress_Wrap;
	AddressW = nStateAddress_Clamp;

	MaxLOD = FLOAT32_MAX_VAL;
	MinLOD = FLOAT32_MIN_VAL;
}

CStatesSampler::CStatesSampler() :
	m_Impl( *this )
{

}

CStatesSampler::~CStatesSampler()
{

}

const CImplStatesSampler& CStatesSampler::GetImpl() const
{
	return m_Impl;
}

const CStatesSampler::SDesc& CStatesSampler::GetDesc() const
{
	return m_Desc;
}

Void CStatesSampler::Acquire( const CStatesSampler::SDesc& desc )
{
	m_Desc = desc;
	m_Impl.Acquire();
}