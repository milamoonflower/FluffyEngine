#pragma once
#include "Component.h"
#include <glm/glm.hpp>
#include <memory>

constexpr glm::vec2 VEC_ZERO{ 0.0f, 0.0f };


class MoveComponent final : public Component
{
public:
	MoveComponent(const std::weak_ptr<class GameObject> pOwner, float verticalSpeed, float horizontalSpeed);
	void Update(const float deltaTime) override;

	std::string GetTypename() override
	{
		return typeid(MoveComponent).name();
	}

	void Move(const glm::vec2& input);

private:
	float m_VerticalSpeed{};
	float m_HorizontalSpeed{};

	glm::vec2 m_Movement{};
};

