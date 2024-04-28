#include "PlayerCharacter.h"
#include "GameObject.h"

PlayerCharacter::PlayerCharacter(GameObject* pOwner, int livesCount, int playerIndex)
	: Character(pOwner, livesCount)
	, m_PlayerIndex{ playerIndex }
{

}
