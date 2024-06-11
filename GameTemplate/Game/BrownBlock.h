#pragma once
class BrownBlockRender;
class Game;

class BrownBlock : public IGameObject
{
public:
	BrownBlock();
	~BrownBlock();
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
	ModelRender				m_modelRender;					// モデルレンダー。
	BrownBlockRender*		m_brownBlockRender = nullptr;	// グレーブロックレンダー。
	Game*					m_game = nullptr;
	PhysicsStaticObject		m_phyStaticObject;				// 静的物理オブジェクト
};