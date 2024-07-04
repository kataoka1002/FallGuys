#pragma once
#include "ItemBase.h"

class BombCountUp : public ItemBase
{
public:
	BombCountUp();
	~BombCountUp();
	void Update();
	void InitModel() override;

private:
};