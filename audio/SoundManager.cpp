#include "SoundManager.h"

void SoundManager::Initialize()
{
	// オーディオの初期化
	audio_ = Audio::GetInstance();
	audio_->Initialize();
	//bgm_.push_back(audio_->LoadWave("sound/bgm/battleMusic1.mp3"));
	//bgm_.push_back(audio_->LoadWave("sound/bgm/battleMusic2.mp3"));
	//bgm_.push_back(audio_->LoadWave("sound/bgm/battleMusic3.mp3"));
	//bgm_.push_back(audio_->LoadWave("sound/bgm/battleMusic4.mp3"));
	playHandle_.resize(bgm_.size());
}

void SoundManager::PlayBGM(BGM index)
{
	if (audio_->IsPlaying(playHandle_[index])) { return; }
	playHandle_[index] = audio_->PlayWave(bgm_[index], true, 0.8f);
}

void SoundManager::PlaySE(SE index)
{
	audio_->PlayWave(se_[index]);
}

void SoundManager::StopBGM(BGM index)
{
	audio_->StopWave(playHandle_[index]);
}

SoundManager* SoundManager::GetInstance()
{
	static SoundManager* instance = new SoundManager;
	instance->Initialize();
	return instance;
}