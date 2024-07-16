#pragma once
#include "ItemBase.h"

class FirePowerUp : public ItemBase
{
public:
	FirePowerUp();
	~FirePowerUp();
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

