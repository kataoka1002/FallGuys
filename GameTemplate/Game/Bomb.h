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
	Vector3		m_moveSpeed = Vector3::Zero;	//移動速度
	float		m_degree = 0.0f;				//角度
	float		m_timer = 0.0f;					//タイマー
	int			m_bombNumber = 0;				//爆弾の番号
	bool		m_isSetBomb = false;			//爆弾を設置しているかどうか
};