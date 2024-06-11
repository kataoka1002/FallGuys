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
	
}

void YellowBlock::SetStaticObject(int num)
{
	//更新処理
	m_yellowBlockRender->UpdateInstancingData(
		m_instanceNo,
		m_position,
		m_rotation,
		m_scale
	);

	// 静的物理オブジェクトを作成。
	m_phyStaticObject.CreateFromModel(m_yellowBlockRender->GetModel(), m_yellowBlockRender->GetWorldMatrix(m_instanceNo));
}

void YellowBlock::Render(RenderContext& rc)
{

}