#pragma once
#include "Singleton.h"
#include <unordered_set>

class CollidersHandler final : public Fluffy::Singleton<CollidersHandler>
{
public:
	void AddColliderComponent(class SpriteColliderComponent* pCollider)
	{
		m_ColliderComponents.insert(pCollider);
	}

	void RemoveColliderComponent(class SpriteColliderComponent* pCollider)
	{
		m_ColliderComponents.erase(m_ColliderComponents.find(pCollider));
	}

	inline const std::unordered_set<class SpriteColliderComponent*>& GetAllColliderComponents() const { return m_ColliderComponents; }

	void Clear()
	{
		m_ColliderComponents.clear();
	}

private:
	std::unordered_set<class SpriteColliderComponent*> m_ColliderComponents;
};

