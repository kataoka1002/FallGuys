#include "stdafx.h"
#include "BombInformation.h"
#include "Bomb.h"
#include "Stage.h"
#include "Player.h"

BombInformation::BombInformation()
{

}

BombInformation::~BombInformation()
{

}

bool BombInformation::Start()
{	
	m_stage = FindGO<Stage>("stage");
	
	//���e��u����ꏊ�̎擾
	m_bombPoint = m_stage->GetBombPoint();

	//�ǂɂȂ�u���b�N�̍��W�̎擾
	m_wallBlockPositionList = m_stage->GetWallBlockPositionList();

	//���e��20����
	int bombNum = 0;
	for (int i = 0; i < 20; i++)
	{
		m_bomb = NewGO<Bomb>(0, "bomb");
		m_bomb->SetBombNumber(bombNum);
		m_bomb->SetPlayerPtr(m_player[0], m_player[1]);
		m_bomb->SetBombInfomation(this);

		if (bombNum >= 0 && bombNum < 5)
		{
			//�e�v���C���[�̐ݒ�
			m_bomb->SetParentPlayer(m_player[0]);

			//���X�g�ɒǉ�
			m_bombs1P.emplace_back(m_bomb);
		}
		else if (bombNum >= 5 && bombNum < 10)
		{
			//�e�v���C���[�̐ݒ�
			m_bomb->SetParentPlayer(m_player[1]);

			//���X�g�ɒǉ�
			m_bombs2P.emplace_back(m_bomb);
		}
		else if (bombNum >= 10 && bombNum < 15)
		{
			//�e�v���C���[�̐ݒ�
			m_bomb->SetParentPlayer(m_player[2]);

			//���X�g�ɒǉ�
			m_bombs3P.emplace_back(m_bomb);
		}
		else if (bombNum >= 15 && bombNum < 20)
		{
			//�e�v���C���[�̐ݒ�
			m_bomb->SetParentPlayer(m_player[3]);

			//���X�g�ɒǉ�
			m_bombs4P.emplace_back(m_bomb);
		}

		bombNum++;
	}

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

	if (num == 0)
	{
		//���e��ݒu����
		SetBombAtPosition(m_bombs1P, plantingPosition);
	}
	else if (num == 1)
	{
		//���e��ݒu����
		SetBombAtPosition(m_bombs2P, plantingPosition);
	}
	else if (num == 2)
	{
		//���e��ݒu����
		SetBombAtPosition(m_bombs3P, plantingPosition);
	}
	else if (num == 3)
	{
		//���e��ݒu����
		SetBombAtPosition(m_bombs4P, plantingPosition);
	}
}

void BombInformation::SetBombAtPosition(std::vector<Bomb*>& bombList, Vector3& pos)
{
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
			//���e�̃|�W�V�������X�V
			bomb->SetBombPosition(pos);

			//�Z�b�g����
			bomb->SetBomb();

			break;
		}
	}
}

void BombInformation::Render(RenderContext& rc)
{

}