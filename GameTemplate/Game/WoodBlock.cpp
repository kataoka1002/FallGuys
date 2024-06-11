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
	//�X�V����
	m_woodBlockRender->UpdateInstancingData(
		m_instanceNo,
		m_position,
		m_rotation,
		m_scale
	);
}

void WoodBlock::SetStaticObject(int num)
{
	//�X�V����
	m_woodBlockRender->UpdateInstancingData(
		m_instanceNo,
		m_position,
		m_rotation,
		m_scale
	);

	// �ÓI�����I�u�W�F�N�g���쐬�B
	m_phyStaticObject.CreateFromModel(m_woodBlockRender->GetModel(), m_woodBlockRender->GetWorldMatrix(m_instanceNo));
}

void WoodBlock::Render(RenderContext& rc)
{

}