#include "stdafx.h"
#include "PlayerIdleState.h"
#include "PlayerWalkState.h"

PlayerIdleState::~PlayerIdleState()
{

}

void PlayerIdleState::Enter()
{
	// 再生するアニメーションを設定。
	m_player->SetAnimation(Player::enAnimClip_Idle, 0.2f);
}

IPlayerState* PlayerIdleState::StateChange()
{
	//スティックの入力量によってステートを変更
	if (g_pad[0]->GetLStickXF() != 0.000f || g_pad[0]->GetLStickYF() != 0.000f)
	{
		// 歩きステートに遷移する
		return new PlayerWalkState(m_player);
	}

	// ここまで来たらステートを遷移しない。
	return nullptr;
}

void PlayerIdleState::Update()
{
	//爆弾の設置
	m_player->PlantBomb();
}