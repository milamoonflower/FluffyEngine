#include "SDLSoundSystem.h"
#include <iostream>
#include <algorithm>

namespace Fluffy
{
	SDLSoundSystem::SDLSoundSystem()
	{
		if (Mix_Init(SDL_INIT_AUDIO) < 0)
		{
			std::cerr << "Failed to initialize sound system: " << SDL_GetError() << std::endl;
			return;
		}

		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
		{
			std::cerr << "Failed to initialize SDL_mixer: " << Mix_GetError() << std::endl;
			return;
		}
	}

	SDLSoundSystem::~SDLSoundSystem()
	{
		for (const auto& pSound : m_pSFX)
		{
			Mix_FreeChunk(pSound.second.get());
		}

		m_pSFX.clear();

		Mix_CloseAudio();
		Mix_Quit();
	}

	void SDLSoundSystem::AddSFX(const std::string& filePath, const soundID ID)
	{
		Mix_Chunk* soundEffect = Mix_LoadWAV(filePath.c_str());
		if (soundEffect == nullptr)
		{
			std::cerr << "Couldn't load sound: " << Mix_GetError() << std::endl;
			return;
		}

		std::lock_guard<std::mutex> lock(m_SoundMutex);
		m_pSFX.insert({ ID, std::shared_ptr<Mix_Chunk>(soundEffect) });
	}

	void SDLSoundSystem::Update()
	{

	}

	void SDLSoundSystem::Play(const soundID ID, const int volume)
	{
		const auto it{ m_pSFX.find(ID) /*std::find(m_pSFX.begin(), m_pSFX.end(), ID)*/ };

		if (it == m_pSFX.end())
		{
			std::cerr << "Sound effect doesn't exist." << std::endl;
			return;
		}

		Mix_Volume(-1, volume);
		int channel = Mix_PlayChannel(-1, it->second.get(), 0);
		if (channel == -1)
		{
			std::cerr << "Sound could not be played." << std::endl;
			return;
		}
	}

	void SDLSoundSystem::Pause()
	{
		Mix_Pause(-1);
	}

	void SDLSoundSystem::Resume()
	{
		Mix_Resume(-1);
	}

	void SDLSoundSystem::Stop()
	{
		Mix_HaltChannel(-1);
	}
}
