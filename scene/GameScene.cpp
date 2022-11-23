#include "GameScene.h"

using namespace std;

void GameScene::Initialize()
{
	fadeManager_.Initialize(&scene_);
	stage_.Initialize();
	sprite_.push_back(Sprite::Create(TextureManager::Load("sceneSprite/Title.png"), {}));
	sprite_.push_back(Sprite::Create(TextureManager::Load("sceneSprite/PUSH_START.png"), { 367.0f,500.0f }));
	sprite_.push_back(Sprite::Create(TextureManager::Load("sceneSprite/HowToPlay.png"), {}));
	sprite_.push_back(Sprite::Create(TextureManager::Load("sceneSprite/Clear.png"), {}));
	sprite_.push_back(Sprite::Create(TextureManager::Load("sceneSprite/GameOver.png"), {}));
}

void GameScene::Update()
{
	std::vector<WorldTransform> pw;

	switch (scene_)
	{
	case Title:
		if (input_->TriggerKey(DIK_SPACE)) { fadeManager_.ChangeScene(HowToPlay); }
		startStringYOffset_ += 0.04f;
		sprite_[1]->SetPosition({ 367.0f,500.0f - fabs(sinf(startStringYOffset_)) * 30.0f });
		break;
	case HowToPlay:
		if (input_->TriggerKey(DIK_SPACE))
		{
			fadeManager_.ChangeScene(Play);
			stage_.Initialize();
		}
		break;
	case Play:
		stage_.Update();
		//soundManager_->PlayBGM(SoundManager::Play);
		if (input_->TriggerKey(DIK_SPACE)) { fadeManager_.ChangeScene(Clear); }
		if (input_->TriggerKey(DIK_RETURN)) { fadeManager_.ChangeScene(GameOver); }
		break;
	case Clear:
		pw = Player::GetInstance()->GetWorldTransforms();
		pw[0].translation_ = { 0,0,0 };
		pw[0].rotation_.y = 0;
		pw[3].rotation_.x += playerBodyRotSpd;
		pw[4].rotation_.x += playerBodyRotSpd;
		if (pw[3].rotation_.x >= 3.0f * PI / 4.0f || pw[3].rotation_.x < 0)
		{
			playerBodyRotSpd = -playerBodyRotSpd;
		}
		for (WorldTransform& w : pw) { w.Update(); }
		Player::GetInstance()->SetWorldTransforms(pw);
		stage_.SetEye({ 0,2.5f,-15.0f });
		stage_.SetTarget({ 0,2.5f,0 });

		if (input_->TriggerKey(DIK_SPACE)) { fadeManager_.ChangeScene(Title); }
		break;
	case GameOver:
			pw = Player::GetInstance()->GetWorldTransforms();
			pw[0].translation_ = { 0,0,0 };
			pw[0].rotation_.y = 0;
			pw[1].rotation_.x = -PI / 4.0f;
			for (WorldTransform& w : pw) { w.Update(); }
			Player::GetInstance()->SetWorldTransforms(pw);
			stage_.SetEye({ 0,2.5f,-15.0f });
			stage_.SetTarget({ 0,2.5f,0 });

		if (input_->TriggerKey(DIK_SPACE))
		{
			fadeManager_.ChangeScene(Reset);
		}
		if (input_->TriggerKey(DIK_RETURN)) { fadeManager_.ChangeScene(Title); }
		break;
	case Reset:
		stage_.Initialize();
		scene_ = Play;
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
	switch (scene_)
	{
	case Title:
		sprite_[0]->Draw();
		sprite_[1]->Draw();
		break;
	case HowToPlay:
		sprite_[2]->Draw();
		break;
	case Clear:
		sprite_[3]->Draw();
		break;
	case GameOver:
		sprite_[4]->Draw();
		break;
	}

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
	switch (scene_)
	{
	case Play:
		stage_.Draw();
		break;
	case Clear:
	case GameOver:
		Player::GetInstance()->Draw();
		break;
	}
	// 3Dオブジェクト描画後処理
	Model::PostDraw();

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
	
	switch (scene_)
	{
	case Play:
		stage_.SpriteDraw();
		break;
	case Clear:
	case GameOver:
		break;
	}
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
