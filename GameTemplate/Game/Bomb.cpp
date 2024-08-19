#include "stdafx.h"
#include "Bomb.h"
#include "Player.h"
#include "BombInformation.h"
#include "Game.h"
#include "BrownBlock.h"

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

	//�����̋����̌�
	const float BOMB_EXPLOSION_ORIGINAL = 60.0f;
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
	//m_charaCon.SetRigidBodyPosition(m_position);
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
	//m_charaCon.Init(
	//	CHARACON_RADIUS,	//���a
	//	CHARACON_HEIGHT,	//����
	//	m_position			//���W
	//);
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

		//�ݒu���Ă��锚�e�̐�������������
		m_bombInfo->DecreaseBombCount(m_bombNumber);

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
	//����������ȏ�L���邩�ǂ���
	bool isExplosionSpreadingRight = true;
	bool isExplosionSpreadingLeft = true;
	bool isExplosionSpreadingUp = true;
	bool isExplosionSpreadingDown = true;

	//�u���b�N���󂵂����ǂ���
	bool isPreventRight = false;
	bool isPreventLeft = false;
	bool isPreventUp = false;
	bool isPreventDown = false;

	//���j���W���Ǘ����郊�X�g
	std::vector<Vector3> explosionPosList;

	//�X�e�[�^�X���̔��j������L�΂�
	for (int i = 0; i <= m_parentPlayer->GetExplosionPow(); i++)
	{
		//�㉺���E�̔�����ݒ�
		Vector3 rightExplosionPos = { m_position.x + (BOMB_EXPLOSION_ORIGINAL * i), m_position.y, m_position.z };
		Vector3 leftExplosionPos = { m_position.x - (BOMB_EXPLOSION_ORIGINAL * i), m_position.y, m_position.z };
		Vector3 upExplosionPos = { m_position.x, m_position.y, m_position.z + (BOMB_EXPLOSION_ORIGINAL * i) };
		Vector3 downExplosionPos = { m_position.x, m_position.y, m_position.z - (BOMB_EXPLOSION_ORIGINAL * i) };

		//�ǂɂȂ�u���b�N�ɂԂ��������ǂ���
		for (auto wallPos : m_bombInfo->GetWallBlockPositionList())
		{
			//�Ԃ������炱��ȏ�L����Ȃ��悤�ɕϐ���ύX����
			if (wallPos.x == rightExplosionPos.x && wallPos.y == rightExplosionPos.y && wallPos.z == rightExplosionPos.z)
			{
				isExplosionSpreadingRight = false;
				isPreventRight = true;
			}
			if (wallPos.x == leftExplosionPos.x && wallPos.y == leftExplosionPos.y && wallPos.z == leftExplosionPos.z)
			{
				isExplosionSpreadingLeft = false;
				isPreventLeft = true;
			}
			if (wallPos.x == upExplosionPos.x && wallPos.y == upExplosionPos.y && wallPos.z == upExplosionPos.z)
			{
				isExplosionSpreadingUp = false;
				isPreventUp = true;
			}
			if (wallPos.x == downExplosionPos.x && wallPos.y == downExplosionPos.y && wallPos.z == downExplosionPos.z)
			{
				isExplosionSpreadingDown = false;
				isPreventDown = true;
			}
		}

		//�u���b�N�������ďo�����󓴂����邩���`�F�b�N
		for (auto cavityPos : m_bombInfo->GetCavityPositionList())
		{
			//�������甚�����L����悤�ɕϐ���ύX����
			if (cavityPos.x == rightExplosionPos.x && cavityPos.y == rightExplosionPos.y && cavityPos.z == rightExplosionPos.z && isPreventRight == false)
			{
				isExplosionSpreadingRight = true;
			}
			if (cavityPos.x == leftExplosionPos.x && cavityPos.y == leftExplosionPos.y && cavityPos.z == leftExplosionPos.z && isPreventLeft == false)
			{
				isExplosionSpreadingLeft = true;
			}
			if (cavityPos.x == upExplosionPos.x && cavityPos.y == upExplosionPos.y && cavityPos.z == upExplosionPos.z && isPreventUp == false)
			{
				isExplosionSpreadingUp = true;
			}
			if (cavityPos.x == downExplosionPos.x && cavityPos.y == downExplosionPos.y && cavityPos.z == downExplosionPos.z && isPreventDown == false)
			{
				isExplosionSpreadingDown = true;
			}
		}

		//�󂹂�u���b�N�����邩���`�F�b�N����
		for (auto brown : m_bombInfo->GetBrownBlockList())
		{
			CheckForBrownBlock(brown, rightExplosionPos);
			CheckForBrownBlock(brown, leftExplosionPos);
			CheckForBrownBlock(brown, upExplosionPos);
			CheckForBrownBlock(brown, downExplosionPos);
		}

		//�����𔭐�������ꏊ�����X�g�ɒǉ�
		if (i == 0)
		{
			explosionPosList.emplace_back(m_position);
		}
		else
		{
			//�������L�����Ȃ���W��ǉ�
			if (isExplosionSpreadingRight == true)
			{
				explosionPosList.emplace_back(rightExplosionPos);
			}
			if (isExplosionSpreadingLeft == true)
			{
				explosionPosList.emplace_back(leftExplosionPos);
			}
			if (isExplosionSpreadingUp == true)
			{
				explosionPosList.emplace_back(upExplosionPos);
			}
			if (isExplosionSpreadingDown == true)
			{
				explosionPosList.emplace_back(downExplosionPos);
			}
		}
	}

	for (auto pos : explosionPosList)
	{
		//�G�t�F�N�g�̍Đ�
		EffectEmitter* m_effect = NewGO<EffectEmitter>(0);
		m_effect->Init(enEffectName_BombExplosion);
		m_effect->SetPosition(pos);
		m_effect->Play();
	}

	//�v���C���[4�l���`�F�b�N
	for (int j = 0; j < 4; j++)
	{
		//�v���C���[�����Ȃ��Ȃ�I���
		if (m_player[j] == nullptr)
		{
			break;
		}

		//�����ƃv���C���[�̈ʒu�֌W�̏���
		for (auto exPos : explosionPosList)
		{
			//��������v���C���[�܂ł̋��������߂�
			Vector3 toPlayer = m_player[j]->GetPosition() - exPos;
			float toPlayerDis = toPlayer.Length();

			//��苗���ȓ��Ȃ�
			if (toPlayerDis <= 30.0f)
			{
				//�v���C���[�͎��S����
				m_player[j]->DeadPlayer();
			}
		}
	}
}

void Bomb::CheckForBrownBlock(BrownBlock* brownBlock, Vector3& exPos)
{
	//�󂹂�u���b�N����������
	if (brownBlock->GetPosition().x == exPos.x && brownBlock->GetPosition().y == exPos.y && brownBlock->GetPosition().z == exPos.z)
	{
		//���X�ǔ��肾�������W���󓴂ɕύX
		for (auto wallPos : m_bombInfo->GetWallBlockPositionList())
		{
			if (wallPos.x == brownBlock->GetPosition().x && wallPos.y == brownBlock->GetPosition().y && wallPos.z == brownBlock->GetPosition().z)
			{
				//�󓴃��X�g�ɒǉ�
				m_bombInfo->AddCavityPosition(wallPos);

				//���e�ݒu�\���X�g�ɒǉ�
				m_bombInfo->AddBombPoint(wallPos);

				//���x���A�b�v�A�C�e���̐ݒu
				m_bombInfo->SetLevelUpItem(wallPos);
				
				//�u���b�N�̍폜
				DeleteGO(brownBlock);
			}
		}
	}
}