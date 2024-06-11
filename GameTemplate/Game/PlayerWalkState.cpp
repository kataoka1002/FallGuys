#include "stdafx.h"
#include "PlayerWalkState.h"
#include "PlayerIdleState.h"

PlayerWalkState::~PlayerWalkState()
{

}

void PlayerWalkState::Enter()
{
	// �Đ�����A�j���[�V������ݒ�B
	//m_player->SetAnimation(Player::enAnimClip_Walk, 0.2f);
}

IPlayerState* PlayerWalkState::StateChange()
{
	if (g_pad[0]->GetLStickXF() == 0.000f || g_pad[0]->GetLStickYF() == 0.000f)
	{
		// �A�C�h���X�e�[�g�ɑJ�ڂ���
		return new PlayerIdleState(m_player);
	}

	// �����܂ŗ�����X�e�[�g��J�ڂ��Ȃ��B
	return nullptr;
}

void PlayerWalkState::Update()
{
	// �ړ������B
	m_player->Move();

	// ��]�����B
	m_player->Turn();
}