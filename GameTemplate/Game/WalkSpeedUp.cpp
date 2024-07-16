#include "stdafx.h"
#include "WalkSpeedUp.h"
#include "Player.h"
#include "Game.h"

WalkSpeedUp::WalkSpeedUp()
{

}

WalkSpeedUp::~WalkSpeedUp()
{

}

void WalkSpeedUp::Update()
{
	//�A�C�e���ɓ����������ǂ����̏���
	CalcHitItem();

	//�R���W�����̈ʒu��ύX
	m_collisionObject->SetPosition(m_position);

	//���f���̏��̍X�V
	m_model.SetPosition(m_position);
	m_model.SetRotation(m_rotation);
	m_model.SetScale(m_scale);
	m_model.Update();
}

void WalkSpeedUp::InitModel()
{
	//���f���̏�����
	m_model.Init("Assets/modelData/item/shoe.tkm");
	m_model.SetPosition(m_position);
	m_model.SetRotation(m_rotation);
	m_model.SetScale(m_scale);
	m_model.Update();

	//�R���W�����I�u�W�F�N�g���쐬����B
	m_collisionObject = NewGO<CollisionObject>(0);

	//����̃R���W�������쐬����B
	m_collisionObject->CreateSphere(
		m_position,				//���W
		Quaternion::Identity,	//��]
		25.0f					//���a
	);

	//�R���W�����I�u�W�F�N�g�������ō폜����Ȃ��悤�ɂ���
	m_collisionObject->SetIsEnableAutoDelete(false);
}

void WalkSpeedUp::CalcHitItem()
{
	//�v���C���[�̃��X�g�̎擾
	for (auto player : m_game->GetPlayerList())
	{
		//�v���C���[���A�C�e���̃R���W�����ɂԂ�������
		if (m_collisionObject->IsHit(player->GetCharaCon()))
		{
			//�����X�s�[�h���グ��
			player->LevelUpWalkSpeed();

			//�����Ȃ��ʒu�Ɉړ�������
			m_position = Vector3{ 0.0f,-200.0f,0.0f };

			//���ꂽ��Ԃɂ���
			m_isTaken = true;

			break;
		}
	}
}