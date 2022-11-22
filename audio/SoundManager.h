#pragma once
#include "Audio.h"
#include <vector>

class SoundManager
{
private:
	Audio* audio_ = nullptr;
	std::vector<uint32_t> bgm_, se_;
	std::vector<uint32_t> playHandle_;

	SoundManager() = default;
	~SoundManager() = default;
	SoundManager(const SoundManager&) = delete;
	const SoundManager& operator=(const SoundManager&) = delete;
public:
	enum BGM { Title, Play, Clear, GameOver };
	enum SE { P_Jamp, P_Damage, E_Bite, E_Breath, E_Damage };

	static SoundManager* GetInstance();

	void Initialize();
	void PlayBGM(BGM index);
	void PlaySE(SE index);
	void StopBGM(BGM index);
	void Finalize() { audio_->Finalize(); }
};