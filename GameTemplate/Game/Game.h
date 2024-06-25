#pragma once

#include "Level3DRender/LevelRender.h"
#include "Stage.h"

class Player;
class Stage;
class Bomb;
class BombInformation;

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

private:
	Stage* m_stage = nullptr;
	Player* m_player0 = nullptr;
	Player* m_player1 = nullptr;
	BombInformation* m_bombInfo = nullptr;
	SkyCube* m_skyCube = nullptr;

	Vector3 m_camerapos = { 0.0f, 815.0f, -220.0f };
};

