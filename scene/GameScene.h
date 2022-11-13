#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "Stage.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {
private: // サブクラス
	enum Scene { Title, HowToPlay, Play, Clear, GameOver };
public: // メンバ関数
	~GameScene();
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
	Audio* audio_ = nullptr;
	Stage stage_;
	DebugText* debugText_ = nullptr;
};
