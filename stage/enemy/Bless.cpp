#include "Bless.h"

/// <summary>
/// ������
/// </summary>
void Bless::Initialize(const Vector3& position, const Vector3 velocity, ViewProjection* viewProjection)
{
	// ���[���h�g�����X�t�H�[��
	worldTransform_.Initialize();
	// �����Ŏ󂯎�����������W���Z�b�g
	worldTransform_.translation_ = position;

	// �����Ŏ󂯎�������x�������o�ϐ��ɑ��
	velocity_ = velocity;

	particleManager_.Initialize(viewProjection);
}

/// <summary>
/// �X�V
/// </summary>
void Bless::Update()
{
	// ���W���ړ������� (1�t���[�����̈ړ��ʂ𑫂�����)
	worldTransform_.translation_ += velocity_;

	particleManager_.Add(worldTransform_.translation_, 60, 10.0f, 0.0f);
	particleManager_.Update();

	// �s��̍X�V
	worldTransform_.Update();

	// ���Ԍo�߂Ńf�X
	if (--dethTimer_ <= 0) {
		isDead_ = true;
	}
}

/// <summary>
/// �`��
/// </summary>
void Bless::Draw()
{
	particleManager_.Draw();
}