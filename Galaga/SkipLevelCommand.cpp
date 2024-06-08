#include "SkipLevelCommand.h"
#include "GameManager.h"

void SkipLevelCommand::Execute()
{
	if (GameManager::GetInstance() != nullptr)
		GameManager::GetInstance()->SkipToNextLevel();
}
