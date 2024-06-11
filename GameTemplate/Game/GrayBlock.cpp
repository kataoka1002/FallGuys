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
	//更新処理
	m_grayBlockRender->UpdateInstancingData(
		m_instanceNo,
		m_position,
		m_rotation,
		m_scale
	);
}

void GrayBlock::SetStaticObject(int num)
{
	//更新処理
	m_grayBlockRender->UpdateInstancingData(
		m_instanceNo,
		m_position,
		m_rotation,
		m_scale
	);

	// 静的物理オブジェクトを作成。
	m_phyStaticObject.CreateFromModel(m_grayBlockRender->GetModel(), m_grayBlockRender->GetWorldMatrix(m_instanceNo));
}

void GrayBlock::Render(RenderContext& rc)
{

}