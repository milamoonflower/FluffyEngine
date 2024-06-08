#include "SDLSoundSystem.h"
#include <SDL_mixer.h>
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
		for (const auto& pSound : m_SoundEffects)
		{
			Mix_FreeChunk(pSound.second);
		}

		m_SoundEffects.clear();

		Mix_CloseAudio();
		Mix_Quit();
	}

	void SDLSoundSystem::AddSFX(const std::string& filePath, const SoundID ID)
	{
		Mix_Chunk* soundEffect = Mix_LoadWAV(filePath.c_str());
		if (soundEffect == nullptr)
		{
			std::cerr << "Couldn't load sound: " << Mix_GetError() << std::endl;
			return;
		}

		std::lock_guard<std::mutex> lock(m_SoundMutex);
		m_SoundEffects.insert({ ID, soundEffect });
	}

	void SDLSoundSystem::Play(const Sound& sound)
	{
		m_SoundQueue.push(sound);
		m_SoundQueuedCondition.notify_one();

		std::thread{ [this] { Update(); } }.detach();	// detach because we don't care to wait for or own this thread, we just want it to do its thing on its own
	}

	void SDLSoundSystem::Update()
	{
		bool hasValidSound{ false };
		Sound sound{};
		{
			std::unique_lock lock{ m_SoundMutex };
			m_SoundQueuedCondition.wait(lock, [this] { return !m_SoundQueue.empty(); });

			// not sure if terminating the thread would make it end up here, so we're double-checking that the queue is not empty just to be safe
			if (!m_SoundQueue.empty())
			{
				sound = m_SoundQueue.front();
				m_SoundQueue.pop();

				hasValidSound = true;
			}
		}

		if (!hasValidSound)
			return;

		m_SoundQueuedCondition.notify_one();

		Mix_Chunk* pSound{ nullptr };
		if (!TryFindSoundEffect(sound.ID, pSound))
		{
			std::cerr << "Sound effect doesn't exist." << std::endl;
			return;
		}

		Mix_Volume(-1, sound.volume);	// all sounds will change the volume of the same channel -> should fix at some point (more channels?)
		int channel = Mix_PlayChannel(-1, pSound, 0);
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

	bool SDLSoundSystem::TryFindSoundEffect(SoundID soundID, Mix_Chunk*& outSound) const
	{
		const auto it{ m_SoundEffects.find(soundID) };

		if (it != m_SoundEffects.end())
		{
			outSound = it->second;
			return true;
		}

		outSound = nullptr;
		return false;
	}
}
