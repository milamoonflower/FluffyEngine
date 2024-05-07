#pragma once
#include "Component.h"
#include "Event.h"
#include <glm\glm.hpp>

namespace Fluffy
{
	class GameObject;
	class IEventListener;
	struct IEventParam;
}

class SpriteColliderComponent : public Fluffy::Component
{
public:
	SpriteColliderComponent(Fluffy::GameObject* pOwner, glm::vec2 size);
	~SpriteColliderComponent() = default;

	SpriteColliderComponent(const SpriteColliderComponent& other) = default;
	SpriteColliderComponent& operator=(const SpriteColliderComponent& other) = default;
	SpriteColliderComponent(SpriteColliderComponent&& other) = default;
	SpriteColliderComponent& operator=(SpriteColliderComponent&& other) = default;

	void Update(const float deltaTime) override;
	inline Fluffy::Event& GetOnCollision() { return m_OnCollision; }
	std::string GetTypeName() override { return typeid(*this).name(); }

private:
	glm::vec2 m_Size; // knowing the size of the collider is enough for now since we can get owner's position
	Fluffy::Event m_OnCollision{ Fluffy::EventType::OnCollision };

	bool IsOverlapping(SpriteColliderComponent* pCollider);
};

