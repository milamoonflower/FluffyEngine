#include "PlayerCharacter.h"
#include "GameObject.h"

PlayerCharacter::PlayerCharacter(const std::weak_ptr<GameObject> pOwner, int livesCount, int playerIndex)
	: Character(pOwner, livesCount)
	, m_PlayerIndex{ playerIndex }
{

}
