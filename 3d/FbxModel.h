#pragma once
#include <string>
#include <vector>
#include <DirectXTex.h>
#include "Vector2.h"
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
public:
	struct VertexPosNormalUv
	{
		Vector3 pos, normal;
		Vector2 uv;
	};
private:
	std::string name;
	std::vector<Node> nodes;
	Node* meshNode = nullptr;
	std::vector<VertexPosNormalUv> vertices;
	std::vector<uint16_t> indices;
	Vector3 ambient = { 1,1,1 }, diffuse = { 1,1,1 };
	DirectX::TexMetadata metadata{};
	DirectX::ScratchImage scratchImg{};
public:
	friend class FbxLoader;
};