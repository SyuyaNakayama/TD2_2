#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

using namespace std;

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();
	debugCamera_ = new DebugCamera(WinApp::kWindowWidth, WinApp::kWindowHeight);
	model_ = Model::Create();
	viewProjection_.Initialize();
	player_.Initialize(&viewProjection_);
	enemy_.Initialize();
	boxes_.resize(100);
	for (WorldTransform& box : boxes_) { box.Initialize(); }

	for (size_t i = 0; i < 25; i++)
	{
		boxes_[i].translation_ = { (float)(i % 4)*2.0f, (float)i*2.0f, 0};
	}
	for (size_t i = 25; i < 50; i++)
	{
		int j = i % 25;
		boxes_[i].translation_ = { (float)(j % 4)*2.0f, (float)j*2.0f, 8.0f};
	}
	for (size_t i = 50; i < 75; i++)
	{
		int j = i % 50;
		boxes_[i].translation_ = { 0,(float)j*2.0f,(float)(j % 4)*2.0f };
	}
	for (size_t i = 75; i < 100; i++)
	{
		int j = i % 75;
		boxes_[i].translation_ = { 8.0f,(float)j*2.0f,(float)(j % 4)*2.0f };
	}

	for (WorldTransform& box : boxes_) { box.Update(); }
}

void GameScene::Update()
{
	player_.Update();
	enemy_.Update();

	// 当たり判定
	collisionManager.CheckAllCollisions(&player_, &enemy_);

	debugCamera_->Update();
	viewProjection_ = debugCamera_->GetViewProjection();
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	for (WorldTransform box : boxes_) { model_->Draw(box, viewProjection_); }

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
