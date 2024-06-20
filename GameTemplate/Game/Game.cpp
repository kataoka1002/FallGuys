#include "stdafx.h"
#include "Game.h"
#include "Stage.h"
#include "Player.h"
#include "BombInformation.h"

Game::~Game()
{
	
}

bool Game::Start()
{
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

	g_camera3D->SetPosition(0.0f, 815.0f, -220.0f);
	g_camera3D->SetTarget(0.0f, 0.0f, -60.0f);

	//�X�e�[�W�̍쐬
	m_stage = NewGO<Stage>(0, "stage");

	//�v���C���[�̍쐬
	m_player = NewGO<Player>(0, "player");

	//���e�C���^�[�t�F�[�X�̍쐬
	m_bombInfo = NewGO<BombInformation>(0, "bombinformation");

	return true;
}

void Game::Update()
{
	if (g_pad[0]->IsPress(enButtonLeft))
	{
		m_camerapos.z += 10.0f;
	}
	if (g_pad[0]->IsPress(enButtonRight))
	{
		m_camerapos.z -= 10.0f;
	}
	if (g_pad[0]->IsPress(enButtonUp))
	{
		m_camerapos.y += 10.0f;
	}
	if (g_pad[0]->IsPress(enButtonDown))
	{
		m_camerapos.y -= 10.0f;
	}

	g_camera3D->SetPosition(m_camerapos);

	// g_renderingEngine->DisableRaytracing();
}

void Game::Render(RenderContext& rc)
{
	
}