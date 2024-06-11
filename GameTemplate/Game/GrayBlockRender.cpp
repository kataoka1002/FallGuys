#include "stdafx.h"
#include "GrayBlockRender.h"
#include "Game.h"

namespace
{
	int GRAY_NUM = 3;
}

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

	m_game = FindGO<Game>("game");
	m_game->SetStaticObject(GRAY_NUM);

	return true;
}

void GrayBlockRender::Update()
{

}

void GrayBlockRender::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}