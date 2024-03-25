#include "KillEnemyCommand.h"
#include "CharactersManager.h"

KillEnemyCommand::KillEnemyCommand(int playerIndex)
	: m_PlayerIndex{ playerIndex }
{

}

void KillEnemyCommand::Execute()
{
	CharactersManager::GetInstance().KillEnemy(m_PlayerIndex);
}
