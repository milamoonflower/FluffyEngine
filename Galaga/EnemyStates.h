#pragma once
#include "FiniteStateMachine.h"
#include <glm\glm.hpp>

enum class EnemyStates
{
	None,
	Entering,
	Idle,
	Diving,
};

namespace Fluffy
{
	class GameObject;
}

class EnemyEnteringState final : public FSMState
{
public:
	EnemyEnteringState(class EnemyCharacter* pOwner);
	~EnemyEnteringState() {};
	void OnEnter() override;
	void Update( const float deltaTime) override;
	inline EnemyStates GetType() const { return EnemyStates::Entering; }

private:
	class EnemyCharacter* const m_pOwner;	// the pointer is const, but the object pointed to is not

	glm::vec2 m_StartPosition{};
	int m_CurrentPathCurveIndex{ 0 };
};

class EnemyIdleState final : public FSMState
{
public:
	EnemyIdleState(class EnemyCharacter* pOwner);
	~EnemyIdleState() {};
	void OnEnter() override;
	void Update(const float deltaTime) override;
	inline EnemyStates GetType() const { return EnemyStates::Idle; }

private:
	class EnemyCharacter* const m_pOwner;
};

class EnemyDivingState final : public FSMState
{
public:
	EnemyDivingState(class EnemyCharacter* pOwner);
	~EnemyDivingState() {};
	void OnEnter() override;
	void Update(const float deltaTime) override;
	void OnExit() override;
	inline EnemyStates GetType() const { return EnemyStates::Diving; }
private:
	class EnemyCharacter* const m_pOwner;

	Fluffy::GameObject* m_Squadron{};
	glm::vec2 m_StartPosition{};
	glm::vec2 m_StartPositionInSquadron{};
	int m_CurrentPathCurveIndex{ 0 };
	bool m_IsReturningToStartPos{ false };
};
