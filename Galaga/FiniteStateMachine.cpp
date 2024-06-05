#include "FiniteStateMachine.h"
#include <iostream>

void FiniteStateMachine::Update(float deltaTime)
{
	if (m_pCurrentState != nullptr)
	{
		m_pCurrentState->Update(deltaTime);
	}
}

void FiniteStateMachine::EnterState(FSMState* newState)
{
	ExitCurrentState();

	m_pCurrentState = newState;

	if (m_pCurrentState != nullptr)
	{
		m_pCurrentState->OnEnter();
	}
}

void FiniteStateMachine::ExitCurrentState()
{
	if (m_pCurrentState != nullptr)
	{
		m_pCurrentState->OnExit();
	}

	m_pCurrentState = nullptr;
}