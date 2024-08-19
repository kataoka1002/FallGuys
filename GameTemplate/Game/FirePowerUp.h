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

	const bool GetIsSet()const
	{
		return m_isSet;
	}

	void SetIsSet()
	{
		m_isSet = true;
	}
private:
	CollisionObject* m_collisionObject = nullptr;
	bool m_isTaken = false;
	bool m_isSet = false;
};

