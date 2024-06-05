#pragma once
#include "Component.h"
#include "Event.h"
#include "Rectf.h"
#include <string>
#include <unordered_set>
#include <glm\glm.hpp>

namespace Fluffy
{
	class GameObject;
	class IEventListener;
	struct IEventParam;

	class RectColliderComponent : public Component
	{
	public:
		RectColliderComponent(GameObject* pOwner, const std::string& collisionLayerName);
		RectColliderComponent(GameObject* pOwner, const glm::vec2& size, const std::string& collisionLayerName);
		virtual ~RectColliderComponent();

		RectColliderComponent(const RectColliderComponent& other) = default;
		RectColliderComponent& operator=(const RectColliderComponent& other) = default;
		RectColliderComponent(RectColliderComponent&& other) = default;
		RectColliderComponent& operator=(RectColliderComponent&& other) = default;

		void Update(const float deltaTime) override;
		inline Event& GetOnCollisionEnter() { return m_OnCollisionEnter; }
		inline Event& GetOnCollisionExit() { return m_OnCollisionExit; }
		inline const std::string& GetCollisionLayerName() const { return m_CollisionLayerName; }

		virtual Rectf GetRect() const;

	private:
		Event m_OnCollisionEnter{ EventType::OnCollisionEnter };
		Event m_OnCollisionExit{ EventType::OnCollisionExit };
		std::string m_CollisionLayerName{};
		glm::vec2 m_Size{};

		std::unordered_set<RectColliderComponent*> m_CurrentCollisions{};

		bool IsOverlapping(const RectColliderComponent* pCollider) const;
	};
}
