#include "Stage.h"
#include "WinApp.h"
#include "SafeDelete.h"
#include "fbx/FbxLoader.h"
#include "DirectXCommon.h"
using namespace std;

void Stage::Initialize()
{
	debugText_ = DebugText::GetInstance();
	debugCamera_ = new DebugCamera(WinApp::kWindowWidth, WinApp::kWindowHeight);
	model_ = Model::Create();
	viewProjection_.Initialize();
	blockManager_.Initialize();
	FbxObject3d::SetViewProjection(&viewProjection_);
	FbxObject3d::CreateGraphicsPipeline();
	fbxModel_ = FbxLoader::GetInstance()->LoadModelFromFile("boneTest");
	fbxObject_ = new FbxObject3d;
	fbxObject_->Initialize(&fbxObjWT);
	fbxObject_->SetModel(fbxModel_);

	player_ = Player::GetInstance();
	player_->Initialize(&viewProjection_);
	enemy_.Initialize();
}

void Stage::Update()
{
	player_->UpdateSpeed();
	// 当たり判定
	//collisionManager.CheckAllCollisions(&player_, &enemy_);
#pragma region オブジェクトの更新
	player_->Update();
	enemy_.Update();
	fbxObject_->Update();
#pragma endregion
#pragma region カメラの更新
	viewProjection_.UpdateMatrix();
	debugCamera_->Update();
	//viewProjection_ = debugCamera_->GetViewProjection();

#pragma endregion
}

void Stage::Draw()
{
	player_->Draw();
	blockManager_.Draw(viewProjection_);
	//enemy_.Draw(viewProjection_);
}

Stage::~Stage()
{
	SafeDelete(debugCamera_);
}