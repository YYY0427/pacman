#include "Field.h"
#include "../DrawFunctions.h"
#include <DxLib.h>

namespace
{
	//マップデータ
	int mapData[Field::MAP_HEIGHT][Field::MAP_WIDTH] =
	{
		{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
		{ 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2 },
		{ 2, 1, 2, 2, 1, 2, 2, 2, 1, 2, 1, 2, 2, 2, 1, 2, 2, 1, 2 },
		{ 2, 3, 2, 2, 1, 2, 2, 2, 1, 2, 1, 2, 2, 2, 1, 2, 2, 3, 2 },
		{ 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2 },
		{ 2, 1, 2, 2, 1, 2, 1, 2, 2, 2, 2, 2, 1, 2, 1, 2, 2, 1, 2 },
		{ 2, 1, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 1, 2 },
		{ 2, 2, 2, 2, 1, 2, 2, 2, 0, 2, 0, 2, 2, 2, 1, 2, 2, 2, 2 },
		{ 4, 4, 4, 2, 1, 2, 0, 0, 0, 0, 0, 0, 0, 2, 1, 2, 4, 4, 4 },
		{ 2, 2, 2, 2, 1, 2, 0, 2, 2, 0, 2, 2, 0, 2, 1, 2, 2, 2, 2 },
		{ 0, 0, 0, 0, 1, 0, 0, 2, 0, 0, 0, 2, 0, 0, 1, 0, 0, 0, 0 },
		{ 2, 2, 2, 2, 1, 2, 0, 2, 2, 2, 2, 2, 0, 2, 1, 2, 2, 2, 2 },
		{ 4, 4, 4, 2, 1, 2, 0, 0, 0, 0, 0, 0, 0, 2, 1, 2, 4, 4, 4 },
		{ 2, 2, 2, 2, 1, 2, 0, 2, 2, 2, 2, 2, 0, 2, 1, 2, 2, 2, 2 },
		{ 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2 },
		{ 2, 1, 2, 2, 1, 2, 2, 2, 1, 2, 1, 2, 2, 2, 1, 2, 2, 1, 2 },
		{ 2, 3, 1, 2, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 2, 1, 3, 2 },
		{ 2, 2, 1, 2, 1, 2, 1, 2, 2, 2, 2, 2, 1, 2, 1, 2, 1, 2, 2 },
		{ 2, 1, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 1, 2 },
		{ 2, 1, 2, 2, 2, 2, 2, 2, 1, 2, 1, 2, 2, 2, 2, 2, 2, 1, 2 },
		{ 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2 },
		{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
	};

	// 点滅スピード
	constexpr int FLASH_SPEED = 20;
}

Field::Field() :
	blendCount_(0),
	blendLimitMax_(false),
	isDraw_(true)
{
	handle_ = my::MyLoadGraph(L"Data/img/game/powerpacdot.png");
}

void Field::Updata()
{
	// パワーエサの点滅更新処理
	Flash();
}

void Field::Draw()
{
	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			// エサの描画
			if (mapData[y][x] == 1)
			{
				DrawFormatString(x * BLOCK_SIZE + 10 + DISPLAY_POS_X, y * BLOCK_SIZE + 10 + DISPLAY_POS_Y, 0xffffff, L"・", true);
			}
			// 壁の描画
			if (mapData[y][x] == 2)
			{
				DrawBox(
					x * BLOCK_SIZE + DISPLAY_POS_X, y * BLOCK_SIZE + DISPLAY_POS_Y,
					x * BLOCK_SIZE + BLOCK_SIZE + DISPLAY_POS_X, y * BLOCK_SIZE + BLOCK_SIZE + DISPLAY_POS_Y,
					GetColor(0, 0, 255), false);
			}
			// パワーエサの描画
			if (mapData[y][x] == 3)
			{
				PowerFeedFlash(y, x);
			}
			if (mapData2[y][x] >= 0)
			{
				DrawFormatString(x * BLOCK_SIZE + 10 + DISPLAY_POS_X, y * BLOCK_SIZE + 10 + DISPLAY_POS_Y, 0xffffff, L"%d", mapData2[y][x], true);
			}
		}
	}
}

// パワーエサの描画
void Field::PowerFeedFlash(int y, int x)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, blendCount_);
	DrawRotaGraph(x * BLOCK_SIZE + 16 + DISPLAY_POS_X, y * BLOCK_SIZE + 16 + DISPLAY_POS_Y, 1, 0, handle_, true);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

// パワーエサの点滅処理
void Field::Flash()
{
	//点滅
	if (blendLimitMax_)
	{
		blendCount_ += FLASH_SPEED;
		if (blendCount_ > 255)
			blendLimitMax_ = false;
	}
	else
	{
		blendCount_ -= FLASH_SPEED;
		if (blendCount_ < 0)
			blendLimitMax_ = true;
	}
}

// ゲームクリア判定
bool Field::IsGameClearCheck()
{
	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			if (mapData[y][x] == 1 || mapData[y][x] == 3)
			{
				return false;
			}
		}
	}
	return true;
}

// ブロックがあるかどうか
bool Field::IsBlock(int y, int x)
{
	if (mapData[y][x] == 2)	
		return true;
	
	return false;
}

// エサがあるかどうか
bool Field::IsFeed(int y, int x)
{
	if (mapData[y][x] == 1)
	{
		mapData[y][x] = 0;
		return true;
	}

	return false;
}

// パワーエサがあるかどうか
bool Field::IsPowerFeed(int y, int x)
{
	if (mapData[y][x] == 3)
	{
		mapData[y][x] = 0;
		return true;
	}
	return false;
}

int  Field::Worp(int ky, int kx, int indexY, int indexX)
{
	//前の座標が特定の位置かつ現在の座標が特定の位置ならワープ
	if (ky == 10 && kx == 1 && indexY == 10 && indexX == 0)
	{
		indexX = 18;
		
	}
	if (ky == 10 && kx == 17 && indexY == 10 && indexX == 18)
	{
		indexX = 0;
	}
	return (indexX);
}

void Field::MoveDataSet(int playerY, int playerX)
{
	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			if (mapData[y][x] != 2 && mapData[y][x] != 4)
			{
				mapData2[y][x] = 0;
			}
		}
	}

	mapData2[playerY][playerX] = 0;
	
	Search(playerY, playerX, 0);
}

void Field::Search(int y, int x, int pos)
{
	pos += 1;

	if (mapData2[y - 1][x] == 0 || mapData2[y - 1][x] > pos)
	{
		mapData2[y - 1][x] = pos;
		Search(y - 1, x, pos);
	}
	if (mapData2[y + 1][x] == 0 || mapData2[y + 1][x] > pos)
	{
		mapData2[y + 1][x] = pos;
		Search(y + 1, x, pos);
	}
	if (mapData2[y][x - 1] == 0 || mapData2[y][x - 1] > pos)
	{
		mapData2[y][x - 1] = pos;
		Search(y, x - 1, pos);
	}
	if (mapData2[y][x + 1] == 0 || mapData2[y][x + 1] > pos)
	{
		mapData2[y][x + 1] = pos;
		Search(y, x + 1, pos);
	}
	return;
}
