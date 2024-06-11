#include "stdafx.h"
#include "PlayerWalkState.h"
#include "PlayerIdleState.h"

PlayerWalkState::~PlayerWalkState()
{

}

void PlayerWalkState::Enter()
{
	// 再生するアニメーションを設定。
	//m_player->SetAnimation(Player::enAnimClip_Walk, 0.2f);
}

IPlayerState* PlayerWalkState::StateChange()
{
	if (g_pad[0]->GetLStickXF() == 0.000f || g_pad[0]->GetLStickYF() == 0.000f)
	{
		// アイドルステートに遷移する
		return new PlayerIdleState(m_player);
	}

	// ここまで来たらステートを遷移しない。
	return nullptr;
}

void PlayerWalkState::Update()
{
	// 移動処理。
	m_player->Move();

	// 回転処理。
	m_player->Turn();
}