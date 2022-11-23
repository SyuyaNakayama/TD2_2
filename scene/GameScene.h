#pragma once

#include "SoundManager.h"
#include "DirectXCommon.h"
#include "SafeDelete.h"
#include "stage/Stage.h"
#include "fadeManager/FadeManager.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {
public: // メンバ関数
	~GameScene() { soundManager_->Finalize(); }

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private: // メンバ変数
	DirectXCommon* dxCommon_= DirectXCommon::GetInstance();
	Input* input_ = Input::GetInstance();
	SoundManager* soundManager_ = SoundManager::GetInstance();
	Stage stage_;
	DebugText* debugText_ = DebugText::GetInstance();
	Scene scene_ = Play;
	FadeManager fadeManager_;
	std::vector<Sprite*> sprite_{};
	float playerBodyRotSpd = 0.06f;
	float startStringYOffset_ = 0;
};