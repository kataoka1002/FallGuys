#pragma once
class WoodBlockRender;
class Game;

class WoodBlock : public IGameObject
{
public:
	WoodBlock();
	~WoodBlock();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

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
	WoodBlockRender*		m_woodBlockRender = nullptr;	// グレーブロックレンダー。
	Game*					m_game = nullptr;
};