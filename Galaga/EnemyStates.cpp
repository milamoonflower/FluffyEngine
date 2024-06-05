#include "EnemyStates.h"
#include "EnemyCharacter.h"
#include "GameObject.h"

void EnemyEnteringState::OnEnter(Blackboard& blackboard) const
{
	blackboard.SetData(CURRENT_PATH_CURVE_INDEX_PARAM, 0);
}

void EnemyEnteringState::Update(Blackboard& blackboard, const float deltaTime) const
{
	EnemyCharacter* pOwner;
	BezierPath path;
	int currentPathCurveIndex;

	if (!blackboard.GetData(OWNER_PARAM, pOwner) ||
		!blackboard.GetData(ENTERING_PATH_PARAM, path) ||
		!blackboard.GetData(CURRENT_PATH_CURVE_INDEX_PARAM, currentPathCurveIndex))
		return;

	Fluffy::GameObject* pOwnerObject{ pOwner->GetGameObject() };
	const glm::vec2 curveEndPoint{ path.GetCurve(currentPathCurveIndex).GetEndPoint() };

	const glm::vec2 distance{ curveEndPoint - pOwnerObject->GetWorldPosition() };
	pOwnerObject->GetTransform().Translate(glm::normalize(distance) * (pOwner->GetSpeed() * deltaTime));

	const glm::vec2 newDistance{ curveEndPoint - pOwnerObject->GetWorldPosition() };
	const float squaredMagnitude{ glm::dot<2, float>(newDistance, newDistance) };

	if (squaredMagnitude > 50.0f)
		return;

	++currentPathCurveIndex;

	if (path.HasCurve(currentPathCurveIndex))
	{
		blackboard.SetData(CURRENT_PATH_CURVE_INDEX_PARAM, currentPathCurveIndex);
	}
	else
	{
		// We arrived!
		pOwnerObject->GetTransform().SetPosition(curveEndPoint);
		pOwner->SetState(EnemyStates::Idle);
	}
}

void EnemyIdleState::OnEnter(Blackboard& /*blackboard*/) const
{

}

void EnemyIdleState::Update(Blackboard& /*blackboard*/, const float /*deltaTime*/) const
{
	// Do the idle movement/formation here
}

void EnemyExitingState::OnEnter(Blackboard& blackboard) const
{
	blackboard.SetData(CURRENT_PATH_CURVE_INDEX_PARAM, 0);

	EnemyCharacter* pOwner;
	if (blackboard.GetData(OWNER_PARAM, pOwner))
	{
		blackboard.SetData(STARTING_POSITION_PARAM, pOwner->GetGameObject()->GetWorldPosition());
	}
}

void EnemyExitingState::Update(Blackboard& blackboard, const float deltaTime) const
{
	EnemyCharacter* pOwner;
	BezierPath path;
	glm::vec2 startPosition;
	int currentPathCurveIndex;

	if (!blackboard.GetData(OWNER_PARAM, pOwner) ||
		!blackboard.GetData(EXITING_PATH_PARAM, path) ||
		!blackboard.GetData(STARTING_POSITION_PARAM, startPosition) ||
		!blackboard.GetData(CURRENT_PATH_CURVE_INDEX_PARAM, currentPathCurveIndex))
		return;

	Fluffy::GameObject* pOwnerObject{ pOwner->GetGameObject() };
	const glm::vec2 curveEndPoint{ startPosition + path.GetCurve(currentPathCurveIndex).GetEndPoint() };

	const glm::vec2 distance{ curveEndPoint - pOwnerObject->GetWorldPosition() };
	pOwnerObject->GetTransform().Translate(glm::normalize(distance) * (pOwner->GetSpeed() * deltaTime));

	const glm::vec2 newDistance{ curveEndPoint - pOwnerObject->GetWorldPosition() };

	// Squared magnitude
	if (glm::dot(newDistance, newDistance) > 50.0f)
		return;

	++currentPathCurveIndex;

	if (path.HasCurve(currentPathCurveIndex))
	{
		blackboard.SetData(CURRENT_PATH_CURVE_INDEX_PARAM, currentPathCurveIndex);
	}
	else
	{
		// We arrived!
		pOwnerObject->GetTransform().SetPosition(curveEndPoint);
		pOwner->Kill();
	}
}
