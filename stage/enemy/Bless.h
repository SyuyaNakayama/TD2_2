#pragma once
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "particleManager/ParticleManager.h"

/// <summary>
/// �G�L�����̒e
/// </summary>
class Bless {
private:
	// ���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	// ���x
	Vector3 velocity_;
	// ����<frm>
	static const int kLifeTime = 60 * 5;
	// �f�X�^�C�}�[
	int dethTimer_ = kLifeTime;
	// �f�X�t���O
	bool isDead_ = false;
	ParticleManager particleManager_;

public:
	bool IsDead() const { return isDead_; }

	/// <summary>
	/// ������
	/// </summary>
	void Initialize(const Vector3& position, const Vector3 velocity, ViewProjection* viewProjection);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();
};
