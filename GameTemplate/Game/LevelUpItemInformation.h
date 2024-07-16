#pragma once
class FirePowerUp;
class WalkSpeedUp;
class BombCountUp;
class Stage;

class LevelUpItemInformation : public IGameObject
{
public:
	LevelUpItemInformation();
	~LevelUpItemInformation();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
private:
	std::vector<FirePowerUp*> m_firePowerUpList;
	std::vector<WalkSpeedUp*> m_walkSpeedUpList;
	std::vector<BombCountUp*> m_bombCountUpList;
	std::vector<Vector3> m_itemPointList;

	Stage* m_stage = nullptr;
};

