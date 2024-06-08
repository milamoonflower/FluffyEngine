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

bool PlayerCharacter::IsDead() const
{
	return !m_pOwner->IsActive();
}

void PlayerCharacter::Respawn()
{
	m_pOwner->SetWorldPosition(m_RespawnPosition);
	m_pOwner->SetActive(true);
}

void PlayerCharacter::OnCollisionEnter(Fluffy::GameObject* pOtherGameObject)
{
	EnemyCharacter* pEnemy{};
	Bullet* pBullet{};
	if (pOtherGameObject->TryGetComponent<EnemyCharacter>(pEnemy) ||
	   (pOtherGameObject->TryGetComponent<Bullet>(pBullet) && pBullet->GetOwnerIndex() == INVALID_PLAYER_INDEX))
	{
		Kill();

		if (pEnemy != nullptr)
			pEnemy->Kill();

		else if (pBullet != nullptr)
			pBullet->OnTargetHit();
	}
}
