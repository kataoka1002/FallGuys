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
	//�u���b�N�̑傫��
	float BLOCK_WIDE = 60.0f;
	float BLOCK_HEIGHT = 60.0f;

	//�X�e�[�W�̑傫��
	int STAGE_SIZE_X = 15;
	int STAGE_SIZE_Y = 13;
}

Stage::Stage()
{

}

Stage::~Stage()
{
	//�O���[�̃u���b�N������
	for (auto block : m_grayBlocks)
	{
		DeleteGO(block);
	}
	DeleteGO(m_grayBlockRender);

	//���F�̃u���b�N������
	for (auto block : m_brownBlocks)
	{
		DeleteGO(block);
	}
	DeleteGO(m_brownBlockRender);

	//�؂̃u���b�N������
	for (auto block : m_woodBlocks)
	{
		DeleteGO(block);
	}
	DeleteGO(m_woodBlockRender);

	//���F�̃u���b�N������
	for (auto block : m_yellowBlocks)
	{
		DeleteGO(block);
	}
	DeleteGO(m_yellowBlockRender);
}

bool Stage::Start()
{
	//�u���b�N�̔z�u
	for (int y = 0; y < STAGE_SIZE_Y; ++y)
	{
		for (int x = 0; x < STAGE_SIZE_X; ++x)
		{
			//1�i�ڃu���b�N�̃|�W�V�����̐ݒ�
			Vector3 pos;
			pos.x = BLOCK_WIDE * x - (BLOCK_WIDE * STAGE_SIZE_X) / 2 + BLOCK_WIDE / 2;
			pos.y = -60.0f;
			pos.z = BLOCK_WIDE * y - (BLOCK_WIDE * STAGE_SIZE_Y) / 2 + BLOCK_WIDE / 2;

			//1�i�ڃu���b�N�̐ݒu
			SetBlock(pos, m_stageData[STAGE_SIZE_Y - 1 - y][x]);

			//2�i�ڂ̃u���b�N�̈ʒu��ݒ�
			pos.y = 0.0f;

			//2�i�ڃu���b�N�̐ݒu
			SetBlock(pos, m_stageData2[STAGE_SIZE_Y - 1 - y][x]);
		}
	}

	//�����_���[�̍쐬
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
	//�u���b�N�̐ݒu
	if (stageData == 0)
	{
		//�z�u���W�A�X�P�[���A��]��ݒ肵�����B
		auto grayBlock = NewGO<GrayBlock>(0);
		grayBlock->SetTRS(pos, g_quatIdentity, Vector3::One);
		grayBlock->SetInstanceNo(m_maxGrayBlock);

		//�u���b�N�̐��𐔂���B
		m_maxGrayBlock++;
		m_grayBlocks.push_back(grayBlock);

		//�ǂɂȂ�u���b�N�̍��W��ۑ�
		m_wallBlockPositionList.emplace_back(pos);
	}
	else if (stageData == 1)
	{
		//�z�u���W�A�X�P�[���A��]��ݒ肵�����B
		auto brownBlock = NewGO<BrownBlock>(0);
		brownBlock->SetTRS(pos, g_quatIdentity, Vector3::One);
		brownBlock->SetInstanceNo(m_maxBrownBlock);

		//�u���b�N�̐��𐔂���B
		m_maxBrownBlock++;
		m_brownBlocks.push_back(brownBlock);

		//�ǂɂȂ�u���b�N�̍��W��ۑ�
		m_wallBlockPositionList.emplace_back(pos);
	}
	else if (stageData == 2)
	{
		//�z�u���W�A�X�P�[���A��]��ݒ肵�����B
		auto woodBlock = NewGO<WoodBlock>(0);
		woodBlock->SetTRS(pos, g_quatIdentity, Vector3::One);
		woodBlock->SetInstanceNo(m_maxWoodBlock);

		//�u���b�N�̐��𐔂���B
		m_maxWoodBlock++;
		m_woodBlocks.push_back(woodBlock);

		//�ǂɂȂ�u���b�N�̍��W��ۑ�
		m_wallBlockPositionList.emplace_back(pos);
	}
	else if (stageData == 3)
	{
		//�z�u���W�A�X�P�[���A��]��ݒ肵�����B
		auto yellowBlock = NewGO<YellowBlock>(0);
		yellowBlock->SetTRS(pos, g_quatIdentity, Vector3::One);
		yellowBlock->SetInstanceNo(m_maxYellowBlock);

		//�u���b�N�̐��𐔂���B
		m_maxYellowBlock++;
		m_yellowBlocks.push_back(yellowBlock);

		//�ǂɂȂ�u���b�N�̍��W��ۑ�
		m_wallBlockPositionList.emplace_back(pos);
	}
	else if (stageData == 4)
	{
		//���e��u����ꏊ��ۑ�
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