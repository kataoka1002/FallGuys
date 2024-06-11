#pragma once
#include "Character.h"
class IPlayerState;

class Player : public Character
{
public:
	Player();
	~Player();
	void Update();

	void InitModel() override;
	void Move()		 override;
	void Turn()		 override;

private:
	IPlayerState* m_playerState = nullptr;
};