#include "Character.h"
#include "IEventParam.h"
#include "EventParams.h"
#include "GameObject.h"
#include "Sprite.h"
#include "SpriteColliderComponent.h"
#include "PlayerCharacter.h"

Character::Character(Fluffy::GameObject* pOwner, int livesCount)
	: Fluffy::Component(pOwner)
	, m_LivesCount{ livesCount }
{

}

void Character::Start()
{
	Fluffy::Sprite* pSpriteComponent{ m_pOwner->GetComponent<Fluffy::Sprite>() };
	Fluffy::SpriteColliderComponent* pCollider{ m_pOwner->AddComponent<Fluffy::SpriteColliderComponent>(pSpriteComponent, GetCollisionLayer()) };
	pCollider->GetOnCollisionEnter().AddListener(this);

	m_SpriteSize = pSpriteComponent->GetTextureSize();
}

void Character::Kill(int killerIndex)
{
	--m_LivesCount;

	const CharacterDeathParam eventParam{ this, killerIndex };
	m_OnDeath.Invoke(&eventParam);
}

void Character::OnNotify(const Fluffy::EventType& eventType, const Fluffy::IEventParam* pParam)
{
	switch (eventType)
	{
	case Fluffy::EventType::OnCollisionEnter:
		if (const Fluffy::CollisionParam* pCollisionParam{ static_cast<const Fluffy::CollisionParam*>(pParam) })
			OnCollisionEnter(pCollisionParam->GetOtherCollider()->GetGameObject());

		break;
	}
}
