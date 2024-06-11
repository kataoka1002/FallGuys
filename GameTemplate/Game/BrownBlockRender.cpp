#include "stdafx.h"
#include "BrownBlockRender.h"
#include "Game.h"

namespace
{
	int BROWN_NUM = 2;
}

bool BrownBlockRender::Start()
{
	m_modelRender.Init(
		"Assets/modelData/stage/BrownBlock.tkm",
		nullptr,
		0,
		enModelUpAxisZ,
		true,
		m_maxBlock
	);

	m_game = FindGO<Game>("game");
	m_game->SetStaticObject(BROWN_NUM);

	return true;
}

void BrownBlockRender::Update()
{

}

void BrownBlockRender::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}