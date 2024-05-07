#include "BulletsManager.h"
#include "GameObject.h"

void BulletsManager::Shoot(int ownerIndex, const glm::vec2& position)
{
	if (!m_BulletsPool.empty())
	{
		Bullet* pBullet;
		pBullet = m_BulletsPool.front();
		m_ActiveBullets.push_back(pBullet);
		m_BulletsPool.pop();

		pBullet->Initialize(ownerIndex, position);
	}
	else
	{
		std::shared_ptr<Fluffy::GameObject> pBulletObject{ std::make_shared<Fluffy::GameObject>(position.x, position.y) };
		Bullet* pBullet{ pBulletObject->AddComponent<Bullet>(ownerIndex, position) };
		pBullet->Initialize(ownerIndex, position);
		m_Scene->Add(pBulletObject);
	}
}

void BulletsManager::PoolBullet(int index)	// pool the bullet if it collides with a thing or is out of screen -> add events
{
	Bullet* pBullet{ m_ActiveBullets[index] };
	m_BulletsPool.push(pBullet);

	m_ActiveBullets.erase(m_ActiveBullets.begin() + index);

	pBullet->GetGameObject()->SetActive(false);
}
