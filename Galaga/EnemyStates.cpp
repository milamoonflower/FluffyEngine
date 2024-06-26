#include "EnemyStates.h"
#include "EnemyCharacter.h"
#include "PlayerCharacter.h"
#include "GameObject.h"
#include "CharactersManager.h"
#include "BulletsManager.h"
#include <glm\glm.hpp>

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
		pOwnerObject->SetWorldPosition(curveEndPoint);
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

EnemyDivingState::EnemyDivingState(class EnemyCharacter* pOwner)
	: m_pOwner(pOwner)
{

}

void EnemyDivingState::OnEnter()
{
	m_CurrentPathCurveIndex = 0;

	m_Squadron = m_pOwner->GetGameObject()->GetParent();
	m_StartPosition = m_pOwner->GetGameObject()->GetWorldPosition();
	m_StartPositionInSquadron = m_pOwner->GetGameObject()->GetLocalPosition();

	m_pOwner->GetGameObject()->SetParent(nullptr, true);

	const glm::vec2 playerPosition{ CharactersManager::GetInstance().GetPlayer(0)->GetGameObject()->GetWorldPosition() };
	const glm::vec2 shootDirection{ glm::normalize(playerPosition - m_StartPositionInSquadron) };

	BulletsManager::GetInstance().Shoot(INVALID_PLAYER_INDEX, m_StartPositionInSquadron, shootDirection);
}

void EnemyDivingState::Update(const float deltaTime)
{
	const BezierPath path{ m_pOwner->GetExitingPath() };

	Fluffy::GameObject* pOwnerObject{ m_pOwner->GetGameObject() };

	const glm::vec2 curveEndPoint
	{
		m_IsReturningToStartPos ?
		m_StartPositionInSquadron + m_Squadron->GetWorldPosition() :
		m_StartPosition + path.GetCurve(m_CurrentPathCurveIndex).GetEndPoint()
	};

	const glm::vec2 distance{ curveEndPoint - pOwnerObject->GetWorldPosition() };
	pOwnerObject->GetTransform().Translate(glm::normalize(distance) * (m_pOwner->GetSpeed() * deltaTime));

	const glm::vec2 newDistance{ curveEndPoint - pOwnerObject->GetWorldPosition() };

	// Squared magnitude
	if (glm::dot(newDistance, newDistance) > 50.0f)
		return;

	if (path.HasCurve(m_CurrentPathCurveIndex + 1))
	{
		++m_CurrentPathCurveIndex;
		m_IsReturningToStartPos = path.GetCurve(m_CurrentPathCurveIndex).GetEndPoint() == glm::vec2{ 0.0f, 0.0f };
	}
	else
	{
		// We arrived!
		pOwnerObject->SetWorldPosition(curveEndPoint);
		m_pOwner->SetState(EnemyStates::Idle);
	}
}

void EnemyDivingState::OnExit()
{
	m_pOwner->GetGameObject()->SetParent(m_Squadron, true);
}
