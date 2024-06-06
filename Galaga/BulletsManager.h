#pragma once
#include "Singleton.h"
#include "Scene.h"
#include "Bullet.h"
#include "IEventListener.h"
#include "Event.h"
#include <glm/glm.hpp>
#include <queue>
#include <unordered_map>

namespace Fluffy
{
	class GameObject;
	class RectColliderComponent;
	struct IEventParam;
}

class BulletsManager : public Fluffy::Singleton<BulletsManager>, Fluffy::IEventListener
{
public:
	void Initialize();
	void Update(const float deltaTime);
	void SetScene(Fluffy::Scene* pScene) { m_Scene = pScene; }
	void Shoot(const int ownerIndex, const glm::vec2& position);

	void OnNotify(const Fluffy::EventType& eventType, const Fluffy::IEventParam* pParam = nullptr) override;

private:
	Fluffy::Scene* m_Scene{ nullptr };
	Fluffy::RectColliderComponent* m_PlayableAreaCollider{ nullptr };
	std::queue<Bullet*> m_BulletsPool{};
	std::vector<Bullet*> m_ActiveBullets{};

	const static float PLAYER_BULLETS_SPEED;
	const static float SHOOT_INTERVAL;
	const static int MAX_BULLETS_COUNT_PER_PLAYER;

	float m_ShootTimer[2]{ 0.0f };
	int m_ActivePlayerBulletCounts[2]{ 0 };
	int m_ShotsFired[2]{ 0 };

	void PoolBullet(Bullet* pBullet);
};
