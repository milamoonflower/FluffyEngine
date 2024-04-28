#include "MoveCommand.h"
#include "Time.h"
#include "CharactersManager.h"
#include "PlayerCharacter.h"
#include "GameObject.h"

MoveCommand::MoveCommand(int playerIndex, glm::vec2 direction, float speed)
	: m_PlayerIndex(playerIndex)
	, m_Direction{ direction }
	, m_Speed{ speed }
{

}

void MoveCommand::Execute()
{
	if (GameObject* pPlayer{ CharactersManager::GetInstance().GetPlayer(m_PlayerIndex)->GetGameObject() })
	{
		glm::vec2 position{ pPlayer->GetWorldPosition() };
		position += m_Direction * (m_Speed * Time::DeltaTime());
		pPlayer->SetWorldPosition(position);
	}
}
