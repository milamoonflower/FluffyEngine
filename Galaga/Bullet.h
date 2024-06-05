#pragma once
#include "Component.h"
#include "Event.h"
#include <glm/glm.hpp>

namespace Fluffy
{
	class GameObject;
}

class Bullet final : public Fluffy::Component
{
public:
	Bullet(Fluffy::GameObject* pOwner, int ownerIndex, const glm::vec2& speed = { 0.0f, -100.0f });
	~Bullet() = default;

	void Update(const float deltaTime) override;
	void Initialize(int ownerIndex, const glm::vec2& position);

	inline Fluffy::Event& GetOnTargetHitEvent() { return m_OnTargetHit; }
	void OnTargetHit();

	inline int GetOwnerIndex() const { return m_OwnerIndex; }

private:
	int m_OwnerIndex;
	glm::vec2 m_Speed;

	Fluffy::Event m_OnTargetHit{ Fluffy::EventType::OnBulletHit };
};
