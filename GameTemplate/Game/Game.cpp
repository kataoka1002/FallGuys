#include "stdafx.h"
#include "Game.h"
#include "Stage.h"
#include "Player.h"
#include "BombInformation.h"
#include "LevelUpItemInformation.h"

namespace
{
	//プレイヤーのスタート位置
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
	//エフェクトの設定
	EffectEngine::GetInstance()->ResistEffect(enEffectName_BombExplosion, u"Assets/effect/bombExplosion.efk");

	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

	//カメラの設定
	g_camera3D->SetPosition(0.0f, 815.0f, -220.0f);
	g_camera3D->SetTarget(0.0f, 0.0f, -60.0f);

	//ステージの作成
	m_stage = NewGO<Stage>(0, "stage");

	//プレイヤーの作成
	m_player0 = NewGO<Player>(0, "player");
	m_player0->SetPlayerNo(0);
	m_player0->SetPosition(PLAYER_POSITION_1);
	m_playerList.emplace_back(m_player0);

	//プレイヤーの作成
	m_player1 = NewGO<Player>(0, "player");
	m_player1->SetPlayerNo(1);
	m_player1->SetPosition(PLAYER_POSITION_2);
	m_playerList.emplace_back(m_player1);

	//爆弾インターフェースの作成
	m_bombInfo = NewGO<BombInformation>(0, "bombinformation");
	m_bombInfo->SetPlayerPtr(m_player0, m_player1);

	//スカイキューブの作成
	m_skyCube = NewGO<SkyCube>(0, "skycube");
	m_skyCube->SetLuminance(1.0f);
	m_skyCube->SetScale(250.0f);
	m_skyCube->SetType((EnSkyCubeType)enSkyCubeType_Day);

	//レベルアップアイテムインターフェースの作成
	m_levelUpItemInfo = NewGO<LevelUpItemInformation>(0, "levelupiteminformation");

	// 環境光の設定
	g_renderingEngine->SetAmbient(Vector3{ 2.5f,2.5f,2.5f });

	//ディレクションライトの設定
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