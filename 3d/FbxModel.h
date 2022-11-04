#pragma once
#include <string>
#include <vector>
#include "Vector3.h"
#include "Matrix4.h"

struct Node
{
	std::string name;
	Vector3 scaling = { 1,1,1 },
		rotation{},
		translation{};
	Matrix4 transform, globalTransform;
	Node* parent = nullptr;
};

class FbxModel
{
private:
	std::string name;
	std::vector<Node> nodes;
public:
	friend class FbxLoader;
};