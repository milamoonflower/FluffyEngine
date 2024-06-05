#pragma once
#include "FiniteStateMachine.h"
#include "Blackboard.h"

enum class EnemyStates
{
	None,
	Entering,
	Idle,
	Exiting,
};

static const std::string ENTERING_PATH_PARAM{ "EnemyEnteringPath" };
static const std::string EXITING_PATH_PARAM{ "EnemyExitingPath" };
static const std::string CURRENT_PATH_CURVE_INDEX_PARAM{ "EnemyPathCurrentCurveIndex" };
static const std::string STARTING_POSITION_PARAM{ "EnemyPathStartingPosition" };

class EnemyEnteringState final : public FSMState
{
public:
	EnemyEnteringState() {};
	~EnemyEnteringState() {};
	void OnEnter(Blackboard& blackboard) const override;
	void Update(Blackboard& blackboard, const float deltaTime) const override;
	inline EnemyStates GetType() const { return EnemyStates::Entering; }
};

class EnemyIdleState final : public FSMState
{
public:
	EnemyIdleState() {};
	~EnemyIdleState() {};
	void OnEnter(Blackboard& blackboard) const override;
	void Update(Blackboard& blackboard, const float deltaTime) const override;
	inline EnemyStates GetType() const { return EnemyStates::Idle; }
};

class EnemyExitingState final : public FSMState
{
public:
	EnemyExitingState() {};
	~EnemyExitingState() {};
	void OnEnter(Blackboard& blackboard) const override;
	void Update(Blackboard& blackboard, const float deltaTime) const override;
	inline EnemyStates GetType() const { return EnemyStates::Exiting; }
};
