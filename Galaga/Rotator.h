#pragma once
#include "Component.h"
#include <glm/glm.hpp>

namespace Fluffy
{
	class Component;
	class GameObject;
}

constexpr float PI{ 3.14159f };

class Rotator final : public Fluffy::Component
{
public:
	Rotator(Fluffy::GameObject* pOwner, const float angleDegrees, const glm::vec2& center);
	Rotator(Fluffy::GameObject* pOwner, const float angleDegrees, const float centerX, const float centerY);
	~Rotator() = default;
	void Update(const float deltaTime) override;
	inline void SetRotationAngle(const float angleDegrees) { m_RotationAngleDegrees = angleDegrees; }
	inline void SetRotationCenter(const glm::vec2& center) { m_RotationCenter = center; }
	inline void SetRotationCenter(const float centerX, const float centerY) { m_RotationCenter = glm::vec2(centerX, centerY); }

private:
	float m_RotationAngleDegrees;
	glm::vec2 m_RotationCenter;
};
