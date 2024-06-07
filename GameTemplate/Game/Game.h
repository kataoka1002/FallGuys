#pragma once

#include "Level3DRender/LevelRender.h"

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

private:
	Stage* m_stage = nullptr;

	ModelRender m_modelRender;
	Vector3 m_pos;

	Vector3 m_camerapos = { 0.0f,660.0f,-350.0f };
};

