#include "MoveCommand.h"
#include "FluffyTime.h"
#include "CharactersManager.h"
#include "PlayerCharacter.h"
#include "GameObject.h"
#include "Structs.h"
#include <iostream>
#include <algorithm>

MoveCommand::MoveCommand(int playerIndex, glm::vec2 direction, float speed)
	: m_PlayerIndex(playerIndex)
	, m_Direction{ direction }
	, m_Speed{ speed }
{

}

void MoveCommand::Execute()
{
	if (const PlayerCharacter* pPlayer{ CharactersManager::GetInstance()->GetPlayer(m_PlayerIndex) })
	{
		if (Fluffy::GameObject* pPlayerGameObject{ pPlayer->GetGameObject() })
		{
			glm::vec2 position{ pPlayerGameObject->GetWorldPosition() };
			position += m_Direction * (m_Speed * Fluffy::FluffyTime::DeltaTime());

			const float halfSpriteSize{ pPlayer->GetSpriteSize().x / 2.0f };
			position.x = std::clamp(position.x, halfSpriteSize, SCREEN_SIZE.x - halfSpriteSize);

			pPlayerGameObject->SetWorldPosition(position);
		}
	}
}
