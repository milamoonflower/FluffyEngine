#pragma once
#include "Component.h"
#include <glm/glm.hpp>

namespace Fluffy
{
	class GameObject;
}

class Bullet final : public Fluffy::Component
{
public:
	Bullet(Fluffy::GameObject* pOwner, int ownerIndex, const glm::vec2& position, const glm::vec2& speed = { 0.0f, -100.0f });
	~Bullet() = default;

	void Update(const float deltaTime) override;
	std::string GetTypeName() override { return typeid(*this).name(); }
	void Initialize(int ownerIndex, const glm::vec2& position);

private:
	int m_OwnerIndex;
	glm::vec2 m_Speed;
};

