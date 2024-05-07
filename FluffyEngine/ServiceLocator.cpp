#include "ServiceLocator.h"

namespace Fluffy
{
	std::unique_ptr<ISoundSystem> ServiceLocator::pSoundSystemInstance = nullptr;
}
