#include "Bless.h"

/// <summary>
/// 初期化
/// </summary>
void Bless::Initialize(const Vector3& position, const Vector3 velocity, ViewProjection* viewProjection)
{
	// ワールドトランスフォーム
	worldTransform_.Initialize();
	// 引数で受け取った初期座標をセット
	worldTransform_.translation_ = position;

	// 引数で受け取った速度をメンバ変数に代入
	velocity_ = velocity;

	particleManager_.Initialize(viewProjection);

	SetCollisionAttribute(CollisionAttribute::EnemyBreath);
	SetCollisionMask(CollisionMask::EnemyBreath);

	isDead_ = false;
}

/// <summary>
/// 更新
/// </summary>
void Bless::Update()
{
	if (isDead_) { return; }
	// 座標を移動させる (1フレーム分の移動量を足しこむ)
	worldTransform_.translation_ += velocity_;

	particleManager_.Add(worldTransform_.translation_, 60, 10.0f, 0.0f);
	particleManager_.Update();

	// 行列の更新
	worldTransform_.Update();

	// 時間経過でデス
	if (--dethTimer_ <= 0)
	{
		isDead_ = true;
		dethTimer_ = kLifeTime;
	}
}

/// <summary>
/// 描画
/// </summary>
void Bless::Draw()
{
	if (isDead_) { return; }
	particleManager_.Draw();
}
