#include "stdafx.h"
#include "BrownBlock.h"
#include "BrownBlockRender.h"

BrownBlock::BrownBlock()
{

}

BrownBlock::~BrownBlock()
{
	m_brownBlockRender->RemoveInstance(m_instanceNo);
}

bool BrownBlock::Start()
{
	m_brownBlockRender = FindGO<BrownBlockRender>("brownblockrender");

	return true;
}

void BrownBlock::Update()
{
	//XVˆ—
	m_brownBlockRender->UpdateInstancingData(
		m_instanceNo,
		m_position,
		m_rotation,
		m_scale
	);
}

void BrownBlock::Render(RenderContext& rc)
{

}