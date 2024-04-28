#pragma once
#include "ISoundSystem.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include <unordered_map>
#include <memory>
#include <mutex>

class SDLSoundSystem : public ISoundSystem
{
public:
	SDLSoundSystem();
	~SDLSoundSystem();
	void AddSFX(const std::string& filePath, const soundID ID) override;
	void Update() override;
	void Play(const soundID ID, const int volume) override;
	void Pause() override;
	void Resume() override;
	void Stop() override;

private:
	std::mutex m_SoundMutex;
	std::unordered_map<soundID, std::shared_ptr<Mix_Chunk>> m_pSFX;
};
