#include "stdafx.h"
#include "Bomb.h"
#include "Player.h"

namespace
{
	//�L�����R���̍���
	const float CHARACON_HEIGHT = 0.0f;

	//�L�����R���̔��a
	const float CHARACON_RADIUS = 25.0f;

	//�c���X�s�[�h
	const float SELLING_SPEED = 0.01f;

	//���e�̑ҋ@�ꏊ
	const Vector3 BOMB_WAITING_POS = { 0.0f,-150.0f,0.0f };

	//���e�̋N���܂ł̎���
	const float BOMB_FUSE_TIME = 3.0f;
}

Bomb::Bomb()
{
	
}

Bomb::~Bomb()
{

}

void Bomb::Update()
{
	//�g��k��
	SwellingModel();

	//�N���܂ł̎��Ԃ̏���
	FuseTime();

	//�L�����N�^�[�R���g���[���[���g�p���č��W���X�V
	//m_position = m_charaCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
	m_model.SetPosition(m_position);
	m_model.SetScale(m_scale);
	m_model.Update();
}

void Bomb::InitModel()
{
	//�����ʒu�͑ҋ@�ꏊ
	m_position = BOMB_WAITING_POS;

	//�^�C�}�[�̃Z�b�g
	m_timer = BOMB_FUSE_TIME;

	//���f���̏�����
	m_model.Init("Assets/modelData/item/bomb.tkm");
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
}

void Bomb::SwellingModel()
{
	//sin�g���g���Ċ��炩�ɑ傫����ω�������
	//�p�x��傫�����Ă���
	m_degree += 10.0f;

	//360�x��-1�`1���������̂�0�x�ɖ߂�
	if (m_degree >= 360.0f)
	{
		m_degree = 0.0f;
	}

	//�p�x�����W�A���ɕϊ�
	float rad = m_degree * 3.141592f / 180.0f;

	//sin�̒l�����߂�
	float sinValue = sin(rad);

	//�ŏI�I�Ȗc�����x�����߂�
	float sellingSpeed = SELLING_SPEED * sinValue;
	m_scale += sellingSpeed;
}

void Bomb::FuseTime()
{
	//�Z�b�g����Ă��Ȃ��Ȃ�Ԃ�
	if (m_isSetBomb == false)
	{
		return;
	}

	//���Ԍv��
	m_timer -= g_gameTime->GetFrameDeltaTime();

	if (m_timer <= 0.0f)
	{
		//����
		Explosion();

		//���e�̃��Z�b�g
		ResetBomb();
	}
}

void Bomb::ResetBomb()
{
	//�ҋ@�ꏊ�ɖ߂�
	m_position = BOMB_WAITING_POS;

	//�^�C�}�[�̃��Z�b�g
	m_timer = BOMB_FUSE_TIME;

	//�Z�b�g����Ă��Ȃ���Ԃɂ���
	m_isSetBomb = false;
}

void Bomb::Explosion()
{

}