#include "Keyboard.h"
#include "Command.h"
#include <functional>
#include <algorithm>

void Keyboard::Update()
{
	int keyCount{};
	const auto currentKeyboardState = SDL_GetKeyboardState(&keyCount);

	m_PreviousKeys.resize(keyCount);
	m_PressedKeys.resize(keyCount);
	m_ReleasedKeys.resize(keyCount);

	std::vector<Uint8> currentPressedKeys{ currentKeyboardState, currentKeyboardState + keyCount };
	std::vector<Uint8> difference(currentPressedKeys.size());

	// gives us the difference in current and previous keyboard states
	std::transform(currentPressedKeys.begin(), currentPressedKeys.end(), m_PreviousKeys.begin(), difference.begin(), std::bit_xor<Uint8>());

	// finds which keys are pressed
	std::transform(difference.begin(), difference.end(), currentPressedKeys.begin(), m_PressedKeys.begin(), std::bit_and<Uint8>());

	// finds which keys were released
	std::transform(difference.begin(), difference.end(), m_PreviousKeys.begin(), m_ReleasedKeys.begin(), std::bit_and<Uint8>());

	m_PreviousKeys = std::move(currentPressedKeys);
}

bool Keyboard::IsPressed(unsigned int key)
{
	return m_PressedKeys[key];
}

bool Keyboard::IsReleased(unsigned int key)
{
	return m_ReleasedKeys[key];
}

bool Keyboard::IsPrevious(unsigned int key)
{
	return m_PreviousKeys[key];
}

void Keyboard::HandleInput()
{
	for (const auto& binding : m_KeyBindings)
	{
		switch (binding.first.inputState)
		{
		case InputState::Previous:
		{
			if (IsPrevious(binding.first.key))
			{
				binding.second->Execute();
			}

			break;
		}
		case InputState::Pressed:
		{
			if (IsPressed(binding.first.key))
			{
				binding.second->Execute();
			}

			break;
		}
		case InputState::Released:
		{
			if (IsReleased(binding.first.key))
			{
				binding.second->Execute();
			}
			break;
		}
		}
	}
}

void Keyboard::AddCommand(KeyboardInput input, std::unique_ptr<Command> command)
{
	m_KeyBindings.insert({ input, std::move(command) });
}
