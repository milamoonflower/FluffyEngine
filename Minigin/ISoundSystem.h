#pragma once
#include <string>

using soundID = unsigned short;

class ISoundSystem
{
public:
	virtual ~ISoundSystem() = default;

	ISoundSystem(const ISoundSystem& other) = delete;
	ISoundSystem(ISoundSystem&& other) = delete;
	ISoundSystem& operator=(const ISoundSystem& other) = delete;
	ISoundSystem& operator=(ISoundSystem&& other) = delete;

	virtual void AddSFX(const std::string& filePath, const soundID ID) = 0;
	virtual void Update() = 0;
	virtual void Play(const soundID ID, const int volume) = 0;
	virtual void Pause() = 0;
	virtual void Resume() = 0;
	virtual void Stop() = 0;

protected:
	ISoundSystem() = default;
};
