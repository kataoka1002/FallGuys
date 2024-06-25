#include "stdafx.h"
#include "Game.h"
#include "Stage.h"
#include "Player.h"
#include "BombInformation.h"

Game::~Game()
{
	DeleteGO(m_stage);
	DeleteGO(m_player0);
	DeleteGO(m_player1);
	DeleteGO(m_bombInfo);
}

bool Game::Start()
{
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

	g_camera3D->SetPosition(0.0f, 815.0f, -220.0f);
	g_camera3D->SetTarget(0.0f, 0.0f, -60.0f);

	//�X�e�[�W�̍쐬
	m_stage = NewGO<Stage>(0, "stage");

	//�v���C���[�̍쐬
	m_player0 = NewGO<Player>(0, "player");
	m_player0->SetPlayerNo(0);
	m_player0->SetPosition(Vector3{ 0.0f,0.0f,-180.0f });

	//�v���C���[�̍쐬
	m_player1 = NewGO<Player>(0, "player");
	m_player1->SetPlayerNo(1);
	m_player1->SetPosition(Vector3{ 0.0f,0.0f,180.0f });

	//���e�C���^�[�t�F�[�X�̍쐬
	m_bombInfo = NewGO<BombInformation>(0, "bombinformation");
	m_bombInfo->SetPlayerPtr(m_player0, m_player1);

	//�X�J�C�L���[�u�̍쐬
	m_skyCube = NewGO<SkyCube>(0, "skycube");
	m_skyCube->SetLuminance(1.0f);
	m_skyCube->SetScale(250.0f);
	m_skyCube->SetType((EnSkyCubeType)enSkyCubeType_Day);

	// �����̐ݒ�
	g_renderingEngine->SetAmbient(Vector3{ 2.5f,2.5f,2.5f });

	//�f�B���N�V�������C�g�̐ݒ�
	g_renderingEngine->SetDirectionLight(0, Vector3{ 0.0f,-1.0f,0.0f }, Vector3{ 3.0f,3.0f,3.0f });

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