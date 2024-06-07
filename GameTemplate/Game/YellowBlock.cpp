#include "stdafx.h"
#include "YellowBlock.h"
#include "YellowBlockRender.h"

YellowBlock::YellowBlock()
{

}

YellowBlock::~YellowBlock()
{
	m_yellowBlockRender->RemoveInstance(m_instanceNo);
}

bool YellowBlock::Start()
{
	m_yellowBlockRender = FindGO<YellowBlockRender>("yellowblockrender");

	return true;
}

void YellowBlock::Update()
{
	//XVˆ—
	m_yellowBlockRender->UpdateInstancingData(
		m_instanceNo,
		m_position,
		m_rotation,
		m_scale
	);
}

void YellowBlock::Render(RenderContext& rc)
{

}