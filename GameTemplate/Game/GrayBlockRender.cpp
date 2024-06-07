#include "stdafx.h"
#include "GrayBlockRender.h"
#include "Game.h"

bool GrayBlockRender::Start()
{
	m_modelRender.Init(
		"Assets/modelData/stage/GrayBlock.tkm",
		nullptr,
		0,
		enModelUpAxisZ,
		true,
		m_maxBlock
	);

	// 静的物理オブジェクトを作成。
	//m_phyStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());

	m_game = FindGO<Game>("game");

	return true;
}

void GrayBlockRender::Update()
{

}

void GrayBlockRender::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}