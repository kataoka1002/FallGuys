#pragma once
class Game;

class ItemBase : public IGameObject
{
public:
	//コンストラクタ
	ItemBase() {}
	//デストラクタ
	virtual ~ItemBase() {}

	bool Start();
	void Render(RenderContext& rc);

	virtual void InitModel() = 0;

	const Vector3& GetPosition() const
	{
		return m_position;
	}

	const void SetPosition(Vector3 pos)
	{
		m_position = pos;
	}

protected:
	Game*				m_game = nullptr;				// ゲーム
	ModelRender			m_model;						// モデル
	Vector3				m_position = {0.0f,-300.0f,0.0f};		// 座標
	//Vector3				m_scale = Vector3::One;			// 大きさ
	float				m_scale = 1.0f;
	Quaternion			m_rotation;						// クォータニオン
	//CharacterController m_charaCon;						// キャラクターコントローラー
};