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
	//�X�V����
	m_brownBlockRender->UpdateInstancingData(
		m_instanceNo,
		m_position,
		m_rotation,
		m_scale
	);
}

void BrownBlock::SetStaticObject(int num)
{
	//�X�V����
	m_brownBlockRender->UpdateInstancingData(
		m_instanceNo,
		m_position,
		m_rotation,
		m_scale
	);

	// �ÓI�����I�u�W�F�N�g���쐬�B
	m_phyStaticObject.CreateFromModel(m_brownBlockRender->GetModel(), m_brownBlockRender->GetWorldMatrix(m_instanceNo));
}

void BrownBlock::Render(RenderContext& rc)
{

}