#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "FbxLoader.h"

using namespace std;

GameScene::~GameScene()
{
	delete fbxModel_, fbxObject_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();
	debugCamera_ = new DebugCamera(WinApp::kWindowWidth, WinApp::kWindowHeight);
	model_ = Model::CreateFromOBJ("tamesi");
	tamesi.Initialize();
	viewProjection_.Initialize();
	player_.Initialize(&viewProjection_);
	enemy_.Initialize();

	FbxObject3d::SetDevice(dxCommon_->GetDevice());
	FbxObject3d::SetViewProjection(&viewProjection_);
	FbxObject3d::CreateGraphicsPipeline();
	fbxModel_ = FbxLoader::GetInstance()->LoadModelFromFile("cube");
	fbxObject_ = new FbxObject3d;
	fbxObject_->Initialize();
	fbxObject_->SetModel(fbxModel_);
}

void GameScene::Update()
{
	player_.Update();
	enemy_.Update();

	// 当たり判定
	collisionManager.CheckAllCollisions(&player_, &enemy_);
	viewProjection_.UpdateMatrix();
	debugCamera_->Update();
	viewProjection_ = debugCamera_->GetViewProjection();
	fbxObject_->Update();
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
	model_->Draw(tamesi, viewProjection_);
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
	fbxObject_->Draw(commandList);
	debugText_->SetPos(0, 0);
	debugText_->Printf("%f", viewProjection_.eye.y);
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
