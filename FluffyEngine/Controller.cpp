#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <Xinput.h>
#include "Controller.h"
#include "Command.h"

namespace Fluffy
{
	bool ControllerInput::operator!=(const ControllerInput& other) const
	{
		return	button != other.button ||
			inputState != other.inputState;
	}

	bool ControllerInput::operator==(const ControllerInput& other) const
	{
		return !(*this != other);
	}

	void Controller::Update()
	{
		XINPUT_STATE currentState{};
		ZeroMemory(&currentState, sizeof(XINPUT_STATE));
		DWORD dwResult = XInputGetState(m_ControllerIndex, &currentState);

		if (dwResult != ERROR_SUCCESS)
		{
			ZeroMemory(&m_InputState, sizeof(XINPUT_STATE));
			m_PreviousButtons = 0;
			m_PressedButtons = 0;
			m_ReleasedButtons = 0;
			return;
		}

		const unsigned int buttonChanges = currentState.Gamepad.wButtons ^ m_PreviousButtons;
		m_PressedButtons = buttonChanges & currentState.Gamepad.wButtons;
		m_ReleasedButtons = buttonChanges & m_PreviousButtons;
		m_PreviousButtons = currentState.Gamepad.wButtons;

		CopyMemory(&m_InputState, &currentState, sizeof(XINPUT_STATE));
	}

	bool Controller::IsPressed(unsigned int button)
	{
		return m_PressedButtons & button;
	}

	bool Controller::IsReleased(unsigned int button)
	{
		return m_ReleasedButtons & button;
	}

	bool Controller::IsPrevious(unsigned int button)
	{
		return m_PreviousButtons & button;
	}

	void Controller::HandleInput()
	{
		for (const auto& binding : m_ButtonBindings)
		{
			switch (binding.first.inputState)
			{
			case InputState::Previous:
			{
				if (IsPrevious(unsigned int(binding.first.button)))
				{
					binding.second->Execute();
				}

				break;
			}
			case InputState::Pressed:
			{
				if (IsPressed(unsigned int(binding.first.button)))
				{
					binding.second->Execute();
				}

				break;
			}
			case InputState::Released:
			{
				if (IsReleased(unsigned int(binding.first.button)))
				{
					binding.second->Execute();
				}
				break;
			}
			}
		}
	}

	void Controller::AddCommand(ControllerInput input, std::unique_ptr<class Command> command)
	{
		m_ButtonBindings.insert({ input, std::move(command) });
	}
}
