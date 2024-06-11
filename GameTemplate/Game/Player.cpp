#include "stdafx.h"
#include "Player.h"
#include "IPlayerState.h"
#include "PlayerIdleState.h"

namespace
{
	//�����X�s�[�h
	const float WALK_SPEED = 100.0f;

	//�L�����R���̍���
	const float CHARACON_HEIGHT = 50.0f;

	//�L�����R���̔��a
	const float CHARACON_RADIUS = 10.0f;
}

Player::Player()
{

}

Player::~Player()
{

}

void Player::Update()
{
	// �A�j���[�V�������Đ�����B
	//PlayAnimation(m_currentAnimationClip);

	// �X�e�[�g��ύX���邩
	IPlayerState* playerState = m_playerState->StateChange();

	// �ύX��̃X�e�[�g���ݒ肳��Ă���Ȃ��
	if (playerState != nullptr)
	{
		// �X�e�[�g��ύX����B
		delete m_playerState;
		m_playerState = playerState;
		m_playerState->Enter();
	}

	// �e�X�e�[�g�̍X�V���������s�B
	m_playerState->Update();

	// ���f�����X�V����B
	m_model.Update();
}

void Player::InitModel()
{
	//���f���̏�����
	m_model.Init("Assets/modelData/player/player.tkm");
	m_model.SetPosition(m_position);
	m_model.SetRotation(m_rotation);
	m_model.SetScale(m_scale);
	m_model.Update();

	//�L�����N�^�[�R���g���[���[��������
	m_charaCon.Init(
		CHARACON_RADIUS,	//���a
		CHARACON_HEIGHT,	//����
		m_position			//���W
	);

	// �����X�e�[�g��ݒ�
	m_playerState = new PlayerIdleState(this);
	m_playerState->Enter();
}

void Player::Move()
{
	//�ړ����x�̏�����
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

	//���X�e�B�b�N�̓��͗ʂ��󂯎��
	LStick_x = g_pad[0]->GetLStickXF();
	LStick_y = g_pad[0]->GetLStickYF();

	//�I�u�W�F�N�g�ێ������ǂ����ŕ���������ς���
	float moveSpeed;
	moveSpeed = WALK_SPEED;

	//XZ�����̈ړ����x���N���A
	m_moveSpeed.x = LStick_x * moveSpeed;		//�E�����ւ̈ړ����x�����Z
	m_moveSpeed.z = LStick_y * moveSpeed;		//�������ւ̈ړ����x�����Z

	//�d�͂̐ݒ�
	m_moveSpeed.y -= 980.0f * g_gameTime->GetFrameDeltaTime();

	//�L�����N�^�[�R���g���[���[���g�p���č��W���X�V
	m_position = m_charaCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());

	if (m_charaCon.IsOnGround())
	{
		//�n�ʂɂ���
		m_moveSpeed.y = 0.0f;
	}

	//���W��ݒ�
	m_model.SetPosition(m_position);
}

void Player::Turn()
{
	//�ړ����x�����]�����߂�
	m_rotSpeed = Math::Lerp(g_gameTime->GetFrameDeltaTime() * 3.5f, m_rotSpeed, m_moveSpeed);

	//�O�����̐ݒ�
	m_forward = m_rotSpeed;
	m_forward.Normalize();

	//��]��ݒ肷��
	m_rotation.SetRotationYFromDirectionXZ(m_rotSpeed);
	m_model.SetRotation(m_rotation);
}