#pragma once
#include "ItemBase.h"

class WalkSpeedUp : public ItemBase
{
public:
	WalkSpeedUp();
	~WalkSpeedUp();
	void Update();
	void InitModel() override;
private:
};

