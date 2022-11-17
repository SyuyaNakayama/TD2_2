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
	particleManager_.Initialize(&viewProjection_);
	player_ = Player::GetInstance();
	player_->Initialize(&viewProjection_);
	enemy_.Initialize();
	axisIndicator_ = AxisIndicator::GetInstance();
	axisIndicator_->SetVisible(true);
	axisIndicator_->SetTargetViewProjection(&viewProjection_);
}

void Stage::Update()
{
	//player_->UpdateSpeed();
	// 当たり判定
	//collisionManager.CheckAllCollisions(&player_, &enemy_);
	//particleManager_.Add({ 20,0,0 }, 60, 10.0f, 0.0f);
#pragma region オブジェクトの更新
	player_->Update();
	enemy_.Update();
	if (Input::GetInstance()->TriggerKey(DIK_RETURN)) { 
		shake_.ShakeStart(10.0f); 
	}
	shake_.Update(viewProjection_);
#pragma endregion
#pragma region カメラの更新
	viewProjection_.UpdateMatrix();
	particleManager_.Update();
	debugCamera_->Update();
	//viewProjection_ = debugCamera_->GetViewProjection();
	axisIndicator_->Update();
#pragma endregion
}

void Stage::Draw()
{
	player_->Draw();
	blockManager_.Draw(viewProjection_);
	enemy_.Draw(viewProjection_);
	particleManager_.Draw();
	axisIndicator_->Draw();
}

Stage::~Stage()
{
	SafeDelete(debugCamera_);
}