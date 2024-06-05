#include "FiniteStateMachine.h"
#include <iostream>

void FiniteStateMachine::Update(float deltaTime)
{
	if (m_pCurrentState != nullptr)
	{
		m_pCurrentState->Update(m_Blackboard, deltaTime);
	}
}

void FiniteStateMachine::EnterState(const FSMState* newState)
{
	ExitCurrentState();

	m_pCurrentState = newState;

	if (m_pCurrentState != nullptr)
	{
		m_pCurrentState->OnEnter(m_Blackboard);
	}
}

void FiniteStateMachine::ExitCurrentState()
{
	if (m_pCurrentState != nullptr)
	{
		m_pCurrentState->OnExit(m_Blackboard);
	}

	m_pCurrentState = nullptr;
}