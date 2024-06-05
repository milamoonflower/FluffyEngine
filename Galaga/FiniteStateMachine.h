#pragma once

class FSMState
{
public:
	FSMState() = default;
	virtual ~FSMState() = default;

	virtual void OnEnter() {};
	virtual void Update(const float /*deltaTime*/) {}
	virtual void OnExit() {}
};

class FiniteStateMachine final
{
public:
	FiniteStateMachine() = default;
	~FiniteStateMachine() = default;

	void Update(float deltaTime);
	inline const FSMState* GetCurrentState() const { return m_pCurrentState; }
	void EnterState(FSMState* newState);
	void ExitCurrentState();

private:
	FSMState* m_pCurrentState{ nullptr };
};

