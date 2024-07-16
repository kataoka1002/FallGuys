#pragma once
#include "Level3DRender/LevelRender.h"
#include "Stage.h"

class Player;
class Stage;
class Bomb;
class BombInformation;
class LevelUpItemInformation;

class Game : public IGameObject
{
public:
	Game() {}
	~Game();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	void SetStaticObject(int& num)
	{
		m_stage->SetStaticObject(num);
	}

	std::vector<Player*> GetPlayerList()
	{
		return m_playerList;
	}

private:
	Stage* m_stage = nullptr;
	Player* m_player0 = nullptr;
	Player* m_player1 = nullptr;
	BombInformation* m_bombInfo = nullptr;
	SkyCube* m_skyCube = nullptr;
	LevelUpItemInformation* m_levelUpItemInfo = nullptr;

	Vector3 m_camerapos = { 0.0f, 815.0f, -220.0f };
	std::vector<Player*> m_playerList;
};