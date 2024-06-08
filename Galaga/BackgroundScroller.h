#pragma once
#include "Component.h"
#include <glm\glm.hpp>

namespace Fluffy
{
	class GameObject;
}

class BackgroundScroller final : public Fluffy::Component
{
public:
	BackgroundScroller(Fluffy::GameObject* pOwner, const std::string& backgroundPath);

	void Update(const float deltaTime) override;

private:
	const glm::vec2 m_StartingPos;
	const float m_Speed{ 300.0f };
	float m_BGHeight{};
};
