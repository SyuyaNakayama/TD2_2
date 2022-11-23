#include "SoundManager.h"

void SoundManager::Initialize()
{
	// オーディオの初期化
	audio_ = Audio::GetInstance();
	audio_->Initialize();
	bgm_.push_back(audio_->LoadWave("sound/bgm/Title.mp3"));
	bgm_.push_back(audio_->LoadWave("sound/bgm/BattleMusic.mp3"));
	bgm_.push_back(audio_->LoadWave("sound/bgm/Clear3.mp3"));
	bgm_.push_back(audio_->LoadWave("sound/bgm/GameOver.mp3"));

	se_.push_back(audio_->LoadWave("sound/se/PlayerAttack.mp3"));
	se_.push_back(audio_->LoadWave("sound/se/PlayerDamage.mp3"));
	se_.push_back(audio_->LoadWave("sound/se/Bite.mp3"));
	se_.push_back(audio_->LoadWave("sound/se/Breath.mp3"));
	se_.push_back(audio_->LoadWave("sound/se/EnemyDamage.mp3"));
	playHandle_.resize(bgm_.size());
}

void SoundManager::PlayBGM(BGM index)
{
	if (audio_->IsPlaying(playHandle_[index])) { return; }
	playHandle_[index] = audio_->PlayWave(bgm_[index], true, 0.2f);
}

void SoundManager::PlaySE(SE index)
{
	audio_->PlayWave(se_[index], false, 1.0f);
}

void SoundManager::StopBGM(BGM index)
{
	audio_->StopWave(playHandle_[index]);
}

SoundManager* SoundManager::GetInstance()
{
	static SoundManager* instance = new SoundManager;
	return instance;
}