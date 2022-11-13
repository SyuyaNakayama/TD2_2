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
	enemy_.Initialize();

	FbxObject3d::SetDevice(dxCommon_->GetDevice());
	FbxObject3d::SetViewProjection(&viewProjection_);
	FbxObject3d::CreateGraphicsPipeline();
	fbxModel_ = FbxLoader::GetInstance()->LoadModelFromFile("cube");
	fbxObject_ = new FbxObject3d;
	fbxObject_->Initialize(&fbxObjWT);
	fbxObject_->SetModel(fbxModel_);
	stage_.Initialize(viewProjection_);
}

void GameScene::Update()
{
	// 当たり判定
	//collisionManager.CheckAllCollisions(&player_, &enemy_);
	enemy_.Update();
	stage_.Update();

	viewProjection_.UpdateMatrix();
	debugCamera_->Update();
	//viewProjection_ = debugCamera_->GetViewProjection();
	fbxObject_->Update();
	
	debugText_->SetPos(0, 0);
	debugText_->Printf("%f", viewProjection_.eye.z);
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
	enemy_.Draw(viewProjection_);
	stage_.Draw();
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
	
	//fbxObject_->Draw(commandList);
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
