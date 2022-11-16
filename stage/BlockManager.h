#pragma once
#include "Block.h"
#include <array>

class BlockManager
{
private:
	std::array<Block, 4> blocks_;

public:
	void Initialize();
	void SetBlocks();
	void Draw();
};
