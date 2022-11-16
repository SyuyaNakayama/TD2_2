#pragma once
#include <string>
#include <vector>
#include <DirectXTex.h>
#include <windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <d3dx12.h>
#include "Vector2.h"
#include "Vector3.h"
#include "Matrix4.h"
#include <fbxsdk.h>

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
	static const int MAX_BONE_INDICES = 4;
	struct VertexPosNormalUvSkin
	{
		Vector3 pos, normal;
		Vector2 uv;
		UINT boneIndex[MAX_BONE_INDICES];
		float boneWeight[MAX_BONE_INDICES];
	};

	struct Bone
	{
		std::string name;
		Matrix4 invInitialPose;
		FbxCluster* fbxCluster;

		Bone(const std::string& name) { this->name = name; }
	};
private:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using TexMetadata = DirectX::TexMetadata;
	using ScratchImage = DirectX::ScratchImage;
	using string = std::string;
	template <class T> using vector = std::vector<T>;

	ComPtr<ID3D12Resource> vertBuff, indexBuff, texBuff;
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	D3D12_INDEX_BUFFER_VIEW ibView{};
	ComPtr<ID3D12DescriptorHeap> descHeapSRV;

	string name;
	vector<Node> nodes;
	Node* meshNode = nullptr;
	vector<VertexPosNormalUvSkin> vertices;
	vector<uint16_t> indices;
	Vector3 ambient = { 1,1,1 }, diffuse = { 1,1,1 };
	TexMetadata metadata{};
	ScratchImage scratchImg{};
	vector<Bone> bones;
	FbxScene* fbxScene = nullptr;

	template<class T> ID3D12Resource* CreateBuffer(ID3D12Device* device, vector<T> vec, ID3D12Resource* res, UINT buffSize);
public:
	friend class FbxLoader;

	~FbxModel() { fbxScene->Destroy(); }

	void CreateBuffers(ID3D12Device* device);
	void Draw(ID3D12GraphicsCommandList* cmdList);

	const Matrix4& GetModelTransform() { return meshNode->globalTransform; }
	vector<Bone>& GetBones() { return bones; }
	FbxScene* GetFbxScene() { return fbxScene; }
};

template<class T>
inline ID3D12Resource* FbxModel::CreateBuffer(ID3D12Device* device, vector<T> vec, ID3D12Resource* res, UINT buffSize)
{
	HRESULT result = device->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(buffSize),
		D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&res));
	assert(SUCCEEDED(result));

	T* map = nullptr;
	result = res->Map(0, nullptr, (void**)&map);
	if (SUCCEEDED(result))
	{
		std::copy(vec.begin(), vec.end(), map);
		res->Unmap(0, nullptr);
	}

	return res;
}