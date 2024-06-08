#pragma once
#include <string>

namespace Fluffy
{
	using SoundID = unsigned short;

	struct Sound
	{
		SoundID ID;
		int volume;
	};

	class ISoundSystem
	{
	public:
		virtual ~ISoundSystem() = default;

		ISoundSystem(const ISoundSystem& other) = delete;
		ISoundSystem(ISoundSystem&& other) = delete;
		ISoundSystem& operator=(const ISoundSystem& other) = delete;
		ISoundSystem& operator=(ISoundSystem&& other) = delete;

		virtual void AddSFX(const std::string& filePath, const SoundID ID) = 0;
		virtual void Update() = 0;
		virtual void Play(const Sound&) = 0;
		virtual void SetVolume(const int volume) = 0;
		virtual void Pause() = 0;
		virtual void Resume() = 0;
		virtual void Stop() = 0;

	protected:
		ISoundSystem() = default;
	};
}
