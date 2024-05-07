#pragma once
#include "ISoundSystem.h"
#include <memory>

namespace Fluffy
{
	class ServiceLocator final
	{
	public:
		static ISoundSystem* GetSoundSystem() { return pSoundSystemInstance.get(); }
		static void RegisterSoundSystem(std::unique_ptr<ISoundSystem>&& soundSystem) { pSoundSystemInstance = std::move(soundSystem); }

	private:
		static std::unique_ptr<ISoundSystem> pSoundSystemInstance;
	};
}
