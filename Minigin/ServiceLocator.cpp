#include "ServiceLocator.h"

std::unique_ptr<ISoundSystem> ServiceLocator::pSoundSystemInstance = nullptr;
