#include "stdafx.h"
#include "YellowBlockRender.h"
#include "Game.h"

bool YellowBlockRender::Start()
{
	m_modelRender.Init(
		"Assets/modelData/stage/YellowBlock.tkm",
		nullptr,
		0,
		enModelUpAxisZ,
		true,
		m_maxBlock
	);

	// 静的物理オブジェクトを作成。
	m_phyStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetWorldMatrix(0));

	m_game = FindGO<Game>("game");

	return true;
}

void YellowBlockRender::Update()
{

}

void YellowBlockRender::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}