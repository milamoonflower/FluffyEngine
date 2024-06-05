#include "CollidersHandler.h"
#include "RectColliderComponent.h"
#include <algorithm>
#include <iterator>

namespace Fluffy
{
	void CollidersHandler::RegisterCollisionLayers(const std::vector<std::string>& layerNames, const std::unordered_map<std::string, std::vector<std::string>> layersInteractions)
	{
		m_CollisionLayers.clear();
		m_LayerInteractions.clear();

		for (const std::string& layerName : layerNames)
		{
			if (m_CollisionLayers.size() == 32)
				throw std::out_of_range("Can't hold this many layers! (unsigned int has only 32 bits to work with)");

			// associate each layer name with a bit position
			m_CollisionLayers.emplace(layerName, 1 << (unsigned int)m_CollisionLayers.size());
		}

		for (const auto& layerInteractions : layersInteractions)
		{
			unsigned int interactionMask{ 0 };

			for (const std::string& layerName : layerInteractions.second)
			{
				// add all the layer bits together to create the bitfield/mask
				interactionMask |= m_CollisionLayers.at(layerName);
			}

			m_LayerInteractions.emplace(layerInteractions.first, interactionMask);
		}
	}

	void CollidersHandler::UnregisterColliderComponent(class RectColliderComponent* pCollider)
	{
		const auto& componentIt{ m_ColliderComponents.find(pCollider) };
		if (componentIt != m_ColliderComponents.end())
			m_ColliderComponents.erase(componentIt);
	}

	std::vector<RectColliderComponent*> CollidersHandler::GetInteractableColliders(const std::string& layerName) const
	{
		std::vector<RectColliderComponent*> colliders{};

		const unsigned int interactionsLayerMaks{ m_LayerInteractions.at(layerName) };

		std::ranges::copy_if(m_ColliderComponents, std::back_inserter(colliders), [this, interactionsLayerMaks](const auto& collider)
			{
				// check all existing colliders, get their layer name's associated bit position and check if it is in interactionsLayerMaks
				return interactionsLayerMaks & m_CollisionLayers.at(collider->GetCollisionLayerName());
			});

		return colliders;
	}
}
