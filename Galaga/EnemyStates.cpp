#include "EnemyStates.h"
#include "EnemyCharacter.h"
#include "GameObject.h"

EnemyEnteringState::EnemyEnteringState(class EnemyCharacter* pOwner)
	: m_pOwner(pOwner)
{

}

void EnemyEnteringState::OnEnter()
{
	m_CurrentPathCurveIndex = 0;
}

void EnemyEnteringState::Update(const float deltaTime)
{
	const BezierPath path{ m_pOwner->GetEnteringPath() };

	Fluffy::GameObject* pOwnerObject{ m_pOwner->GetGameObject() };
	const glm::vec2 curveEndPoint{ path.GetCurve(m_CurrentPathCurveIndex).GetEndPoint() };

	const glm::vec2 distance{ curveEndPoint - pOwnerObject->GetWorldPosition() };
	pOwnerObject->GetTransform().Translate(glm::normalize(distance) * (m_pOwner->GetSpeed() * deltaTime));

	const glm::vec2 newDistance{ curveEndPoint - pOwnerObject->GetWorldPosition() };
	const float squaredMagnitude{ glm::dot<2, float>(newDistance, newDistance) };

	if (squaredMagnitude > 50.0f)
		return;

	if (path.HasCurve(m_CurrentPathCurveIndex + 1))
	{
		++m_CurrentPathCurveIndex;
	}
	else
	{
		// We arrived!
		pOwnerObject->GetTransform().SetPosition(curveEndPoint);
		m_pOwner->SetState(EnemyStates::Idle);
	}
}

EnemyIdleState::EnemyIdleState(class EnemyCharacter* pOwner)
	: m_pOwner(pOwner)
{

}

void EnemyIdleState::OnEnter()
{

}

void EnemyIdleState::Update(const float /*deltaTime*/)
{
	// Do the idle movement/formation here
}

EnemyExitingState::EnemyExitingState(class EnemyCharacter* pOwner)
	: m_pOwner(pOwner)
{

}

void EnemyExitingState::OnEnter()
{
	m_CurrentPathCurveIndex = 0;

	if (m_pOwner != nullptr)
		m_StartPosition = m_pOwner->GetGameObject()->GetWorldPosition();
}

void EnemyExitingState::Update(const float deltaTime)
{
	const BezierPath path{ m_pOwner->GetExitingPath() };

	Fluffy::GameObject* pOwnerObject{ m_pOwner->GetGameObject() };
	const glm::vec2 curveEndPoint{ m_StartPosition + path.GetCurve(m_CurrentPathCurveIndex).GetEndPoint() };

	const glm::vec2 distance{ curveEndPoint - pOwnerObject->GetWorldPosition() };
	pOwnerObject->GetTransform().Translate(glm::normalize(distance) * (m_pOwner->GetSpeed() * deltaTime));

	const glm::vec2 newDistance{ curveEndPoint - pOwnerObject->GetWorldPosition() };

	// Squared magnitude
	if (glm::dot(newDistance, newDistance) > 50.0f)
		return;

	if (path.HasCurve(m_CurrentPathCurveIndex + 1))
	{
		++m_CurrentPathCurveIndex;
	}
	else
	{
		// We arrived!
		pOwnerObject->GetTransform().SetPosition(curveEndPoint);
		m_pOwner->SetState(EnemyStates::Idle);
	}
}
