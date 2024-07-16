#pragma once
#include "ItemBase.h"

class BombCountUp : public ItemBase
{
public:
	BombCountUp();
	~BombCountUp();
	void Update();
	void InitModel() override;

	void CalcHitItem();

	const bool GetIsTaken()const
	{
		return m_isTaken;
	}
private:
	CollisionObject* m_collisionObject = nullptr;
	bool m_isTaken = false;
};