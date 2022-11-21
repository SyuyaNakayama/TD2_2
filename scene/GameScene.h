#pragma once

#include "SoundManager.h"
#include "DirectXCommon.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "stage/Stage.h"
#include "fadeManager/FadeManager.h"
#include "scene.h"

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
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	SoundManager* soundManager_ = nullptr;
	Stage stage_;
	DebugText* debugText_ = nullptr;
	Scene scene_ = Play;
	FadeManager fadeManager_;
	Sprite* sprite_ = nullptr;
};
