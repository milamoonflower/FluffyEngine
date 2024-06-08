#include "BulletsManager.h"
#include "GameObject.h"
#include "IEventParam.h"
#include "EventParams.h"
#include "RectColliderComponent.h"
#include "Structs.h"
#include "Character.h"
#include "CollisionLayers.h"
#include "ServiceLocator.h"
#include "SDLSoundSystem.h"
#include "GameEvents.h"

const float BulletsManager::PLAYER_BULLETS_SPEED{ 400.0f };
const float BulletsManager::SHOOT_INTERVAL{ 0.2f };
const int BulletsManager::MAX_BULLETS_COUNT_PER_PLAYER{ 2 };

void BulletsManager::Shoot(const int ownerIndex, const glm::vec2& position)
{
	if (m_ShootTimer[ownerIndex] > 0.0f || m_ActivePlayerBulletCounts[ownerIndex] >= MAX_BULLETS_COUNT_PER_PLAYER)
		return;

	Bullet* pBullet;

	if (!m_BulletsPool.empty())
	{
		pBullet = m_BulletsPool.front();
		m_BulletsPool.pop();
	}
	else
	{
		std::shared_ptr<Fluffy::GameObject> pBulletObject{ std::make_shared<Fluffy::GameObject>(position) };
		pBullet = pBulletObject->AddComponent<Bullet>(ownerIndex, glm::vec2(0.0f, -PLAYER_BULLETS_SPEED));

		m_Scene->Add(pBulletObject);
	}

	m_ActiveBullets.push_back(pBullet);
	pBullet->Initialize(ownerIndex, position);

	m_ShootTimer[ownerIndex] = SHOOT_INTERVAL;
	++m_ActivePlayerBulletCounts[ownerIndex];
	++m_ShotsFired[ownerIndex];

	if (ownerIndex != INVALID_PLAYER_INDEX)
		GameEvents::OnPlayerShoot.Invoke();
}

void BulletsManager::Initialize()
{
	if (m_PlayableAreaCollider != nullptr)
		return;

	std::shared_ptr<Fluffy::GameObject> pPlayableAreaObject{ std::make_shared<Fluffy::GameObject>(0.0f, 0.0f) };
	m_PlayableAreaCollider = pPlayableAreaObject->AddComponent<Fluffy::RectColliderComponent>(SCREEN_SIZE, CollisionLayers::PLAYABLE_AREA);
	m_PlayableAreaCollider->GetOnCollisionExit().AddListener(this);

	m_Scene->Add(pPlayableAreaObject);

	GameEvents::OnBulletHit.AddListener(this);
}

void BulletsManager::Update(const float deltaTime)
{
	std::ranges::for_each(m_ShootTimer, [deltaTime](float& timer)
		{
			if (timer > 0.0f)
				timer -= deltaTime;
		});
}

void BulletsManager::OnNotify(const Fluffy::EventType& eventType, const Fluffy::IEventParam* pParam /*= nullptr*/)
{
	switch (eventType)
	{
	case Fluffy::EventType::OnBulletHit:
		if (const BulletHitParam* pBulletParam{ static_cast<const BulletHitParam*>(pParam) })
			PoolBullet(pBulletParam->GetBullet());

		break;

	case Fluffy::EventType::OnCollisionExit:
		if (const Fluffy::CollisionParam* pCollisionParam{ static_cast<const Fluffy::CollisionParam*>(pParam) })
		{
			Bullet* pBullet;
			if (pCollisionParam->GetOtherCollider()->GetGameObject()->TryGetComponent<Bullet>(pBullet))
			{
				PoolBullet(pBullet);
			}
		}
	}
}

void BulletsManager::PoolBullet(Bullet* pBullet)
{
	const auto& bullet{ std::ranges::find(m_ActiveBullets, pBullet) };
	if (bullet == m_ActiveBullets.end())
		return;

	--m_ActivePlayerBulletCounts[pBullet->GetOwnerIndex()];

	m_BulletsPool.push(pBullet);
	m_ActiveBullets.erase(bullet);

	pBullet->GetGameObject()->SetActive(false);
}
