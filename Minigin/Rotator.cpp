#include "Rotator.h"
#include "GameObject.h"

constexpr float PI{ 3.14159f };

Rotator::Rotator(const std::weak_ptr<GameObject> pOwner, const float angleDegrees, const glm::vec2& center)
	: Component(pOwner)
	, m_RotationAngleDegrees{ angleDegrees }
	, m_RotationCenter{ center }
{

}

Rotator::Rotator(const std::weak_ptr<GameObject> pOwner, const float angleDegrees, const float centerX, const float centerY)
	: Component(pOwner)
	, m_RotationAngleDegrees{ angleDegrees }
	, m_RotationCenter{ glm::vec2(centerX, centerY) }
{

}

void Rotator::Update(const float deltaTime)
{
	if (auto owner{ GetOwner() })
	{
		glm::vec2 position{ GetOwner()->GetTransform().GetPosition() };

		const float anglesRad{ m_RotationAngleDegrees * (PI / 180.0f) * deltaTime };

		const float c{ (float)cos(-anglesRad) };
		const float s{ (float)sin(-anglesRad) };

		position.x -= m_RotationCenter.x;
		position.y -= m_RotationCenter.y;

		float x = (position.x * c) - (position.y * s);
		float y = (position.x * s) + (position.y * c);

		x += m_RotationCenter.x;
		y += m_RotationCenter.y;

		GetOwner()->SetLocalPosition(x, y);
	}	
}
