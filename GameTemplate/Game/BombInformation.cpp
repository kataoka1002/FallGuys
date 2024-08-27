#include "stdafx.h"
#include "BombInformation.h"
#include "Bomb.h"
#include "Stage.h"
#include "Player.h"
#include "LevelUpItemInformation.h"

namespace
{
	//�u���锚�e�̍ő吔
	const int MAX_BOMB_COUNT = 1;
}

BombInformation::BombInformation()
{
	//�u���锚�e�̍ő吔���Z�b�g
	m_maxBombCount1P = MAX_BOMB_COUNT;
	m_maxBombCount2P = MAX_BOMB_COUNT;
	m_maxBombCount3P = MAX_BOMB_COUNT;
	m_maxBombCount4P = MAX_BOMB_COUNT;
}

BombInformation::~BombInformation()
{
	for (auto bomb : m_bombs1P)
	{
		DeleteGO(bomb);
	}
	m_bombs1P.clear();

	for (auto bomb : m_bombs2P)
	{
		DeleteGO(bomb);
	}
	m_bombs2P.clear();

	for (auto bomb : m_bombs3P)
	{
		DeleteGO(bomb);
	}
	m_bombs3P.clear();

	for (auto bomb : m_bombs4P)
	{
		DeleteGO(bomb);
	}
	m_bombs4P.clear();
}

bool BombInformation::Start()
{	
	m_stage = FindGO<Stage>("stage");

	m_levelUpItemInfo = FindGO<LevelUpItemInformation>("levelupiteminformation");
	
	//���e��u����ꏊ�̎擾
	m_bombPoint = m_stage->GetBombPoint();

	//�󓴂̏ꏊ�̎擾
	m_cavityPositionList = m_stage->GetBombPoint();

	//�ǂɂȂ�u���b�N�̍��W�̎擾
	m_wallBlockPositionList = m_stage->GetWallBlockPositionList();

	//���F�u���b�N�̃��X�g���擾
	m_brownBlocks = m_stage->GetBrownBlockList();

	//���F�u���b�N�̍��W���X�g�̎擾
	m_brownBlockPositionList = m_stage->GetBrownBlockPositionList();

	//���e�̃��X�g���Ǘ�����z��
	//std::vector<std::unique_ptr<Bomb>> bombs[4] = { m_bombs1P ,m_bombs2P ,m_bombs3P ,m_bombs4P };
	std::vector<Bomb*> bombs[4] = { m_bombs1P ,m_bombs2P ,m_bombs3P ,m_bombs4P };

	//���e��20����
	int bombNum = 0;
	for (int i = 0; i < 20; i++)
	{
		m_bomb = NewGO<Bomb>(0, "bomb");
		m_bomb->SetBombNumber(bombNum);
		m_bomb->SetPlayerPtr(m_player[0], m_player[1]);
		m_bomb->SetBombInfomation(this);

		//���e�����ꂼ��̃��X�g�ɒǉ����Ă���
		if (bombNum >= 0 && bombNum < 20)
		{
			//�e�v���C���[�̐ݒ�
			int index = bombNum / 5;
			m_bomb->SetParentPlayer(m_player[index]);

			//���X�g�ɒǉ�
			bombs[index].emplace_back(m_bomb);
		}

		bombNum++;
	}

	//���X�g�̏��̍X�V
	m_bombs1P = bombs[0];
	m_bombs2P = bombs[1];
	m_bombs3P = bombs[2];
	m_bombs4P = bombs[3];

	//���̔z��̒��g����ɂ���
	bombs[0].clear();
	bombs[1].clear();
	bombs[2].clear();
	bombs[3].clear();

	return true;
}

void BombInformation::Update()
{
	
}

