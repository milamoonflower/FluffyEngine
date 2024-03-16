#include "MoveComponent.h"
#include "GameObject.h"
#include <vcruntime_typeinfo.h>

MoveComponent::MoveComponent(const std::weak_ptr<class GameObject> pOwner, float verticalSpeed, float horizontalSpeed)
	: Component(pOwner)
	, m_VerticalSpeed{ verticalSpeed }
	, m_HorizontalSpeed{ horizontalSpeed }
{

}

void MoveComponent::Update(const float deltaTime)
{
	if (m_Movement != VEC_ZERO)
	{
		glm::vec2 position{ GetOwner()->GetWorldPosition() };
		glm::vec2 movement{ deltaTime * m_Movement };
		GetOwner()->SetWorldPosition(position - movement);
		m_Movement = VEC_ZERO;
	}
}

void MoveComponent::Move(const glm::vec2& input)
{
	m_Movement = glm::vec2((input.x * m_HorizontalSpeed), (input.y * m_VerticalSpeed));
}
