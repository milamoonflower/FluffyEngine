#pragma once
#include "ISoundSystem.h"
#include <SDL.h>
#include <unordered_map>
#include <memory>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <future>

struct Mix_Chunk;

namespace Fluffy
{
	class SDLSoundSystem : public ISoundSystem
	{
	public:
		SDLSoundSystem();
		~SDLSoundSystem();
		void AddSFX(const std::string& filePath, const SoundID ID) override;
		void Play(const Sound& sound) override;
		void Update() override;
		void Pause() override;
		void Resume() override;
		void Stop() override;

	private:
		std::mutex m_SoundMutex;
		std::condition_variable m_SoundQueuedCondition;
		std::unordered_map<SoundID, Mix_Chunk*> m_SoundEffects;
		std::queue<Sound> m_SoundQueue;

		bool TryFindSoundEffect(SoundID soundID, Mix_Chunk*& outSound) const;
	};
}
