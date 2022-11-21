#include "Bless.h"
#include "Affin.h"
#include <cassert>

/// <summary>
/// ������
/// </summary>
void Bless::Initialize(Model* model, const Vector3& position, const Vector3 velocity) {
	// NULL�|�C���^�`�F�b�N
	assert(model);

	model_ = model;
	// �e�N�X�`���ǂݍ���
	textureHandle_ = TextureManager::Load("white1x1.png");

	// ���[���h�g�����X�t�H�[��
	worldTransform_.Initialize();
	// �����Ŏ󂯎�����������W���Z�b�g
	worldTransform_.translation_ = position;

	worldTransform_.TransferMatrix();

	// �����Ŏ󂯎�������x�������o�ϐ��ɑ��
	velocity_ = velocity;
}

/// <summary>
/// �X�V
/// </summary>
void Bless::Update() {

	// ���W���ړ������� (1�t���[�����̈ړ��ʂ𑫂�����)
	worldTransform_.translation_ += velocity_;

	// �s��̍X�V
	worldTransform_.matWorld_ = Affin::matWorld(
		worldTransform_.translation_, worldTransform_.rotation_, worldTransform_.scale_);
	worldTransform_.TransferMatrix();

	// ���Ԍo�߂Ńf�X
	if (--dethTimer_ <= 0) {
		isDead_ = true;
	}
}

/// <summary>
/// �`��
/// </summary>
void Bless::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
