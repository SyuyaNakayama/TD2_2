#pragma once
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "particleManager/ParticleManager.h"

/// <summary>
/// 敵キャラの弾
/// </summary>
class Bless {
private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// 速度
	Vector3 velocity_;
	// 寿命<frm>
	static const int kLifeTime = 60 * 5;
	// デスタイマー
	int dethTimer_ = kLifeTime;
	// デスフラグ
	bool isDead_ = false;
	ParticleManager particleManager_;

public:
	bool IsDead() const { return isDead_; }

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(const Vector3& position, const Vector3 velocity, ViewProjection* viewProjection);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
};

