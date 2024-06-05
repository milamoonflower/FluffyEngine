#include "PlayerCharacter.h"
#include "GameObject.h"
#include "SpriteColliderComponent.h"
#include "EnemyCharacter.h"
#include "Bullet.h"

PlayerCharacter::PlayerCharacter(Fluffy::GameObject* pOwner, int livesCount, int playerIndex)
	: Character(pOwner, livesCount)
	, m_PlayerIndex{ playerIndex }
	, m_RespawnPosition{ pOwner->GetWorldPosition() }
{

}

void PlayerCharacter::Kill(int killerIndex)
{
	Character::Kill(killerIndex);

	m_pOwner->SetActive(false);
}

void PlayerCharacter::Respawn()
{
	m_pOwner->SetWorldPosition(m_RespawnPosition);
	m_pOwner->SetActive(true);
}

void PlayerCharacter::OnCollisionEnter(Fluffy::GameObject* pOtherGameObject)
{
	const Bullet* bullet{};
	if (pOtherGameObject->HasComponent<EnemyCharacter>() ||
	   (pOtherGameObject->TryGetComponent<Bullet>(bullet) && bullet->GetOwnerIndex() == INVALID_PLAYER_INDEX))
	{
		Kill();
	}
}
