#include "Transform.h"

Transform::Transform(const glm::vec2& position)
	: m_Position{ position }
{

}

void Transform::SetPosition(const float x, const float y)
{
	m_Position.x = x;
	m_Position.y = y;
}

void Transform::SetPosition(const glm::vec2 position)
{
	m_Position = position;
}
