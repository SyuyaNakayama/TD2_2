#include "Stage.h"
#include "DirectXCommon.h"
#include "SafeDelete.h"
using namespace std;

void Stage::Initialize()
{
	debugText_ = DebugText::GetInstance();
	viewProjection_.Initialize();
	blockManager_.Initialize();
	player_ = Player::GetInstance();
	player_->Initialize(&viewProjection_);
	enemy_->Initialize(&viewProjection_);
	skydome = new Skydome();
	skydome->Initialize();
}

void Stage::Update()
{
#pragma region �I�u�W�F�N�g�̍X�V
	player_->Update();
	enemy_->Update();
	//if (Input::GetInstance()->TriggerKey(DIK_RETURN)) {
	//	shake_.ShakeStart(10.0f);
	//}
#pragma endregion
	// �����蔻��
	collisionManager.CheckAllCollisions(enemy_);
#pragma region �J�����̍X�V
	viewProjection_.UpdateMatrix();
#pragma endregion
}

void Stage::Draw()
{
	player_->Draw();
	blockManager_.Draw(viewProjection_);
	skydome->Draw(viewProjection_);
	enemy_->Draw();
}

void Stage::SpriteDraw()
{
	player_->SpriteDraw();
	enemy_->SpriteDraw();
};

Stage::~Stage()
{
	SafeDelete(skydome);
}