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
	//更新処理
	m_woodBlockRender->UpdateInstancingData(
		m_instanceNo,
		m_position,
		m_rotation,
		m_scale
	);
}

void WoodBlock::SetStaticObject(int num)
{
	//更新処理
	m_woodBlockRender->UpdateInstancingData(
		m_instanceNo,
		m_position,
		m_rotation,
		m_scale
	);

	// 静的物理オブジェクトを作成。
	m_phyStaticObject.CreateFromModel(m_woodBlockRender->GetModel(), m_woodBlockRender->GetWorldMatrix(m_instanceNo));
}

void WoodBlock::Render(RenderContext& rc)
{

}