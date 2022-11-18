#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

using namespace std;

void GameScene::Initialize()
{
	debugText_ = DebugText::GetInstance();
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	fadeManager_.Initialize(&scene_);
	stage_.Initialize();
	//sprite_ = Sprite::Create(TextureManager::Load("image.webp"), { 0,0 });
	//sprite_->SetSize({ 1280,720 });
}

void GameScene::Update()
{
	switch (scene_)
	{
	case Title:
		if (input_->TriggerKey(DIK_SPACE)) { fadeManager_.ChangeScene(HowToPlay); }
		break;
	case HowToPlay:
		if (input_->TriggerKey(DIK_SPACE))
		{
			fadeManager_.ChangeScene(Play);
			stage_.Initialize();
		}
		break;
	case Play:
		if (input_->TriggerKey(DIK_SPACE)) { fadeManager_.ChangeScene(Clear); }
		if (input_->TriggerKey(DIK_RETURN)) { fadeManager_.ChangeScene(GameOver); }
		stage_.Update();
		break;
	case Clear:
		if (input_->TriggerKey(DIK_SPACE)) { fadeManager_.ChangeScene(Title); }
		break;
	case GameOver:
		if (input_->TriggerKey(DIK_SPACE))
		{
			fadeManager_.ChangeScene(Play);
			stage_.Initialize();
		}
		if (input_->TriggerKey(DIK_RETURN))
		{
			fadeManager_.ChangeScene(Title);
		}
		break;
	}
	fadeManager_.Update();
}

void GameScene::Draw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>
	//sprite_->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	if (scene_ == Play)
	{
		// 3Dオブジェクト描画前処理
		Model::PreDraw(commandList);

		/// <summary>
		/// ここに3Dオブジェクトの描画処理を追加できる
		/// </summary>
		stage_.Draw();
		// 3Dオブジェクト描画後処理
		Model::PostDraw();
	}
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	fadeManager_.Draw();
	// デバッグテキストの描画
	debugText_->DrawAll(commandList);

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
