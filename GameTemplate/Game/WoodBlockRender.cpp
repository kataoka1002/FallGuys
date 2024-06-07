#include "stdafx.h"
#include "WoodBlockRender.h"
#include "Game.h"

bool WoodBlockRender::Start()
{
	m_modelRender.Init(
		"Assets/modelData/stage/WoodBlock.tkm",
		nullptr,
		0,
		enModelUpAxisZ,
		true,
		m_maxBlock
	);

	// 静的物理オブジェクトを作成。
	m_phyStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());

	m_game = FindGO<Game>("game");

	return true;
}

void WoodBlockRender::Update()
{

}

void WoodBlockRender::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}