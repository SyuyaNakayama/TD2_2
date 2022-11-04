#include "FbxLoader.h"
#include <cassert>
#include <MathUtility.h>
using namespace MathUtility;

const std::string FbxLoader::BASE_DIRECTORY = "Resources/";

FbxLoader* FbxLoader::GetInstance()
{
	static FbxLoader instance;
	return &instance;
}

void FbxLoader::Initialize(ID3D12Device* device)
{
	assert(fbxManager == nullptr);
	this->device = device;
	fbxManager = FbxManager::Create();
	FbxIOSettings* ios = FbxIOSettings::Create(fbxManager, IOSROOT);
	fbxManager->SetIOSettings(ios);
	fbxImporter = FbxImporter::Create(fbxManager, "");
}

void FbxLoader::Finalize()
{
	fbxImporter->Destroy();
	fbxManager->Destroy();
}

void FbxLoader::LoadModelFromFile(const string& modelName)
{
	const string
		DIRECTORY_PATH = BASE_DIRECTORY + modelName + "/",
		FILE_NAME = modelName + ".fbx",
		FULLPATH = DIRECTORY_PATH + FILE_NAME;

	bool result = fbxImporter->Initialize(FULLPATH.c_str(), -1, fbxManager->GetIOSettings());
	assert(result);

	FbxScene* fbxScene = FbxScene::Create(fbxManager, "fbxScene");
	fbxImporter->Import(fbxScene);

	FbxModel* model = new FbxModel();
	model->name = modelName;

	int nodeCount = fbxScene->GetNodeCount();
	model->nodes.reserve(nodeCount);

	ParseNodeRecursive(model, fbxScene->GetRootNode());
	fbxScene->Destroy();
}

void FbxLoader::ParseNodeRecursive(FbxModel* model, FbxNode* fbxNode, Node* parent)
{
	model->nodes.emplace_back();
	Node& node = model->nodes.back();
	node.name = fbxNode->GetName();

	FbxDouble3 rotation = fbxNode->LclRotation.Get(),
		scaling = fbxNode->LclScaling.Get(),
		translation = fbxNode->LclTranslation.Get();

	node.rotation = { (float)rotation[0],(float)rotation[1],(float)rotation[2] };
	node.scaling = { (float)scaling[0],(float)scaling[1],(float)scaling[2] };
	node.translation = { (float)translation[0],(float)translation[1],(float)translation[2] };

	node.rotation.x = DegreeToRadian(node.rotation.x);
	node.rotation.y = DegreeToRadian(node.rotation.y);
	node.rotation.z = DegreeToRadian(node.rotation.z);

	Matrix4 matScaling = Matrix4Scaling(node.scaling),
		matRotation = Matrix4Rotation(node.rotation),
		matTranslation = Matrix4Translation(node.translation);

	node.globalTransform = node.transform = matScaling * matRotation * matTranslation;

	if (parent)
	{
		node.parent = parent;
		node.globalTransform *= parent->globalTransform;
	}

	for (size_t i = 0; i < fbxNode->GetChildCount(); i++)
	{
		ParseNodeRecursive(model, fbxNode->GetChild(i), &node);
	}
}