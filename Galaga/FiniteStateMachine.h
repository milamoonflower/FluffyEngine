#pragma once
#include <vector>
#include <unordered_map>
#include "Blackboard.h"

class FSMState
{
public:
	FSMState() {}
	virtual ~FSMState() = default;

	virtual void OnEnter(Blackboard& /*blackboard*/) const {};
	virtual void Update(Blackboard& /*blackboard*/, const float /*deltaTime*/) const {}
	virtual void OnExit(Blackboard& /*blackboard*/) const {}
};

class FiniteStateMachine final
{
public:
	FiniteStateMachine() = default;
	~FiniteStateMachine() = default;

	void Update(float deltaTime);
	inline const Blackboard& GetBlackboard() const { return m_Blackboard; }
	inline Blackboard& GetBlackboard() { return m_Blackboard; }
	inline const FSMState* GetCurrentState() const { return m_pCurrentState; }
	void EnterState(const FSMState* newState);
	void ExitCurrentState();

private:
	Blackboard m_Blackboard{ };
	const FSMState* m_pCurrentState{ nullptr };
};

