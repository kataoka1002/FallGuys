#include "stdafx.h"
#include "GrayBlock.h"
#include "GrayBlockRender.h"

GrayBlock::GrayBlock()
{

}

GrayBlock::~GrayBlock()
{
	m_grayBlockRender->RemoveInstance(m_instanceNo);
}

bool GrayBlock::Start()
{
	m_grayBlockRender = FindGO<GrayBlockRender>("grayblockrender");

	return true;
}

void GrayBlock::Update()
{
	//XVˆ—
	m_grayBlockRender->UpdateInstancingData(
		m_instanceNo,
		m_position,
		m_rotation,
		m_scale
	);
}

void GrayBlock::Render(RenderContext& rc)
{

}