void BombInformation::PlantBomb(int num)
{
	//�v���C���[�̃|�W�V�������擾
	Vector3 playerPos = m_player[num]->GetPosition();

	//��ԋ߂��|�C���g�܂ł̋���
	float shortestDistance = 10000.0f;

	//���e��u���|�W�V����
	Vector3 plantingPosition = { 0.0f,0.0f,0.0f };

	for (auto point : m_bombPoint)
	{
		//�v���C���[�̃|�W�V��������|�C���g�܂ł̃x�N�g�������߂�
		Vector3 vec = point - playerPos;

		//���̃x�N�g���̒��������߂�
		float toPoint = vec.Length();

		//�ۑ����Ă������ŒZ���������������Ȃ�
		if (toPoint < shortestDistance)
		{
			//�ŒZ�������X�V����
			shortestDistance = toPoint;

			//���e��u���|�W�V�������X�V����
			plantingPosition = point;
		}
	}

	//���e�̃��X�g���Ǘ�����z��
	std::vector<Bomb*> bombs[4] = { m_bombs1P ,m_bombs2P ,m_bombs3P ,m_bombs4P };

	//���e�̐ݒu
	SetBombAtPosition(bombs[num], plantingPosition, num);
}

void BombInformation::SetBombAtPosition(std::vector<Bomb*>& bombList, Vector3& pos, int& playerNum)
{
	// �e�v���C���[�̐ݒu�������e�̐��ƍő�ݒu�����i�[����z��
	int m_plantBombCount[4] = { m_plantBombCount1P, m_plantBombCount2P, m_plantBombCount3P, m_plantBombCount4P };
	int m_maxBombCount[4] = { m_maxBombCount1P, m_maxBombCount2P, m_maxBombCount3P, m_maxBombCount4P };

	for (auto bomb : bombList)
	{
		//�ݒu����|�C���g�ɔ��e�����łɒu����Ă��Ȃ������m�F����
		if (pos.x == bomb->GetPosition().x &&
			pos.y == bomb->GetPosition().y &&
			pos.z == bomb->GetPosition().z)
		{
			break;
		}

		//�Z�b�g����ĂȂ����e�Ȃ�
		if (bomb->GetIsSetBomb() == false)
		{
			// �ݒu�������e�̌��𑝂₷
			if (playerNum >= 0 && playerNum < 4 && m_plantBombCount[playerNum] < m_maxBombCount[playerNum])
			{
				// ���e�̃|�W�V�������X�V
				bomb->SetBombPosition(pos);

				// �Z�b�g����
				bomb->SetBomb();

				// �ݒu���Ă��锚�e�̐��𑝂₷
				m_plantBombCount[playerNum]++;
			}

			break;
		}
	}

	// �e�v���C���[�̐ݒu�������e�̐����X�V
	m_plantBombCount1P = m_plantBombCount[0];
	m_plantBombCount2P = m_plantBombCount[1];
	m_plantBombCount3P = m_plantBombCount[2];
	m_plantBombCount4P = m_plantBombCount[3];
}

void BombInformation::DecreaseBombCount(int& bombNum)
{
	// �e�v���C���[�̔��e�J�E���g��z��ŊǗ�
	int* bombCounts[] = { &m_plantBombCount1P, &m_plantBombCount2P, &m_plantBombCount3P, &m_plantBombCount4P };

	// �Ή�����v���C���[�̔��e�J�E���g������������
	if (bombNum >= 0 && bombNum < 20)
	{
		int index = bombNum / 5;
		(*bombCounts[index])--;
	}
}

void BombInformation::LevelUpBombCount(int& playerNum)
{
	//�u���锚�e�̍ő�l�̔z��
	int* maxBombCount[4] = { &m_maxBombCount1P ,&m_maxBombCount2P ,&m_maxBombCount3P ,&m_maxBombCount4P };

	//�u���鐔�𑝂₷(�ő�5��)
	(*maxBombCount[playerNum])++;
	(*maxBombCount[playerNum]) = min((*maxBombCount[playerNum]), 5);
}

void BombInformation::SetLevelUpItem(Vector3& pos)
{
	//�A�C�e���̐ݒu
	m_levelUpItemInfo->SetLevelUpItem(pos);
}

void BombInformation::Render(RenderContext& rc)
{

}