#pragma once
#include "Singleton.h"
#include <unordered_set>
#include <unordered_map>
#include <stdexcept>

namespace Fluffy
{
	class CollidersHandler final : public Singleton<CollidersHandler>
	{
	public:
		void RegisterCollisionLayers(const std::vector<std::string>& layerNames, const std::unordered_map<std::string, std::vector<std::string>> layersInteractions);

		inline void RegisterColliderComponent(class RectColliderComponent* pCollider)
		{
			m_ColliderComponents.insert(pCollider);
		}

		void UnregisterColliderComponent(class RectColliderComponent* pCollider);

		inline const std::unordered_set<class RectColliderComponent*>& GetAllColliderComponents() const { return m_ColliderComponents; }
		std::vector<class RectColliderComponent*> GetInteractableColliders(const std::string& layerName) const;

		inline void Clear()
		{
			m_ColliderComponents.clear();
		}

	private:
		std::unordered_set<class RectColliderComponent*> m_ColliderComponents{};
		std::unordered_map<std::string, unsigned int> m_CollisionLayers{};

		// layerMask here defines all the layers the [key] interacts with (for example 01101001, where each 1 is a layer, defined in m_CollisionLayers)
		std::unordered_map<std::string, unsigned int /*layerMask*/> m_LayerInteractions{};
	};
}
