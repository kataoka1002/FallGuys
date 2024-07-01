#include "stdafx.h"
#include "Player.h"
#include "IPlayerState.h"
#include "PlayerIdleState.h"
#include "BombInformation.h"

namespace
{
	//歩くスピード
	const float WALK_SPEED = 100.0f;

	//キャラコンの高さ
	const float CHARACON_HEIGHT = 50.0f;

	//キャラコンの半径
	const float CHARACON_RADIUS = 10.0f;

	//爆破威力
	const int BOMB_EXPLOSION_POWER = 2;
}

Player::Player()
{
	//アニメーションの初期化
	animationClips[enAnimClip_Idle].Load("Assets/animData/playerIdle.tka");
	animationClips[enAnimClip_Idle].SetLoopFlag(true);
	animationClips[enAnimClip_Walk].Load("Assets/animData/playerWalk.tka");
	animationClips[enAnimClip_Walk].SetLoopFlag(true);

	//爆破力の設定
	m_bombExplosionPow = BOMB_EXPLOSION_POWER;
}

Player::~Player()
{

}

void Player::Update()
{
	// アニメーションを再生する。
	m_model.PlayAnimation(m_currentAnimationClip, m_complementTime);

	// ステートを変更するか
	IPlayerState* playerState = m_playerState->StateChange();

	// 変更先のステートが設定されているならば
	if (playerState != nullptr)
	{
		// ステートを変更する。
		delete m_playerState;
		m_playerState = playerState;
		m_playerState->Enter();
	}

	// 各ステートの更新処理を実行。
	m_playerState->Update();

	// モデルを更新する。
	m_model.Update();
}

void Player::InitModel()
{
	//クラスを見つける
	m_bombInfo = FindGO<BombInformation>("bombinformation");

	//アニメーションイベント用の関数を設定する
	m_model.AddAnimationEvent([&](const wchar_t* clipName, const wchar_t* eventName) {
		OnAnimationEvent(clipName, eventName);
	});

	//モデルの初期化
	m_model.Init("Assets/modelData/player/player.tkm", animationClips, enAnimClip_Num, enModelUpAxisZ);
	m_model.SetPosition(m_position);
	m_model.SetRotation(m_rotation);
	m_model.SetScale(m_scale);
	m_model.Update();

	//キャラクターコントローラーを初期化
	m_charaCon.Init(
		CHARACON_RADIUS,	//半径
		CHARACON_HEIGHT,	//高さ
		m_position			//座標
	);

	// 初期ステートを設定
	m_playerState = new PlayerIdleState(this);
	m_playerState->Enter();
}

void Player::Move()
{
	//移動速度の初期化
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

	//左スティックの入力量を受け取る
	LStick_x = g_pad[m_playerNo]->GetLStickXF();
	LStick_y = g_pad[m_playerNo]->GetLStickYF();

	//オブジェクト保持中かどうかで歩く速さを変える
	float moveSpeed;
	moveSpeed = WALK_SPEED;

	//XZ成分の移動速度をクリア
	m_moveSpeed.x = LStick_x * moveSpeed;		//右方向への移動速度を加算
	m_moveSpeed.z = LStick_y * moveSpeed;		//奥方向への移動速度を加算

	//重力の設定
	m_moveSpeed.y -= 980.0f * g_gameTime->GetFrameDeltaTime();

	//キャラクターコントローラーを使用して座標を更新
	m_position = m_charaCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());

	if (m_charaCon.IsOnGround())
	{
		//地面についた
		m_moveSpeed.y = 0.0f;
	}

	//座標を設定
	m_model.SetPosition(m_position);
}

void Player::Turn()
{
	//移動速度から回転を求める
	m_rotSpeed = Math::Lerp(g_gameTime->GetFrameDeltaTime() * 3.5f, m_rotSpeed, m_moveSpeed);

	//前方向の設定
	m_forward = m_rotSpeed;
	m_forward.Normalize();

	//回転を設定する
	m_rotation.SetRotationYFromDirectionXZ(m_rotSpeed);
	m_model.SetRotation(m_rotation);
}

void Player::PlantBomb()
{
	if (g_pad[m_playerNo]->IsTrigger(enButtonA))
	{
		//爆弾を設置する
		m_bombInfo->PlantBomb(m_playerNo);
	}
}

void Player::OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName)
{

}