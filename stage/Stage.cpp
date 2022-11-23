#include "Stage.h"
#include "DirectXCommon.h"
#include "SafeDelete.h"
using namespace std;

void Stage::Initialize()
{
	debugText_ = DebugText::GetInstance();
	debugCamera_ = new DebugCamera(WinApp::kWindowWidth, WinApp::kWindowHeight);
	viewProjection_.Initialize();
	blockManager_.Initialize();
	player_ = Player::GetInstance();
	player_->Initialize(&viewProjection_);
	enemy_.Initialize(&viewProjection_);
	skydome = new Skydome();
	skydome->Initialize();
}

void Stage::Update()
{
	// �����蔻��
	//collisionManager.CheckAllCollisions(&player_, &enemy_);
#pragma region �I�u�W�F�N�g�̍X�V
	player_->Update();
	enemy_.Update();
	//if (Input::GetInstance()->TriggerKey(DIK_RETURN)) {
	//	shake_.ShakeStart(10.0f);
	//}
	shake_.Update(viewProjection_);
#pragma endregion

#pragma region �J�����̍X�V
	viewProjection_.UpdateMatrix();
	debugCamera_->Update();
	//viewProjection_ = debugCamera_->GetViewProjection();
#pragma endregion
}

void Stage::Draw()
{
	player_->Draw();
	blockManager_.Draw(viewProjection_);
	skydome->Draw(viewProjection_);
	enemy_.Draw();
}

void Stage::SpriteDraw()
{
	enemy_.SpriteDraw();
	player_->SpriteDraw();
};

Stage::~Stage()
{
	SafeDelete(debugCamera_);
	SafeDelete(skydome);
}