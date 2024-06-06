#pragma once
#include "ShootCommand.h"
#include "BulletsManager.h"
#include "CharactersManager.h"
#include "PlayerCharacter.h"
#include "GameObject.h"

ShootCommand::ShootCommand(int playerIndex)
	: m_PlayerIndex{ playerIndex }
{

}

void ShootCommand::Execute()
{
	const glm::vec2 position{ CharactersManager::GetInstance()->GetPlayer(m_PlayerIndex)->GetGameObject()->GetWorldPosition() };
	BulletsManager::GetInstance().Shoot(m_PlayerIndex, position);
}
