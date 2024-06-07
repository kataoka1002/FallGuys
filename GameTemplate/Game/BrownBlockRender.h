#pragma once
class Game;

class BrownBlockRender : public IGameObject
{
public:

	bool Start();
	void Update();
	void Render(RenderContext& rc);

	/// <summary>
	/// ブロックの最大数を設定する。
	/// </summary>
	/// <param name="numBlock"></param>
	void SetMaxBlock(int maxBlock)
	{
		m_maxBlock = maxBlock;
	}

	/// <summary>
	/// インスタンシングデータの更新。
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="rot"></param>
	/// <param name="scale"></param>
	void UpdateInstancingData(
		int instanceNo,
		const Vector3& pos,
		const Quaternion& rot,
		const Vector3& scale)
	{
		m_modelRender.UpdateInstancingData(instanceNo, pos, rot, scale);
	}

	/// <summary>
	/// インスタンスを破棄。
	/// </summary>
	/// <param name="instanceNo">削除するインスタンスの番号</param>
	void RemoveInstance(int instanceNo)
	{
		m_modelRender.RemoveInstance(instanceNo);
	}

private:
	PhysicsStaticObject m_phyStaticObject;  //静的物理オブジェクト
	ModelRender			m_modelRender;		// モデルレンダラー。
	int					m_maxBlock = 0;		// ブロックの数
	Game*				m_game = nullptr;
};