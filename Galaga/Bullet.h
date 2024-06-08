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
	Bullet(Fluffy::GameObject* pOwner, int ownerIndex, const glm::vec2& speed);
	~Bullet() = default;

	void Update(const float deltaTime) override;
	void Initialize(int ownerIndex, const glm::vec2& position, const glm::vec2& speed);
	void OnTargetHit();

	inline int GetOwnerIndex() const { return m_OwnerIndex; }

private:
	int m_OwnerIndex;
	glm::vec2 m_Speed;
};
