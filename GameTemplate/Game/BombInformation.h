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
	/// ���e��ݒu����ꏊ�����߂�
	/// </summary>
	/// <param name="num">�v���C���[�̃i���o�[</param>
	void PlantBomb(int num);

	/// <summary>
	/// ���e��ݒu����
	/// </summary>
	/// <param name="bombList">���e�̃��X�g</param>
	/// <param name="pos">�ݒu�ꏊ</param>
	void SetBombAtPosition(std::vector<Bomb*>& bombList, Vector3& pos);

	/// <summary>
	/// �v���C���[�̃|�C���^��ݒ肷��
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
};