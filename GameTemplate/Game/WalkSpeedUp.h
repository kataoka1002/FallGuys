#pragma once
#include "ItemBase.h"

class WalkSpeedUp : public ItemBase
{
public:
	WalkSpeedUp();
	~WalkSpeedUp();
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