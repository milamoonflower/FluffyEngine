#include "SuicideCommand.h"
#include "CharactersManager.h"
#include "PlayerCharacter.h"

SuicideCommand::SuicideCommand(int playerIndex)
	: m_PlayerIndex(playerIndex)
{

}

void SuicideCommand::Execute()
{
	if (PlayerCharacter* pPlayer{ CharactersManager::GetInstance().GetPlayer(m_PlayerIndex) })
	{
		pPlayer->Kill();
	}
}
