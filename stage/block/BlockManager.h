#pragma once
#include "Block.h"
#include <array>

class BlockManager
{
private:
	std::array<Block,4> blocks_;
	
	void SetBlocks();
public:
	void Initialize();
	void Draw(ViewProjection viewProjection);
};