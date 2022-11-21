#include "Bless.h"
#include "Affin.h"
#include <cassert>

/// <summary>
/// 初期化
/// </summary>
void Bless::Initialize(Model* model, const Vector3& position, const Vector3 velocity) {
	// NULLポインタチェック
	assert(model);

	model_ = model;
	// テクスチャ読み込み
	textureHandle_ = TextureManager::Load("white1x1.png");

	// ワールドトランスフォーム
	worldTransform_.Initialize();
	// 引数で受け取った初期座標をセット
	worldTransform_.translation_ = position;

	worldTransform_.TransferMatrix();

	// 引数で受け取った速度をメンバ変数に代入
	velocity_ = velocity;
}

/// <summary>
/// 更新
/// </summary>
void Bless::Update() {

	// 座標を移動させる (1フレーム分の移動量を足しこむ)
	worldTransform_.translation_ += velocity_;

	// 行列の更新
	worldTransform_.matWorld_ = Affin::matWorld(
		worldTransform_.translation_, worldTransform_.rotation_, worldTransform_.scale_);
	worldTransform_.TransferMatrix();

	// 時間経過でデス
	if (--dethTimer_ <= 0) {
		isDead_ = true;
	}
}

/// <summary>
/// 描画
/// </summary>
void Bless::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
