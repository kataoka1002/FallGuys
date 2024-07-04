#pragma once
#include "ItemBase.h"

class FirePowerUp : public ItemBase
{
public:
	FirePowerUp();
	~FirePowerUp();
	void Update();
	void InitModel() override;
private:
};

