#pragma once
#include "RectColliderComponent.h"
#include "GameObject.h"
#include "CollidersHandler.h"
#include "Rectf.h"
#include "IEventParam.h"
#include <algorithm>
#include <iterator>

namespace Fluffy
{
	RectColliderComponent::RectColliderComponent(GameObject* pOwner, const std::string& collisionLayerName)
		: Component(pOwner)
		, m_CollisionLayerName{ collisionLayerName }
	{

	}

	RectColliderComponent::RectColliderComponent(GameObject* pOwner, const glm::vec2& size, const std::string& collisionLayerName)
		: RectColliderComponent(pOwner, collisionLayerName)
	{
		m_Size = size;
		CollidersHandler::GetInstance().RegisterColliderComponent(this);
	}

	RectColliderComponent::~RectColliderComponent()
	{
		CollidersHandler::GetInstance().UnregisterColliderComponent(this);
	}

	void RectColliderComponent::Update(const float /*deltaTime*/)
	{
		const auto& colliders{ CollidersHandler::GetInstance().GetAllColliderComponents() };
		std::vector<RectColliderComponent*> currentCollisions{};

		for (const auto& pCollider : colliders)
		{
			if (pCollider != this && pCollider->GetGameObject()->IsActive() && IsOverlapping(pCollider))
			{
				const CollisionParam param{ this, pCollider };
				m_OnCollisionEnter.Invoke(&param);	// tell the listener what we collide with

				currentCollisions.push_back(pCollider);
			}
		}

		std::vector<RectColliderComponent*> exitCollisions{};
		std::ranges::set_difference(m_CurrentCollisions, currentCollisions, std::back_inserter(exitCollisions));

		std::ranges::for_each(exitCollisions, [this](RectColliderComponent* pCollider)
			{
				const CollisionParam param{ this, pCollider };
				m_OnCollisionExit.Invoke(&param);
				m_CurrentCollisions.erase(pCollider);
			});

		m_CurrentCollisions.insert(currentCollisions.begin(), currentCollisions.end());
	}

	Rectf RectColliderComponent::GetRect() const
	{
		return Rectf
		{
			m_pOwner->GetWorldPosition(),
			m_Size
		};
	}

	bool RectColliderComponent::IsOverlapping(const RectColliderComponent* pCollider) const
	{
		const Rectf r1{ GetRect() };
		const Rectf r2{ pCollider->GetRect() };

		// If one rectangle is on left side of the other
		if (r1.Right() < r2.left || r2.Right() < r1.left)
			return false;

		// If one rectangle is under the other
		if (r1.bottom > r2.Top() || r2.bottom > r1.Top())
			return false;

		return true;
	}
}
