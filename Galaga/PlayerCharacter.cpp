#include "PlayerCharacter.h"
#include "GameObject.h"

PlayerCharacter::PlayerCharacter(Fluffy::GameObject* pOwner, int livesCount, int playerIndex)
	: Character(pOwner, livesCount)
	, m_PlayerIndex{ playerIndex }
{

}
