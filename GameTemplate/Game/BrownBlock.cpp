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
	//更新処理
	m_brownBlockRender->UpdateInstancingData(
		m_instanceNo,
		m_position,
		m_rotation,
		m_scale
	);
}

void BrownBlock::SetStaticObject(int num)
{
	//更新処理
	m_brownBlockRender->UpdateInstancingData(
		m_instanceNo,
		m_position,
		m_rotation,
		m_scale
	);

	// 静的物理オブジェクトを作成。
	m_phyStaticObject.CreateFromModel(m_brownBlockRender->GetModel(), m_brownBlockRender->GetWorldMatrix(m_instanceNo));
}

void BrownBlock::Render(RenderContext& rc)
{

}