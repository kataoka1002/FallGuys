#pragma once
class YellowBlockRender;
class Game;

class YellowBlock : public IGameObject
{
public:
	YellowBlock();
	~YellowBlock();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	void SetStaticObject(int num);

	void SetTRS(Vector3 pos, Quaternion rot, Vector3 scale)
	{
		m_position = pos;
		m_rotation = rot;
		m_scale = scale;
	}

	void SetInstanceNo(int num)
	{
		m_instanceNo = num;
	}

private:
	int						m_instanceNo = 0;				// インスタンス番号。
	Vector3					m_position;						// 座標。
	Vector3					m_scale;						// 大きさ。
	Quaternion				m_rotation;						// 回転。
	YellowBlockRender*		m_yellowBlockRender = nullptr;	// 黄色ブロックレンダー。
	Game*					m_game = nullptr;
	PhysicsStaticObject		m_phyStaticObject;				// 静的物理オブジェクト
};