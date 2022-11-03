#include "FbxLoader.h"
#include <cassert>

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
}
