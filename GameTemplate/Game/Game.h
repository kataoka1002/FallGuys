#pragma once

#include "Level3DRender/LevelRender.h"
#include "Stage.h"

class Player;
class Stage;

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

	ModelRender m_modelRender;
	Vector3 m_pos;

	Vector3 m_camerapos = { 0.0f, 815.0f, -220.0f };
};

