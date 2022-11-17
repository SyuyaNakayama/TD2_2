#include "Stage.h"
#include "DirectXCommon.h"
#include "SafeDelete.h"
using namespace std;

void Stage::Initialize()
{
	debugText_ = DebugText::GetInstance();
	debugCamera_ = new DebugCamera(WinApp::kWindowWidth, WinApp::kWindowHeight);
	model_ = Model::Create();
	DragonHead = Model::CreateFromOBJ("DragonHead");
	viewProjection_.Initialize();
	blockManager_.Initialize();
	particleManager_.Initialize(&viewProjection_);
	player_ = Player::GetInstance();
	player_->Initialize(&viewProjection_);
	enemy_.Initialize(DragonHead);
}

void Stage::Update()
{
	player_->UpdateSpeed();
	// 当たり判定
	//collisionManager.CheckAllCollisions(&player_, &enemy_);
	particleManager_.Add(player_->GetPosition(), 60, 10.0f, 0.0f);
#pragma region オブジェクトの更新
	player_->Update();
	enemy_.Update();
	//fbxObject_->Update();
#pragma endregion
#pragma region カメラの更新
	viewProjection_.UpdateMatrix();
	particleManager_.Update();
	debugCamera_->Update();
	//viewProjection_ = debugCamera_->GetViewProjection();

#pragma endregion
}

void Stage::Draw()
{
	player_->Draw();
	blockManager_.Draw(viewProjection_);
	enemy_.Draw(viewProjection_);
	particleManager_.Draw();
}

Stage::~Stage()
{
	SafeDelete(debugCamera_);
}