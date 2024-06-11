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
	//�X�V����
	m_grayBlockRender->UpdateInstancingData(
		m_instanceNo,
		m_position,
		m_rotation,
		m_scale
	);
}

void GrayBlock::SetStaticObject(int num)
{
	//�X�V����
	m_grayBlockRender->UpdateInstancingData(
		m_instanceNo,
		m_position,
		m_rotation,
		m_scale
	);

	// �ÓI�����I�u�W�F�N�g���쐬�B
	m_phyStaticObject.CreateFromModel(m_grayBlockRender->GetModel(), m_grayBlockRender->GetWorldMatrix(m_instanceNo));
}

void GrayBlock::Render(RenderContext& rc)
{

}