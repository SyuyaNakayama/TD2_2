#include "Stage.h"
#include "WinApp.h"
#include "SafeDelete.h"
using namespace std;

void Stage::Initialize()
{
	debugText_ = DebugText::GetInstance();
	debugCamera_ = new DebugCamera(WinApp::kWindowWidth, WinApp::kWindowHeight);
	model_ = Model::Create();
	viewProjection_.Initialize();
	/*FbxObject3d::SetDevice(dxCommon_->GetDevice());
	FbxObject3d::SetViewProjection(&viewProjection_);
	FbxObject3d::CreateGraphicsPipeline();
	fbxModel_ = FbxLoader::GetInstance()->LoadModelFromFile("cube");
	fbxObject_ = new FbxObject3d;
	fbxObject_->Initialize(&fbxObjWT);
	fbxObject_->SetModel(fbxModel_);*/

	blocks_.resize(100);
	for (size_t i = 0; i < blocks_.size(); i++)
	{
		blocks_[i].Initialize();
		if (i < 25)
		{
			blocks_[i].translation_ = { -POLE_RAD + 2.0f * (float)(i + 1),(float)i * 2.0f,-POLE_RAD };
		}
		else if (i < 50)
		{
			blocks_[i].translation_ = { POLE_RAD,(float)i * 2.0f,-POLE_RAD + 2.0f * (float)(i % 25 + 1) };
		}
		else if (i < 75)
		{
			blocks_[i].translation_ = { POLE_RAD - 2.0f * (float)(i % 50 + 1),(float)i * 2.0f,POLE_RAD };
		}
		else
		{
			blocks_[i].translation_ = { -POLE_RAD,(float)i * 2.0f,POLE_RAD - 2.0f * (float)(i % 75 + 1) };
		}
		blocks_[i].Update();
	}
	player_ = Player::GetInstance();
	player_->Initialize(&viewProjection_);
	enemy_.Initialize();
}

void Stage::Update()
{
	player_->UpdateSpeed();
	// 当たり判定
	//collisionManager.CheckAllCollisions(&player_, &enemy_);
#pragma region オブジェクトの更新
	player_->Update();
	enemy_.Update();
	//fbxObject_->Update();
#pragma endregion
#pragma region カメラの更新
	viewProjection_.UpdateMatrix();
	debugCamera_->Update();
	//viewProjection_ = debugCamera_->GetViewProjection();

#pragma endregion
}

void Stage::Draw()
{
	player_->Draw();
	for (WorldTransform& block : blocks_) { model_->Draw(block, viewProjection_); }
	//enemy_.Draw(viewProjection_);
}

Stage::~Stage()
{
	SafeDelete(debugCamera_);
}