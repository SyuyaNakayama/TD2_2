#pragma once
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "particleManager/ParticleManager.h"
#include "collider/Collider.h"

/// <summary>
/// 敵キャラの弾
/// </summary>
class Bless :public Collider
{
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
	void OnCollision(Collider* collider) {}
	const Vector3 GetWorldPosition() { return worldTransform_.translation_; }
	const Vector3 GetRadius() { return Vector3(5.0f, 5.0f, 5.0f); }
};

