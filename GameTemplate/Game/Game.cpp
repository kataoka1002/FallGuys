#include "stdafx.h"
#include "Game.h"
#include "Stage.h"
#include "Player.h"
#include "BombInformation.h"
#include "LevelUpItemInformation.h"

namespace
{
	//�v���C���[�̃X�^�[�g�ʒu
	const Vector3 PLAYER_POSITION_1 = { -360.0f,0.0f,300.0f };
	const Vector3 PLAYER_POSITION_2 = { 360.0f,0.0f,300.0f };
	const Vector3 PLAYER_POSITION_3 = { -360.0f,0.0f,-300.0f };
	const Vector3 PLAYER_POSITION_4 = { 360.0f,0.0f,-300.0f };
}

Game::~Game()
{
	DeleteGO(m_stage);
	DeleteGO(m_bombInfo);
	DeleteGO(m_levelUpItemInfo);

	for (auto player : m_playerList)
	{
		DeleteGO(player);
	}
	m_playerList.clear();
}

bool Game::Start()
{
	//�G�t�F�N�g�̐ݒ�
	EffectEngine::GetInstance()->ResistEffect(enEffectName_BombExplosion, u"Assets/effect/bombExplosion.efk");

	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

	//�J�����̐ݒ�
	g_camera3D->SetPosition(0.0f, 815.0f, -220.0f);
	g_camera3D->SetTarget(0.0f, 0.0f, -60.0f);

	//�X�e�[�W�̍쐬
	m_stage = NewGO<Stage>(0, "stage");

	//�v���C���[�̍쐬
	m_player0 = NewGO<Player>(0, "player");
	m_player0->SetPlayerNo(0);
	m_player0->SetPosition(PLAYER_POSITION_1);
	m_playerList.emplace_back(m_player0);

	//�v���C���[�̍쐬
	m_player1 = NewGO<Player>(0, "player");
	m_player1->SetPlayerNo(1);
	m_player1->SetPosition(PLAYER_POSITION_2);
	m_playerList.emplace_back(m_player1);

	//���e�C���^�[�t�F�[�X�̍쐬
	m_bombInfo = NewGO<BombInformation>(0, "bombinformation");
	m_bombInfo->SetPlayerPtr(m_player0, m_player1);

	//�X�J�C�L���[�u�̍쐬
	m_skyCube = NewGO<SkyCube>(0, "skycube");
	m_skyCube->SetLuminance(1.0f);
	m_skyCube->SetScale(250.0f);
	m_skyCube->SetType((EnSkyCubeType)enSkyCubeType_Day);

	//���x���A�b�v�A�C�e���C���^�[�t�F�[�X�̍쐬
	m_levelUpItemInfo = NewGO<LevelUpItemInformation>(0, "levelupiteminformation");

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