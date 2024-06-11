#include "stdafx.h"
#include "YellowBlockRender.h"
#include "Game.h"

namespace
{
	int YELLOW_NUM = 1;
}

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

	m_game = FindGO<Game>("game");
	m_game->SetStaticObject(YELLOW_NUM);

	return true;
}

void YellowBlockRender::Update()
{

}

void YellowBlockRender::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}