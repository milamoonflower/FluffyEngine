#include "Bullet.h"
#include "GameObject.h"
#include "Sprite.h"
#include "SpriteColliderComponent.h"

Bullet::Bullet(Fluffy::GameObject* pOwner, int ownerIndex, const glm::vec2& position, const glm::vec2& speed)
	: Component(pOwner)
	, m_OwnerIndex{ ownerIndex }
	, m_Speed{ speed }
{
	Fluffy::Sprite* pSprite{ m_pOwner->AddComponent<Fluffy::Sprite>(ownerIndex == 0 ? "enemyBullet.png" : "galaga_player_bullet.png") };
	m_pOwner->AddComponent<SpriteColliderComponent>(pSprite->GetTextureSize());
	m_pOwner->SetActive(true);
	m_pOwner->SetWorldPosition(position);
}

void Bullet::Update(const float deltaTime)
{
	m_pOwner->SetWorldPosition(m_pOwner->GetWorldPosition() + (m_Speed * deltaTime));
}

void Bullet::Initialize(int ownerIndex, const glm::vec2& position)
{
	m_pOwner->GetComponentOfType<Fluffy::Sprite>()->SetTexture(ownerIndex == 0 ? "enemyBullet.png" : "galaga_player_bullet.png");

	m_pOwner->SetActive(true);
	m_pOwner->SetWorldPosition(position);
}
