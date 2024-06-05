#pragma once
#include "Singleton.h"
#include <unordered_set>

namespace Fluffy
{
	class CollidersHandler final : public Singleton<CollidersHandler>
	{
	public:
		inline void RegisterCollisionLayer(const std::string& layerName)
		{
			m_CollisionLayers.emplace(layerName, 1 << (unsigned int)m_CollisionLayers.size());
		}

		inline void RegisterColliderComponent(class RectColliderComponent* pCollider)
		{
			m_ColliderComponents.insert(pCollider);
		}

		inline void UnregisterColliderComponent(class RectColliderComponent* pCollider)
		{
			const auto& componentIt{ m_ColliderComponents.find(pCollider) };
			if (componentIt != m_ColliderComponents.end())
				m_ColliderComponents.erase(componentIt);
		}

		inline const std::unordered_set<class RectColliderComponent*>& GetAllColliderComponents() const { return m_ColliderComponents; }

		inline void Clear()
		{
			m_ColliderComponents.clear();
		}

	private:
		std::unordered_set<class RectColliderComponent*> m_ColliderComponents{};
		std::unordered_map<std::string, unsigned int> m_CollisionLayers{};
	};
}
