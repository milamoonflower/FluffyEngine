#pragma once
#include "GameObject.h"
#include "SpriteColliderComponent.h"
#include "CollidersHandler.h"
#include "Structs.h"
#include "IEventParam.h"

SpriteColliderComponent::SpriteColliderComponent(Fluffy::GameObject* pOwner, glm::vec2 size)
	: Component(pOwner)
	, m_Size{ size }
{

}

void SpriteColliderComponent::Update(const float deltaTime)
{
	const auto& colliders{ CollidersHandler::GetInstance().GetAllColliderComponents() };

	for (const auto& collider : colliders)
	{
		if (collider != this && IsOverlapping(collider))
		{
			Fluffy::OnCollisionParam param{ collider };
			m_OnCollision.Invoke(&param);	// tell the listener what we collide with
		}
	}
}

bool SpriteColliderComponent::IsOverlapping(SpriteColliderComponent* pCollider)
{
	Rectf r1{ m_pOwner->GetWorldPosition(), m_pOwner->GetWorldPosition() + m_Size};
	Rectf r2{ pCollider->GetGameObject()->GetWorldPosition(), pCollider->GetGameObject()->GetWorldPosition() + pCollider->m_Size };

	// If one rectangle is on left side of the other
	if ((r1.left + r1.width) < r2.left || (r2.left + r2.width) < r1.left)
	{
		return false;
	}

	// If one rectangle is under the other
	if (r1.bottom > (r2.bottom + r2.height) || r2.bottom > (r1.bottom + r1.height))
	{
		return false;
	}

	return true;
}
