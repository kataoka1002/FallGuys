#include "stdafx.h"
#include "Stage.h"
#include "GrayBlock.h"
#include "GrayBlockRender.h"
#include "BrownBlock.h"
#include "BrownBlockRender.h"
#include "WoodBlock.h"
#include "WoodBlockRender.h"
#include "YellowBlock.h"
#include "YellowBlockRender.h"

namespace
{
	//ブロックの大きさ
	float BLOCK_WIDE = 60.0f;
	float BLOCK_HEIGHT = 60.0f;

	//ステージの大きさ
	int STAGE_SIZE_X = 15;
	int STAGE_SIZE_Y = 13;
}

Stage::Stage()
{

}

Stage::~Stage()
{
	//グレーのブロックを消す
	for (auto block : m_grayBlocks)
	{
		DeleteGO(block);
	}
	DeleteGO(m_grayBlockRender);

	//茶色のブロックを消す
	for (auto block : m_brownBlocks)
	{
		DeleteGO(block);
	}
	DeleteGO(m_brownBlockRender);

	//木のブロックを消す
	for (auto block : m_woodBlocks)
	{
		DeleteGO(block);
	}
	DeleteGO(m_woodBlockRender);

	//黄色のブロックを消す
	for (auto block : m_yellowBlocks)
	{
		DeleteGO(block);
	}
	DeleteGO(m_yellowBlockRender);
}

bool Stage::Start()
{
	//ブロックの配置
	for (int y = 0; y < STAGE_SIZE_Y; ++y)
	{
		for (int x = 0; x < STAGE_SIZE_X; ++x)
		{
			//1段目ブロックのポジションの設定
			Vector3 pos;
			pos.x = BLOCK_WIDE * x - (BLOCK_WIDE * STAGE_SIZE_X) / 2 + BLOCK_WIDE / 2;
			pos.y = -60.0f;
			pos.z = BLOCK_WIDE * y - (BLOCK_WIDE * STAGE_SIZE_Y) / 2 + BLOCK_WIDE / 2;

			//1段目ブロックの設置
			SetBlock(pos, m_stageData[STAGE_SIZE_Y - 1 - y][x]);

			//2段目のブロックの位置を設定
			pos.y = 0.0f;

			//2段目ブロックの設置
			SetBlock(pos, m_stageData2[STAGE_SIZE_Y - 1 - y][x]);
		}
	}

	//レンダラーの作成
	if (m_maxGrayBlock != 0)
	{
		m_grayBlockRender = NewGO<GrayBlockRender>(0, "grayblockrender");
		m_grayBlockRender->SetMaxBlock(m_maxGrayBlock);
	}

	if (m_maxBrownBlock != 0)
	{
		m_brownBlockRender = NewGO<BrownBlockRender>(0, "brownblockrender");
		m_brownBlockRender->SetMaxBlock(m_maxBrownBlock);
	}

	if (m_maxWoodBlock != 0)
	{
		m_woodBlockRender = NewGO<WoodBlockRender>(0, "woodblockrender");
		m_woodBlockRender->SetMaxBlock(m_maxWoodBlock);
	}

	if (m_maxYellowBlock != 0)
	{
		m_yellowBlockRender = NewGO<YellowBlockRender>(0, "yellowblockrender");
		m_yellowBlockRender->SetMaxBlock(m_maxYellowBlock);
	}

	return true;
}

void Stage::Update()
{
	
}

void Stage::SetBlock(Vector3& pos, int& stageData)
{
	//ブロックの設置
	if (stageData == 0)
	{
		//配置座標、スケール、回転を設定し生成。
		auto grayBlock = NewGO<GrayBlock>(0);
		grayBlock->SetTRS(pos, g_quatIdentity, Vector3::One);
		grayBlock->SetInstanceNo(m_maxGrayBlock);

		//ブロックの数を数える。
		m_maxGrayBlock++;
		m_grayBlocks.push_back(grayBlock);

		//壁になるブロックの座標を保存
		m_wallBlockPositionList.emplace_back(pos);
	}
	else if (stageData == 1)
	{
		//配置座標、スケール、回転を設定し生成。
		auto brownBlock = NewGO<BrownBlock>(0);
		brownBlock->SetTRS(pos, g_quatIdentity, Vector3::One);
		brownBlock->SetInstanceNo(m_maxBrownBlock);

		//ブロックの数を数える。
		m_maxBrownBlock++;
		m_brownBlocks.push_back(brownBlock);

		//壁になるブロックの座標を保存
		m_wallBlockPositionList.emplace_back(pos);
	}
	else if (stageData == 2)
	{
		//配置座標、スケール、回転を設定し生成。
		auto woodBlock = NewGO<WoodBlock>(0);
		woodBlock->SetTRS(pos, g_quatIdentity, Vector3::One);
		woodBlock->SetInstanceNo(m_maxWoodBlock);

		//ブロックの数を数える。
		m_maxWoodBlock++;
		m_woodBlocks.push_back(woodBlock);

		//壁になるブロックの座標を保存
		m_wallBlockPositionList.emplace_back(pos);
	}
	else if (stageData == 3)
	{
		//配置座標、スケール、回転を設定し生成。
		auto yellowBlock = NewGO<YellowBlock>(0);
		yellowBlock->SetTRS(pos, g_quatIdentity, Vector3::One);
		yellowBlock->SetInstanceNo(m_maxYellowBlock);

		//ブロックの数を数える。
		m_maxYellowBlock++;
		m_yellowBlocks.push_back(yellowBlock);

		//壁になるブロックの座標を保存
		m_wallBlockPositionList.emplace_back(pos);
	}
	else if (stageData == 4)
	{
		//爆弾を置ける場所を保存
		m_bombPoint.push_back(pos);
	}
}

void Stage::SetStaticObject(int& blockNum)
{
	if (blockNum == 1)
	{
		int num = 0;
		for (auto block : m_yellowBlocks)
		{
			block->SetStaticObject(num);
			num++;
		}
	}
	else if (blockNum == 2)
	{
		int num = 0;
		for (auto block : m_brownBlocks)
		{
			block->SetStaticObject(num);
			num++;
		}
	}
	else if (blockNum == 3)
	{
		int num = 0;
		for (auto block : m_grayBlocks)
		{
			block->SetStaticObject(num);
			num++;
		}
	}
	else if (blockNum == 4)
	{
		int num = 0;
		for (auto block : m_woodBlocks)
		{
			block->SetStaticObject(num);
			num++;
		}
	}
}

void Stage::Render(RenderContext& rc)
{
	
}