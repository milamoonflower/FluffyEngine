#pragma once
#include "Singleton.h"
#include "Scene.h"
#include <glm/glm.hpp>
#include <queue>
#include <unordered_map>
#include "Bullet.h"

namespace Fluffy
{
	class GameObject;
}

class BulletsManager : public Fluffy::Singleton<BulletsManager>
{
public:
	void SetScene(Fluffy::Scene* pScene) { m_Scene = pScene; }
	void Shoot(int ownerIndex, const glm::vec2& position);

private:
	Fluffy::Scene* m_Scene;
	std::queue<Bullet*> m_BulletsPool;
	std::vector<Bullet*> m_ActiveBullets;

	void PoolBullet(int index);
};

