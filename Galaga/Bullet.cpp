#include "Bullet.h"
#include "GameObject.h"
#include "Sprite.h"
#include "SpriteColliderComponent.h"
#include "CollisionLayers.h"
#include "EventParams.h"
#include "Character.h"
#include "GameEvents.h"

Bullet::Bullet(Fluffy::GameObject* pOwner, int ownerIndex, const glm::vec2& speed)
	: Component(pOwner)
	, m_OwnerIndex{ ownerIndex }
	, m_Speed{ speed }
{
	const Fluffy::Sprite* pSprite{ m_pOwner->AddComponent<Fluffy::Sprite>(ownerIndex == INVALID_PLAYER_INDEX ? "galaga_enemy_bullet.png" : "galaga_player_bullet.png") };
	m_pOwner->AddComponent<Fluffy::SpriteColliderComponent>(pSprite, CollisionLayers::BULLET);
	m_pOwner->SetActive(true);
}

void Bullet::Update(const float deltaTime)
{
	m_pOwner->SetWorldPosition(m_pOwner->GetWorldPosition() + (m_Speed * deltaTime));
}

void Bullet::Initialize(int ownerIndex, const glm::vec2& position, const glm::vec2& speed)
{
	m_OwnerIndex = ownerIndex;
	m_Speed = speed;

	m_pOwner->GetComponent<Fluffy::Sprite>()->SetTexture(ownerIndex == INVALID_PLAYER_INDEX ? "galaga_enemy_bullet.png" : "galaga_player_bullet.png");

	m_pOwner->SetWorldPosition(position);
	m_pOwner->SetActive(true);
}

void Bullet::OnTargetHit()
{
	const BulletHitParam param{ this };
	GameEvents::OnBulletHit.Invoke(&param);
}
