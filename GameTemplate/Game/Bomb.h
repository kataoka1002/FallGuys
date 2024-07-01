#pragma once
#include "ItemBase.h"
class BombInformation;
class Player;

class Bomb : public ItemBase
{
public:
	Bomb();
	~Bomb();
	void Update();

	void InitModel() override;

	void SwellingModel();
	void FuseTime();
	void ResetBomb();
	void Explosion();

	void SetBombPosition(Vector3& pos)
	{
		m_position = pos;
	}
	
	void SetBombNumber(int num)
	{
		m_bombNumber = num;
	}

	void SetBomb()
	{
		m_isSetBomb = true;
	}

	void ExplosionBomb()
	{
		m_isSetBomb = false;
	}

	bool GetIsSetBomb()
	{
		return m_isSetBomb;
	}

	void SetParentPlayer(Player* player)
	{
		m_parentPlayer = player;
	}

	void SetBombInfomation(BombInformation* bombInfo)
	{
		m_bombInfo = bombInfo;
	}

	/// <summary>
	/// �v���C���[�̃|�C���^��ݒ肷��
	/// </summary>
	/// <param name="player0"></param>
	/// <param name="player1"></param>
	/// <param name="player2"></param>
	/// <param name="player3"></param>
	void SetPlayerPtr(Player* player0 = nullptr, Player* player1 = nullptr, Player* player2 = nullptr, Player* player3 = nullptr)
	{
		m_player[0] = player0;
		m_player[1] = player1;
		m_player[2] = player2;
		m_player[3] = player3;
	}

private:
	BombInformation*	m_bombInfo = nullptr;
	Player*				m_player[4] = { nullptr ,nullptr ,nullptr ,nullptr };
	Player*				m_parentPlayer = nullptr;		//�e�v���C���[
	Vector3				m_moveSpeed = Vector3::Zero;	//�ړ����x
	float				m_degree = 0.0f;				//�p�x
	float				m_timer = 0.0f;					//�^�C�}�[
	int					m_bombNumber = 0;				//���e�̔ԍ�
	bool				m_isSetBomb = false;			//���e��ݒu���Ă��邩�ǂ���

};