#include "ToggleSoundCommand.h"
#include "SoundManager.h"

void ToggleSoundCommand::Execute()
{
	SoundManager::GetInstance().ToggleMute();
}
