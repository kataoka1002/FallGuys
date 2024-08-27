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
	//�ǃu���b�N�ɂԂ��������ǂ���
	bool isHitWallBlockRight = false;
	bool isHitWallBlockLeft = false;
	bool isHitWallBlockUp = false;
	bool isHitWallBlockDown = false;

	//���F�u���b�N���󂵂����ǂ���
	bool isRightBlockBreak = false;
	bool isLeftBlockBreak = false;
	bool isUpBlockBreak = false;
	bool isDownBlockBreak = false;

	//���F�u���b�N�ɂԂ��������ǂ���
	bool isHitBrownBlockRight = false;
	bool isHitBrownBlockLeft = false;
	bool isHitBrownBlockUp = false;
	bool isHitBrownBlockDown = false;

	//�����̊g����~�߂邩�ǂ���
	bool isStopExplosionRight = false;
	bool isStopExplosionLeft = false;
	bool isStopExplosionUp = false;
	bool isStopExplosionDown = false;

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

		//�󓴍��W�ɂԂ��������ǂ���
		bool isHitCavityPosRight = false;
		bool isHitCavityPosLeft = false;
		bool isHitCavityPosUp = false;
		bool isHitCavityPosDown = false;

		//�ǂɂȂ�u���b�N(���F�u���b�N�A�t���[���̃u���b�N)�ɂԂ��������ǂ���
		for (auto wallPos : m_bombInfo->GetWallBlockPositionList())
		{
			//�Ԃ������炱��ȏ�L����Ȃ��悤�ɕϐ���ύX����
			if (wallPos.x == rightExplosionPos.x && wallPos.y == rightExplosionPos.y && wallPos.z == rightExplosionPos.z)
			{
				isHitWallBlockRight = true;
			}
			if (wallPos.x == leftExplosionPos.x && wallPos.y == leftExplosionPos.y && wallPos.z == leftExplosionPos.z)
			{
				isHitWallBlockLeft = true;
			}
			if (wallPos.x == upExplosionPos.x && wallPos.y == upExplosionPos.y && wallPos.z == upExplosionPos.z)
			{
				isHitWallBlockUp = true;
			}
			if (wallPos.x == downExplosionPos.x && wallPos.y == downExplosionPos.y && wallPos.z == downExplosionPos.z)
			{
				isHitWallBlockDown = true;
			}
		}

		//�u���b�N�������ďo�����󓴂����邩���`�F�b�N
		for (auto cavityPos : m_bombInfo->GetCavityPositionList())
		{
			//�������甚�����L����悤�ɕϐ���ύX����
			if (cavityPos.x == rightExplosionPos.x && cavityPos.y == rightExplosionPos.y && cavityPos.z == rightExplosionPos.z)
			{
				isHitCavityPosRight = true;
			}
			if (cavityPos.x == leftExplosionPos.x && cavityPos.y == leftExplosionPos.y && cavityPos.z == leftExplosionPos.z)
			{
				isHitCavityPosLeft = true;
			}
			if (cavityPos.x == upExplosionPos.x && cavityPos.y == upExplosionPos.y && cavityPos.z == upExplosionPos.z)
			{
				isHitCavityPosUp = true;
			}
			if (cavityPos.x == downExplosionPos.x && cavityPos.y == downExplosionPos.y && cavityPos.z == downExplosionPos.z)
			{
				isHitCavityPosDown = true;
			}
		}

		if (i != 0)
		{
			//���F�u���b�N�ɂԂ��������ǂ���
			for (auto brownPos : m_bombInfo->GetBrownBlockPositionList())
			{
				//�Ԃ������炱��ȏ�L����Ȃ��悤�ɕϐ���ύX����
				if (brownPos.x == rightExplosionPos.x && brownPos.y == rightExplosionPos.y && brownPos.z == rightExplosionPos.z)
				{
					isHitBrownBlockRight = true;
				}
				if (brownPos.x == leftExplosionPos.x && brownPos.y == leftExplosionPos.y && brownPos.z == leftExplosionPos.z)
				{
					isHitBrownBlockLeft = true;
				}
				if (brownPos.x == upExplosionPos.x && brownPos.y == upExplosionPos.y && brownPos.z == upExplosionPos.z)
				{
					isHitBrownBlockUp = true;
				}
				if (brownPos.x == downExplosionPos.x && brownPos.y == downExplosionPos.y && brownPos.z == downExplosionPos.z)
				{
					isHitBrownBlockDown = true;
				}
			}
		}

		//���F�u���b�N�����邩���`�F�b�N����
		for (auto brown : m_bombInfo->GetBrownBlockList())
		{
			if (isRightBlockBreak == false && isHitWallBlockRight == false)
			{
				CheckForBrownBlock(brown, rightExplosionPos, isRightBlockBreak);
			}
			if (isLeftBlockBreak == false && isHitWallBlockLeft == false)
			{
				CheckForBrownBlock(brown, leftExplosionPos, isLeftBlockBreak);
			}
			if (isUpBlockBreak == false && isHitWallBlockUp == false)
			{
				CheckForBrownBlock(brown, upExplosionPos, isUpBlockBreak);
			}
			if (isDownBlockBreak == false && isHitWallBlockDown == false)
			{
				CheckForBrownBlock(brown, downExplosionPos, isDownBlockBreak);
			}
		}

		//�����𔭐�������ꏊ�����X�g�ɒǉ�
		if (i == 0)
		{
			explosionPosList.emplace_back(m_position);
		}
		else
		{
			//�������L�����Ȃ���W��ǉ�
			if (((isHitWallBlockRight == false && isHitBrownBlockRight == false) || (isHitWallBlockRight == false && isHitCavityPosRight == true)) && isStopExplosionRight == false)
			{
				explosionPosList.emplace_back(rightExplosionPos);
			}
			//�L����Ȃ��Ȃ甚�����~�߂�t���O�𗧂Ă�
			else if (isHitBrownBlockRight == true && isHitCavityPosRight == false)
			{
				isStopExplosionRight = true;
			}

			if (((isHitWallBlockLeft == false && isHitBrownBlockLeft == false) || (isHitWallBlockLeft == false && isHitCavityPosLeft == true)) && isStopExplosionLeft == false)
			{
				explosionPosList.emplace_back(leftExplosionPos);
			}
			else if (isHitBrownBlockLeft == true && isHitCavityPosLeft == false)
			{
				isStopExplosionLeft = true;
			}

			if (((isHitWallBlockUp == false && isHitBrownBlockUp == false) || (isHitWallBlockUp == false && isHitCavityPosUp == true)) && isStopExplosionUp == false)
			{
				explosionPosList.emplace_back(upExplosionPos);
			}
			else if (isHitBrownBlockUp == true && isHitCavityPosUp == false)
			{
				isStopExplosionUp = true;
			}

			if (((isHitWallBlockDown == false && isHitBrownBlockDown == false) || (isHitWallBlockDown == false && isHitCavityPosDown == true)) && isStopExplosionDown == false)
			{
				explosionPosList.emplace_back(downExplosionPos);
			}
			else if (isHitBrownBlockDown == true && isHitCavityPosDown == false)
			{
				isStopExplosionDown = true;
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

void Bomb::CheckForBrownBlock(BrownBlock* brownBlock, Vector3& exPos, bool& isBlockBreak)
{
	//���F�u���b�N����������
	if (brownBlock->GetPosition().x == exPos.x && brownBlock->GetPosition().y == exPos.y && brownBlock->GetPosition().z == exPos.z)
	{
		//���X�ǔ��肾�������F�u���b�N�̍��W���󓴂ɕύX
		for (auto brownBlockPos : m_bombInfo->GetBrownBlockPositionList())
		{
			if (brownBlockPos.x == brownBlock->GetPosition().x && brownBlockPos.y == brownBlock->GetPosition().y && brownBlockPos.z == brownBlock->GetPosition().z)
			{
				//�󓴃��X�g�ɒǉ�
				m_bombInfo->AddCavityPosition(brownBlockPos);

				//���e�ݒu�\���X�g�ɒǉ�
				m_bombInfo->AddBombPoint(brownBlockPos);

				//���x���A�b�v�A�C�e���̐ݒu
				m_bombInfo->SetLevelUpItem(brownBlockPos);
				
				//�u���b�N�̍폜
				DeleteGO(brownBlock);

				//�u���b�N�폜�ς�
				isBlockBreak = true;

				//�G�t�F�N�g�̍Đ�
				EffectEmitter* m_effect = NewGO<EffectEmitter>(0);
				m_effect->Init(enEffectName_BombExplosion);
				m_effect->SetPosition(brownBlockPos);
				m_effect->Play();
			}
		}
	}
}