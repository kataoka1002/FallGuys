#include "stdafx.h"
#include "PlayerIdleState.h"
#include "PlayerWalkState.h"

PlayerIdleState::~PlayerIdleState()
{

}

void PlayerIdleState::Enter()
{
	// �Đ�����A�j���[�V������ݒ�B
	m_player->SetAnimation(Player::enAnimClip_Idle, 0.2f);
}

IPlayerState* PlayerIdleState::StateChange()
{
	//�X�e�B�b�N�̓��͗ʂɂ���ăX�e�[�g��ύX
	if (g_pad[0]->GetLStickXF() != 0.000f || g_pad[0]->GetLStickYF() != 0.000f)
	{
		// �����X�e�[�g�ɑJ�ڂ���
		return new PlayerWalkState(m_player);
	}

	// �����܂ŗ�����X�e�[�g��J�ڂ��Ȃ��B
	return nullptr;
}

void PlayerIdleState::Update()
{
	//���e�̐ݒu
	m_player->PlantBomb();
}