#include "stdafx.h"
#include "WoodBlockRender.h"
#include "Game.h"

namespace
{
	int WOOD_NUM = 4;
}

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

	m_game = FindGO<Game>("game");
	m_game->SetStaticObject(WOOD_NUM);

	return true;
}

void WoodBlockRender::Update()
{

}

void WoodBlockRender::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}