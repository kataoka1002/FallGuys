#pragma once
#include "ItemBase.h"
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

private:
	Player*		m_player = nullptr;
	Vector3		m_moveSpeed = Vector3::Zero;	//�ړ����x
	float		m_degree = 0.0f;				//�p�x
	float		m_timer = 0.0f;					//�^�C�}�[
	int			m_bombNumber = 0;				//���e�̔ԍ�
	bool		m_isSetBomb = false;			//���e��ݒu���Ă��邩�ǂ���
};