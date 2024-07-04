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

	/// <summary>
	/// 爆弾を設置する場所を決める
	/// </summary>
	/// <param name="num">プレイヤーのナンバー</param>
	void PlantBomb(int num);

	/// <summary>
	/// 爆弾を設置する
	/// </summary>
	/// <param name="bombList">爆弾のリスト</param>
	/// <param name="pos">設置場所</param>
	void SetBombAtPosition(std::vector<Bomb*>& bombList, Vector3& pos, int& playerNum);

	/// <summary>
	/// プレイヤーのポインタを設定する
	/// </summary>
	/// <param name="player0"></param>
	/// <param name="player1"></param>
	/// <param name="player2"></param>
	/// <param name="player3"></param>
	void SetPlayerPtr(Player* player0 = nullptr, Player* player1 = nullptr, Player* player2 = nullptr, Player* player3 = nullptr)
	{
		m_player[0] = player0;
		m_player[1] = player1;
		m_player[2] = player2;
		m_player[3] = player3;
	}

	const std::vector<Vector3>& GetWallBlockPositionList()
	{
		return m_wallBlockPositionList;
	}

	/// <summary>
	/// 設置している爆弾の数を減少させる
	/// </summary>
	/// <param name="bombNum"></param>
	void DecreaseBombCount(int& bombNum);

	/// <summary>
	/// 置ける爆弾の個数を増やす(最大5個)
	/// </summary>
	void LevelUpBombCount(int& playerNum);

private:
	Bomb* m_bomb = nullptr;
	Stage* m_stage = nullptr;
	Player* m_player[4] = { nullptr,nullptr,nullptr,nullptr };
	std::vector<Bomb*> m_bombs1P;
	std::vector<Bomb*> m_bombs2P;
	std::vector<Bomb*> m_bombs3P;
	std::vector<Bomb*> m_bombs4P;
	std::vector<Vector3> m_bombPoint;
	std::vector<Vector3> m_wallBlockPositionList;
	std::vector<Vector3> m_bombPlantedPosition;
	int m_maxBombCount1P = 0;
	int m_maxBombCount2P = 0;
	int m_maxBombCount3P = 0;
	int m_maxBombCount4P = 0;
	int m_plantBombCount1P = 0;
	int m_plantBombCount2P = 0;
	int m_plantBombCount3P = 0;
	int m_plantBombCount4P = 0;
};