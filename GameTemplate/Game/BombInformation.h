#pragma once
class Bomb;
class Stage;
class Player;

class BombInformation : public IGameObject
{
public: 
	BombInformation();
	~BombInformation();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	void PlantBomb(int num);

private:
	Bomb* m_bomb = nullptr;
	Stage* m_stage = nullptr;
	Player* m_player = nullptr;
	std::vector<Bomb*> m_bombs1P;
	std::vector<Bomb*> m_bombs2P;
	std::vector<Bomb*> m_bombs3P;
	std::vector<Bomb*> m_bombs4P;
	std::vector<Vector3> m_bombPoint;
	std::vector<Vector3> m_bombPlantedPosition;
};