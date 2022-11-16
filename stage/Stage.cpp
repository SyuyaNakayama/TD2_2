#include "Stage.h"
#include "DirectXCommon.h"
#include "SafeDelete.h"
using namespace std;

void Stage::Initialize()
{
	debugText_ = DebugText::GetInstance();
	debugCamera_ = new DebugCamera(WinApp::kWindowWidth, WinApp::kWindowHeight);
	model_ = Model::Create();
	viewProjection_.Initialize();
	blockManager_.Initialize();
	particleManager_.Initialize();
	player_ = Player::GetInstance();
	player_->Initialize(&viewProjection_);
	enemy_.Initialize();
	/*FbxObject3d::SetDevice(dxCommon_->GetDevice());
	FbxObject3d::SetViewProjection(&viewProjection_);
	FbxObject3d::CreateGraphicsPipeline();
	fbxModel_ = FbxLoader::GetInstance()->LoadModelFromFile("cube");
	fbxObject_ = new FbxObject3d;
	fbxObject_->Initialize(&fbxObjWT);
	fbxObject_->SetModel(fbxModel_);*/
}

void Stage::Update()
{
	player_->UpdateSpeed();
	// 当たり判定
	//collisionManager.CheckAllCollisions(&player_, &enemy_);
	particleManager_.Add(60, 10.0f, 0.0f);
#pragma region オブジェクトの更新
	player_->Update();
	enemy_.Update();
	//fbxObject_->Update();
	particleManager_.SetEye({ viewProjection_.eye.x,viewProjection_.eye.y,viewProjection_.eye.z });
	particleManager_.Update();
#pragma endregion
#pragma region カメラの更新
	viewProjection_.UpdateMatrix();
	debugCamera_->Update();
	//viewProjection_ = debugCamera_->GetViewProjection();

#pragma endregion
}

void Stage::Draw()
{
	//player_->Draw();
	blockManager_.Draw(viewProjection_);
	//enemy_.Draw(viewProjection_);
	particleManager_.PreDraw(DirectXCommon::GetInstance()->GetCommandList());
	particleManager_.Draw();
	particleManager_.PostDraw();
}

Stage::~Stage()
{
	SafeDelete(debugCamera_);
}