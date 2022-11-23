#include "BlockManager.h"

void BlockManager::Initialize()
{
	blocks_[0].Initialize(Front);
	blocks_[1].Initialize(Right);
	blocks_[2].Initialize(Back);
	blocks_[3].Initialize(Left);

	SetBlocks();
}

void BlockManager::SetBlocks()
{
	for (size_t i = 0; i < 1; i++)
	{
		blocks_[Front].Add({ POLE_RAD,0.0f });//, { POLE_RAD - 1.0f,1.0f,1.0f });
		blocks_[Right].Add({ POLE_RAD,0.0f });//, { 1.0f,1.0f,POLE_RAD + 1.0f });
		blocks_[Back].Add({ POLE_RAD,0.0f });// , { POLE_RAD - 1.0f,1.0f,1.0f });
		blocks_[Left].Add({ POLE_RAD,0.0f });//, { 1.0f,1.0f,POLE_RAD + 1.0f });
	}
}

void BlockManager::Draw(ViewProjection viewProjection)
{
	for (Block& block : blocks_) { block.Draw(viewProjection); }
}
