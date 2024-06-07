#include "stdafx.h"
#include "WoodBlock.h"
#include "WoodBlockRender.h"

WoodBlock::WoodBlock()
{

}

WoodBlock::~WoodBlock()
{
	m_woodBlockRender->RemoveInstance(m_instanceNo);
}

bool WoodBlock::Start()
{
	m_woodBlockRender = FindGO<WoodBlockRender>("woodblockrender");

	return true;
}

void WoodBlock::Update()
{
	//XVˆ—
	m_woodBlockRender->UpdateInstancingData(
		m_instanceNo,
		m_position,
		m_rotation,
		m_scale
	);
}

void WoodBlock::Render(RenderContext& rc)
{

}